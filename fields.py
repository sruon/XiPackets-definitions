import re
import clang.cindex as clang
from clang.cindex import CursorKind, TypeKind
from typing import Optional, List, Dict, Any, Union as UnionType


def _is_signed(type_obj):
    """Check if type is signed"""
    type_name = type_obj.spelling.lower()
    if 'unsigned' in type_name or type_name.startswith('uint'):
        return False
    elif 'signed' in type_name or type_name.startswith('int') or type_name in ['char', 'short', 'long']:
        return True
    return False  # For non-integer types like arrays


def _parse_array(type_obj):
    """Extract base type and array size"""
    type_str = type_obj.spelling

    # Check if it's an array type
    if '[' in type_str and ']' in type_str:
        # Extract base type and array size
        match = re.match(r'(.+?)\s*\[(\d+)\]', type_str)
        if match:
            base_type = match.group(1).strip()
            array_size = int(match.group(2))
            return base_type, array_size

    # Not an array
    return type_str, None


def _extract_hint(field):
    """Extract structured hints from inline comment"""
    if not field.location.file:
        return {}

    with open(field.location.file.name, 'r') as f:
        lines = f.readlines()

    line = lines[field.location.line - 1]
    if '//' in line:
        comment = line.split('//')[1].strip()
        hints = {}

        # Parse key:value pairs
        for match in re.finditer(r'(\w+):(\w+)', comment):
            hints[match.group(1)] = match.group(2)

        # Parse standalone keywords
        words = re.findall(r'\b\w+\b', comment)
        for word in words:
            if ':' not in comment or word not in comment.replace(':', ' '):
                if 'flags' not in hints:
                    hints['flags'] = []
                if word not in [k for k, v in hints.items() if k != 'flags']:
                    hints['flags'].append(word)

        return hints if hints else None

    return None


def _is_primitive_type(type_name):
    """Check if a type is a primitive C type"""
    primitives = {
        'char', 'signed char', 'unsigned char',
        'short', 'signed short', 'unsigned short', 'short int', 'signed short int', 'unsigned short int',
        'int', 'signed int', 'unsigned int', 'signed', 'unsigned',
        'long', 'signed long', 'unsigned long', 'long int', 'signed long int', 'unsigned long int',
        'long long', 'signed long long', 'unsigned long long', 'long long int', 'signed long long int',
        'unsigned long long int',
        'float', 'double', 'long double',
        'void',
        # Common typedefs
        'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
        'int8_t', 'int16_t', 'int32_t', 'int64_t',
        'size_t', 'ssize_t'
    }
    return type_name.strip() in primitives


class BitField:
    def __init__(self, name: str, bits: int, signed: bool = False) -> None:
        self.name = name
        self.bits = bits
        self.signed = signed
        self.bytes = 0
        self.type = f"{'int' if signed else 'uint'}{bits}" if bits > 1 else "bit"

    def __repr__(self) -> str:
        return f"BitField(name={self.name}, bits={self.bits}, signed={self.signed})"


class UnionVariant:
    def __init__(self, name: str, fields: list, type_name: Optional[str] = None) -> None:
        self.name = name
        self.fields = fields
        self.type_name = type_name
        self.bytes = max(field.bytes for field in fields) if fields else 0

    def __repr__(self) -> str:
        type_str = f" (type: {self.type_name})" if self.type_name else ""
        return f"UnionVariant(name={self.name}, fields={len(self.fields)}, bytes={self.bytes}){type_str}"


