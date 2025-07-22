"""Data models for struct fields and union variants"""

from dataclasses import dataclass
from typing import Optional, List, Dict, Any

from .exceptions import FieldParsingError
from .types import UnionVariant


@dataclass
class StructField:
    """Represents a single field in a C struct, with nested field support"""
    name: str
    type_name: str
    bits: int
    signed: bool
    size_bytes: int
    base_type: str
    array_size: Optional[int]
    hints: Optional[Dict[str, Any]]
    is_enum: bool
    enum_underlying_type: Optional[str]
    is_union: bool = False
    nested_fields: Optional[List['StructField']] = None
    union_variants: Optional[List[UnionVariant]] = None
    discriminator_field: Optional[str] = None

    @classmethod
    def from_cursor(cls, cursor) -> 'StructField':
        """Create StructField from clang cursor"""
        try:
            from .parsers import FieldParser
            parser = FieldParser(cursor)
            field_data = parser.parse()
            return cls(**field_data)
        except Exception as e:
            raise FieldParsingError(f"Failed to parse field from cursor: {e}")

    @property
    def is_bitfield(self) -> bool:
        from .type_utils import get_type_bits
        return 0 < self.bits < get_type_bits(self.type_name)

    @property
    def is_array(self) -> bool:
        return self.array_size is not None

    @property
    def is_primitive(self) -> bool:
        from .type_utils import is_primitive_type
        return is_primitive_type(self.base_type)

    @property
    def has_variants(self) -> bool:
        return self.union_variants is not None and len(self.union_variants) > 0

    @property
    def has_nested_fields(self) -> bool:
        return self.nested_fields is not None and len(self.nested_fields) > 0

    @property
    def effective_type(self) -> str:
        if self.is_enum and self.enum_underlying_type:
            return self.enum_underlying_type
        return self.base_type

    def get_variant_by_value(self, discriminator_value: int) -> Optional[UnionVariant]:
        if not self.has_variants:
            return None
        return next((v for v in self.union_variants if v.discriminator_value == discriminator_value), None)

    def get_all_fields_flat(self) -> List['StructField']:
        result = [self]
        if self.has_nested_fields:
            for field in self.nested_fields:
                result.extend(field.get_all_fields_flat())
        if self.has_variants:
            for variant in self.union_variants:
                for field in variant.fields:
                    result.extend(field.get_all_fields_flat())
        return result

    def find_field_by_name(self, field_name: str) -> Optional['StructField']:
        if self.name == field_name:
            return self
        if self.has_nested_fields:
            for field in self.nested_fields:
                found = field.find_field_by_name(field_name)
                if found:
                    return found
        if self.has_variants:
            for variant in self.union_variants:
                for field in variant.fields:
                    found = field.find_field_by_name(field_name)
                    if found:
                        return found
        return None

    def __str__(self) -> str:
        type_str = f"{self.type_name}:{self.bits}" if self.is_bitfield else self.type_name
        parts = [f"{self.name}: {type_str}"]
        if self.bits > 0:
            parts.append(f"({self.bits} bits)")
        if self.signed is not None:
            parts.append("signed" if self.signed else "unsigned")
        if self.has_nested_fields:
            parts.append(f"[{len(self.nested_fields)} nested fields]")
        if self.has_variants:
            parts.append(f"[{len(self.union_variants)} variants via {self.discriminator_field}]")
        if self.hints:
            parts.append(f"hints={self.hints}")
        return " ".join(parts)