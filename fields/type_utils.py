"""Type analysis utilities for C types"""

import re
from typing import Optional, Tuple
from clang.cindex import TypeKind

from .exceptions import FieldParsingError


def is_signed(clang_type) -> bool:
    """Check if clang type is signed"""
    type_name = clang_type.spelling.lower()
    if 'unsigned' in type_name or type_name.startswith('uint'):
        return False
    elif 'signed' in type_name or any(t in type_name for t in ['char', 'short', 'int', 'long']):
        return True
    return False


def get_type_bits(type_name: str) -> int:
    """Get bit size for type"""
    type_name = type_name.lower()
    if any(t in type_name for t in ['char', 'int8']):
        return 8
    elif any(t in type_name for t in ['short', 'int16']):
        return 16
    elif any(t in type_name for t in ['int32']) or (type_name == 'int' or type_name == 'long'):
        return 32
    elif 'float' in type_name:
        return 32
    return 0


def parse_array_type(type_name: str) -> Tuple[str, Optional[int]]:
    """Parse array type and return (base_type, array_size)"""
    if '[' not in type_name:
        return type_name, None
    match = re.match(r'(.+?)\s*\[(\d+)\]', type_name)
    if match:
        return match.group(1).strip(), int(match.group(2))
    return type_name, None


def is_enum_type(clang_type) -> bool:
    """Check if clang type is an enum"""
    if clang_type.kind == TypeKind.ENUM:
        return True
    if clang_type.kind == TypeKind.ELABORATED:
        return clang_type.get_canonical().kind == TypeKind.ENUM
    if clang_type.kind == TypeKind.TYPEDEF:
        raise FieldParsingError("typedef not supported")
    return False


def get_enum_underlying_type(clang_type) -> Optional[str]:
    """Get the underlying type of an enum"""
    try:
        if clang_type.kind == TypeKind.ENUM:
            decl = clang_type.get_declaration()
        elif clang_type.kind in [TypeKind.TYPEDEF, TypeKind.ELABORATED]:
            decl = clang_type.get_canonical().get_declaration()
        else:
            return None
        return decl.enum_type.spelling if hasattr(decl, 'enum_type') else 'int'
    except:
        return None


def is_primitive_type(type_name: str) -> bool:
    """Check if type is a primitive C type"""
    primitives = {
        'char', 'signed char', 'unsigned char',
        'short', 'unsigned short', 'signed short',
        'int', 'unsigned int', 'signed int', 'signed', 'unsigned',
        'long', 'unsigned long', 'signed long',
        'long long', 'unsigned long long', 'signed long long',
        'float', 'double', 'long double', 'void',
        'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
        'int8_t', 'int16_t', 'int32_t', 'int64_t',
        'size_t', 'ssize_t'
    }
    return type_name.strip() in primitives


def is_union_type(cursor) -> bool:
    """Check if cursor represents a union type"""
    from clang.cindex import CursorKind
    return (cursor.type.kind == TypeKind.RECORD and
            cursor.type.get_declaration().kind == CursorKind.UNION_DECL)