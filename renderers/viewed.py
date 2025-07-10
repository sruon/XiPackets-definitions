from typing import List, Dict, Any, Optional, Union
from packet import Packet
from fields import BitField, _is_primitive_type, StructField, UnionVariant
import jinja2


class ViewedRenderer:
    def __init__(self, filename: str) -> None:
        self.template = jinja2.Environment(
            loader=jinja2.FileSystemLoader("renderers/templates")
        ).get_template("packet_ids.j2")
        self.filename: str = filename

    def render(self, packets: List[Packet]) -> None:
        with open(self.filename, "w") as f:
            content = self.template.render(packets=packets)
            f.write(content)
        print(f"Generated {self.filename}")


class PositionField:
    """Simple field class for combined position data"""

    def __init__(self) -> None:
        self.name: str = "pos"
        self.bytes: int = 12  # 3 * 4 bytes for x/z/y float fields
        self.xml_type: str = "pos"
        self.lookup: Optional[str] = None
        self.arg: Optional[str] = None


class ProcessedField:
    def __init__(self, field: Union[StructField, BitField, PositionField]) -> None:
        self.name: str = field.name
        self.bytes: int = field.bytes
        self.xml_type: str = self._determine_type(field)
        self.lookup: Optional[str] = self._determine_lookup(field)
        self.save: Optional[List[str]] = self._determine_save(field)
        self.arg: Optional[str] = self._determine_arg(field)
        self.bits: Optional[int] = getattr(field, "bits", None)
        self.is_union_type: bool = (
                isinstance(field, StructField)
                and hasattr(field, "union_variants")
                and field.union_variants is not None
        )
        self.union_variants: Optional[List[UnionVariant]] = (
            getattr(field, "union_variants", None)
            if isinstance(field, StructField)
            else None
        )

    def _determine_type(
            self, field: Union[StructField, BitField, PositionField]
    ) -> str:
        # First check for explicit type hint
        if isinstance(field, StructField) and field.hints and 'type' in field.hints:
            return field.hints['type']

        type_map = {
            "uint8_t": "byte",
            "uint16_t": "uint16",
            "uint32_t": "uint32",
            "uint64_t": "uint64",
            "int8_t": "byte",
            "int16_t": "int16",
            "int32_t": "int32",
            "int64_t": "int64",
            "float": "float",
            "double": "double",
            "char": "byte",
            "bit": "bitval",
            "int": "int",
            "uint": "uint",
            # Add common enum underlying types
            "unsigned int": "uint32",
            "int": "int32",
            "unsigned short": "uint16",
            "short": "int16",
            "unsigned char": "byte",
            "char": "byte",
            "unsigned long": "uint32",
            "long": "int32",
            "unsigned long long": "uint64",
            "long long": "int64",
        }

        # Handle direction fields
        if isinstance(field, StructField) and field.name == "dir":
            return "dir"

        # Handle enums
        if isinstance(field, StructField) and field.is_enum:
            if field.enum_type:
                mapped_type = type_map.get(field.enum_type)
                if mapped_type is None:
                    raise ValueError(f"Unknown enum underlying type: {field.enum_type} for field {field.name}")
                return mapped_type
            return "uint32"

        # Handle bit fields
        if isinstance(field, BitField):
            if field.bits == 1:
                return "bitval"
            return "byte"

        # Handle arrays
        if isinstance(field, StructField) and field.array_size:
            return "t" if field.base_type == "char" else "a"

        # Handle position fields
        if isinstance(field, PositionField):
            return "pos"

        # Map basic types
        field_type = field.type if isinstance(field, StructField) else field.base_type
        mapped_type = type_map.get(field_type)
        if mapped_type is None:
            raise ValueError(f"Unknown type: {field_type} for field {field.name}")
        return mapped_type

    def _determine_lookup(
            self, field: Union[StructField, BitField, PositionField]
    ) -> Optional[str]:
        hints = getattr(field, "hints", {}) or {}
        return hints.get("lookup")

    def _determine_save(
            self, field: Union[StructField, BitField, PositionField]
    ) -> Optional[List[str]]:
        hints = getattr(field, "hints", {}) or {}
        save = hints.get("save")
        if save is None:
            return None
        return [save] if isinstance(save, str) else save

    def _determine_arg(
            self, field: Union[StructField, BitField, PositionField]
    ) -> Optional[str]:
        # First check for explicit bits hint
        if isinstance(field, StructField) and field.hints and 'bits' in field.hints:
            return field.hints['bits']

        # Then handle array size
        if (
                isinstance(field, StructField)
                and hasattr(field, "array_size")
                and field.array_size
        ):
            return str(field.array_size)
        return None


class ProcessedPacket:
    """Packet class for preprocessed packets"""

    def __init__(self, name: str, packet_id: str, fields: List):
        self.name = name
        self.id = packet_id
        self.fields = fields