class StructField:
    def __init__(self, field) -> None:
        if field.kind == getattr(CursorKind, 'UNION_DECL'):
            self.name = field.spelling or "anonymous_union"
            self.type = field.type.spelling
            self.bits = -1
        else:
            self.name = field.spelling
            self.type = field.type.spelling
            self.bits = field.get_bitfield_width()

        self.signed = _is_signed(field.type)
        self.bytes = field.type.get_size()
        self.base_type, self.array_size = _parse_array(field.type)
        self.hints = _extract_hint(field)
        self._clang_field = field
        self._expanded_fields = None
        self.union_variants = None
        if self.is_union_type(): self._parse_union_variants()

    def is_custom_type(self) -> bool:
        base_type = self.base_type if self.array_size else self.type
        return not _is_primitive_type(base_type)

    def is_union_type(self) -> bool:
        return (self._clang_field.type.kind == getattr(TypeKind, 'RECORD') and
                self._clang_field.type.get_declaration().kind == getattr(CursorKind, 'UNION_DECL'))

    def _parse_union_variants(self) -> None:
        if not self.is_union_type(): return
        union_decl = self._clang_field.type.get_declaration()
        self.union_variants = []
        for child in union_decl.get_children():
            if child.kind == getattr(CursorKind, 'FIELD_DECL'):
                variant_name = child.spelling
                variant_type_name = child.type.spelling
                variant_struct = self._find_variant_struct(variant_type_name)
                if variant_struct:
                    struct_fields = []
                    for struct_child in variant_struct.get_children():
                        if struct_child.kind == getattr(CursorKind, 'FIELD_DECL'):
                            struct_fields.append(StructField(struct_child))
                    variant = UnionVariant(variant_name, struct_fields, variant_type_name)
                    self.union_variants.append(variant)

    def _find_variant_struct(self, type_name):
        tu = self._clang_field.translation_unit
        for cursor in tu.cursor.walk_preorder():
            if cursor.kind == getattr(CursorKind, 'TYPEDEF_DECL') and cursor.spelling == type_name:
                underlying = cursor.underlying_typedef_type
                if underlying.kind == getattr(TypeKind, 'RECORD'):
                    return underlying.get_declaration()
                elif underlying.kind == getattr(TypeKind, 'TYPEDEF'):
                    return self._find_variant_struct(underlying.spelling)

        clean_type_name = type_name.replace('struct ', '').strip()
        for cursor in tu.cursor.walk_preorder():
            if cursor.kind == getattr(CursorKind, 'STRUCT_DECL') and cursor.spelling == clean_type_name:
                return cursor
        return None

    def get_union_variant(self, variant_name):
        if not self.union_variants: return None
        for variant in self.union_variants:
            if variant.name == variant_name: return variant
        return None

    def get_expanded_fields(self):
        if self._expanded_fields is not None: return self._expanded_fields
        if not self.is_custom_type():
            self._expanded_fields = [self]
            return self._expanded_fields
        if self.is_union_type():
            self._expanded_fields = [self]
            return self._expanded_fields

        type_decl = self._find_type_declaration()
        if not type_decl:
            self._expanded_fields = [self]
            return self._expanded_fields

        expanded = []
        for child in type_decl.get_children():
            if child.kind == getattr(CursorKind, 'FIELD_DECL'):
                bitfield_width = child.get_bitfield_width()
                if bitfield_width > 0:
                    field_name = child.spelling
                    is_signed = _is_signed(child.type)
                    expanded.append(BitField(field_name, bitfield_width, is_signed))
                else:
                    nested_field = StructField(child)
                    expanded.extend(nested_field.get_expanded_fields())

        self._expanded_fields = expanded if expanded else [self]
        return self._expanded_fields

    def _find_type_declaration(self):
        type_name = self.base_type if self.array_size else self.type
        tu = self._clang_field.translation_unit

        for cursor in tu.cursor.walk_preorder():
            if cursor.kind == getattr(CursorKind, 'TYPEDEF_DECL') and cursor.spelling == type_name:
                underlying = cursor.underlying_typedef_type
                if underlying.kind == getattr(TypeKind, 'RECORD'):
                    return underlying.get_declaration()
                elif underlying.kind == getattr(TypeKind, 'TYPEDEF'):
                    return self._find_variant_struct(underlying.spelling)

        clean_type_name = type_name.replace('struct ', '').strip()
        for cursor in tu.cursor.walk_preorder():
            if cursor.kind == getattr(CursorKind, 'STRUCT_DECL') and cursor.spelling == clean_type_name:
                return cursor
        return None

    def __repr__(self) -> str:
        array_str = f"[{self.array_size}]" if self.array_size else ""
        bits_str = f" ({self.bits} bits)" if self.bits > 0 else ""
        return f"StructField(name={self.name}, type={self.type}{array_str}{bits_str})"