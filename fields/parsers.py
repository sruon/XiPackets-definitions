"""Parsers for converting clang cursors to StructField objects"""

from clang.cindex import CursorKind
from .types import UnionVariant
from .type_utils import (
    is_signed, parse_array_type, get_type_bits, is_enum_type,
    get_enum_underlying_type, is_primitive_type, is_union_type
)
from .hint_utils import extract_hints
from .type_finder import find_type_declaration, find_variant_struct_declaration
from .exceptions import FieldParsingError


class FieldParser:
    """Handles parsing of individual fields from clang cursors"""
    
    def __init__(self, cursor):
        self.cursor = cursor
    
    def parse(self):
        """Parse cursor into StructField data"""
        # Basic info
        if self.cursor.kind == CursorKind.UNION_DECL:
            name = self.cursor.spelling
            if "unnamed" in name or not name:
                name = "data"
            type_name = f"union {name}"
            size_bytes = self.cursor.type.get_size() if hasattr(self.cursor, 'type') else 0
            signed, base_type, array_size, bits = False, f"union {name}", None, 0
            is_enum, enum_underlying_type, is_union = False, None, True
        else:
            name = self.cursor.spelling or "anonymous"
            type_name = self.cursor.type.spelling
            size_bytes = self.cursor.type.get_size() if hasattr(self.cursor, 'type') else 0
            
            # Type info
            signed = is_signed(self.cursor.type)
            base_type, array_size = parse_array_type(type_name)
            bitfield_width = self.cursor.get_bitfield_width() if self.cursor.kind == CursorKind.FIELD_DECL else 0
            bits = bitfield_width if bitfield_width > 0 else get_type_bits(type_name)
            is_enum = is_enum_type(self.cursor.type) if hasattr(self.cursor, 'type') else False
            enum_underlying_type = get_enum_underlying_type(self.cursor.type) if is_enum else None
            is_union = is_union_type(self.cursor)

        # Structure info
        hints = extract_hints(self.cursor)
        nested_fields = union_variants = discriminator_field = None
        
        if self.cursor.kind == CursorKind.UNION_DECL or (not is_primitive_type(base_type) and not is_enum):
            if is_union:
                union_variants, discriminator_field = parse_union_variants(self.cursor)
            else:
                nested_fields = parse_nested_fields(self.cursor)

        return {
            'name': name,
            'type_name': type_name,
            'bits': bits,
            'signed': signed,
            'size_bytes': size_bytes,
            'base_type': base_type,
            'array_size': array_size,
            'hints': hints,
            'is_enum': is_enum,
            'enum_underlying_type': enum_underlying_type,
            'is_union': is_union,
            'nested_fields': nested_fields,
            'union_variants': union_variants,
            'discriminator_field': discriminator_field
        }


def parse_union_variants(cursor):
    """Parse union variants and detect discriminator field"""
    type_decl = find_type_declaration(cursor)
    if not type_decl:
        raise FieldParsingError("Could not find type declaration for union field")

    discriminator_field = None
    variants = []

    for child in type_decl.get_children():
        if child.kind == CursorKind.FIELD_DECL:
            variant_name = child.spelling
            
            # Extract discriminator field name from first variant
            if discriminator_field is None:
                parts = variant_name.split('_')
                if len(parts) >= 2:
                    if parts[-1].isdigit():
                        discriminator_field = parts[-2]
                    elif len(parts) > 1:
                        discriminator_field = '_'.join(parts[:-1])

            # Extract discriminator value
            parts = variant_name.split('_')
            discriminator_value = int(parts[-1]) if len(parts) >= 2 and parts[-1].isdigit() else None

            # Parse variant fields
            variant_struct = find_variant_struct_declaration(child)
            if not variant_struct:
                raise FieldParsingError(f"Could not find struct declaration for variant {variant_name}")
            
            # Import StructField here to avoid circular import
            from .models import StructField
            variant_fields = [StructField.from_cursor(sc) for sc in variant_struct.get_children() 
                             if sc.kind == CursorKind.FIELD_DECL]
            
            variants.append(UnionVariant(variant_name, discriminator_value, variant_fields))

    return variants if variants else None, discriminator_field


def parse_nested_fields(cursor):
    """Parse nested fields for struct types"""
    type_decl = find_type_declaration(cursor)
    if not type_decl:
        raise FieldParsingError("Could not find type declaration for nested fields")
    
    # Import StructField here to avoid circular import
    from .models import StructField
    fields = [StructField.from_cursor(child) for child in type_decl.get_children() 
              if child.kind == CursorKind.FIELD_DECL]
    return fields if fields else None