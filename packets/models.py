"""Packet model and related functionality"""

from clang import cindex as clang
from dataclasses import dataclass
from typing import List

from fields import StructField
from .exceptions import PacketParsingError
from .utils import extract_packet_id


@dataclass
class Packet:
    """Represents a network packet with its fields"""
    name: str
    id: str
    fields: List[StructField]

    @classmethod
    def from_cursor(cls, cursor) -> 'Packet':
        """Create Packet from clang cursor"""
        try:
            name = cursor.spelling
            if not name:
                raise PacketParsingError("Packet cursor has no name")
            
            packet_id = extract_packet_id(cursor)
            fields = [StructField.from_cursor(field) for field in cursor.get_children()
                     if field.kind in [clang.CursorKind.FIELD_DECL, clang.CursorKind.UNION_DECL]]
            
            return cls(name, packet_id, fields)
        except Exception as e:
            raise PacketParsingError(f"Failed to parse packet from cursor: {e}")

    def find_field_by_name(self, field_name: str) -> StructField:
        """Find a field by name (searches recursively through nested fields)"""
        for field in self.fields:
            found = field.find_field_by_name(field_name)
            if found:
                return found
        return None

    def get_all_fields_flat(self) -> List[StructField]:
        """Get all fields including nested ones in a flat list"""
        result = []
        for field in self.fields:
            result.extend(field.get_all_fields_flat())
        return result

    @property
    def field_count(self) -> int:
        """Get total number of fields including nested ones"""
        return len(self.get_all_fields_flat())

    def __str__(self) -> str:
        """Human-readable representation"""
        return f"Packet({self.name}, id={self.id}, {len(self.fields)} fields)"