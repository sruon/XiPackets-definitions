"""Utilities for finding type declarations in clang AST"""

from clang.cindex import CursorKind, TypeKind
from .type_utils import parse_array_type


def find_type_declaration(cursor):
    """Find the declaration for a custom type"""
    # Try direct type declaration from type object
    if hasattr(cursor, 'type'):
        if cursor.type.kind == TypeKind.RECORD:
            return cursor.type.get_declaration()
        elif cursor.type.kind == TypeKind.ELABORATED:
            canonical = cursor.type.get_canonical()
            if canonical.kind == TypeKind.RECORD:
                return canonical.get_declaration()
    
    # Fallback: search translation unit
    if not hasattr(cursor, 'type'):
        return None
        
    base_type = parse_array_type(cursor.type.spelling)[0]
    clean_type_name = base_type.replace('struct ', '').replace('union ', '').strip()
    
    for c in cursor.translation_unit.cursor.walk_preorder():
        if (c.kind in [CursorKind.STRUCT_DECL, CursorKind.UNION_DECL] and 
            c.spelling == clean_type_name):
            return c
    return None


def find_variant_struct_declaration(variant_cursor):
    """Find the struct declaration for a union variant"""
    from .exceptions import FieldParsingError
    
    variant_type = variant_cursor.type
    if variant_type.kind == TypeKind.ELABORATED:
        canonical = variant_type.get_canonical()
        if canonical.kind == TypeKind.RECORD:
            return canonical.get_declaration()
    elif variant_type.kind == TypeKind.RECORD:
        return variant_type.get_declaration()
    raise FieldParsingError("Could not find struct declaration for union variant")