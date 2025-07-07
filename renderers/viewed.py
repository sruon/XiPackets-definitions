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
        }

        field_type = getattr(field, "type", "")
        if isinstance(field, BitField):
            if field.bits == 1:
                return "bitval"
            return "uint" if not field.signed else "int"

        if isinstance(field, StructField) and field.array_size is not None:
            if field.base_type == "char":
                return "t"
            return "a"

        return type_map.get(field_type, "unknown")

    def _determine_lookup(
        self, field: Union[StructField, BitField, PositionField]
    ) -> Optional[str]:
        hints = getattr(field, "hints", {}) or {}
        return hints.get("lookup")

    def _determine_arg(
        self, field: Union[StructField, BitField, PositionField]
    ) -> Optional[str]:
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


class FFXIXmlRenderer:
    def __init__(self, filename: str) -> None:
        self.template = jinja2.Environment(
            loader=jinja2.FileSystemLoader("renderers/templates")
        ).get_template("ffxi.xml.j2")
        self.filename: str = filename

    def render(self, s2c_packets: List[Packet], c2s_packets: List[Packet]) -> None:
        processed_s2c = [self._process_packet(p) for p in s2c_packets]
        processed_c2s = [self._process_packet(p) for p in c2s_packets]

        with open(self.filename, "w") as f:
            content = self.template.render(
                s2c_packets=processed_s2c, c2s_packets=processed_c2s
            )
            f.write(content)
        print(f"Generated {self.filename}")

    def _process_packet(self, packet: Packet) -> Dict[str, Any]:
        return {
            "id": packet.id,
            "name": packet.name,
            "fields": self._preprocess_fields(packet.fields),
        }

    def _preprocess_fields(self, fields: List[StructField]) -> List[Dict[str, Any]]:
        processed_fields: List[Dict[str, Any]] = []
        field_idx = 0

        while field_idx < len(fields):
            field = fields[field_idx]

            if field.name in ["id", "size", "sync"]:
                field_idx += 1
                continue

            if (
                field.name == "x"
                and field_idx + 2 < len(fields)
                and fields[field_idx + 1].name == "z"
                and fields[field_idx + 2].name == "y"
            ):
                processed_fields.append(
                    self._convert_to_dict(ProcessedField(PositionField()))
                )
                field_idx += 3
                continue

            if field.is_union_type():
                union_data = self._process_union_field(field)
                processed_fields.append(union_data)
            else:
                expanded = self._expand_array_field(field)
                processed_fields.extend(self._convert_to_dict(f) for f in expanded)

            field_idx += 1

        return processed_fields

    def _process_union_field(self, field: StructField) -> Dict[str, Any]:
        discriminator = self._extract_discriminator_name(field)
        cases: List[Dict[str, Any]] = []

        if field.union_variants:
            for variant in field.union_variants:
                case_num = self._extract_case_number(variant.name)
                case_fields = []
                for variant_field in variant.fields:
                    expanded = self._expand_array_field(variant_field)
                    case_fields.extend(self._convert_to_dict(f) for f in expanded)

                cases.append({"value": case_num, "fields": case_fields})

        return {
            "name": field.name,
            "is_union": True,
            "discriminator": discriminator,
            "cases": cases,
        }

    def _extract_discriminator_name(self, field: StructField) -> str:
        if field.union_variants and field.union_variants[0].name:
            variant_name = field.union_variants[0].name
            if "_" in variant_name:
                return variant_name.split("_")[0]
        return "Unknown"

    def _extract_case_number(self, variant_name: str) -> int:
        if "_" in variant_name:
            parts = variant_name.split("_")
            try:
                return int(parts[-1])
            except ValueError:
                pass
        return 0

    def _expand_array_field(self, field: StructField) -> List[ProcessedField]:
        expanded_fields: List[ProcessedField] = []

        if hasattr(field, "bits") and field.bits > 0:
            bitfield = BitField(field.name, field.bits, field.signed)
            processed = ProcessedField(bitfield)
            expanded_fields.append(processed)
            return expanded_fields

        if hasattr(field, "array_size") and field.array_size:
            if field.base_type == "uint8_t" or field.base_type == "char":
                expanded_fields.append(ProcessedField(field))
                return expanded_fields

            for array_idx in range(field.array_size):
                element_name = f"{field.name}_{array_idx + 1}"
                element_field = self._create_array_element(field, element_name)
                if element_field.is_custom_type():
                    expanded_fields.extend(
                        ProcessedField(bf) for bf in element_field.get_expanded_fields()
                    )
                else:
                    expanded_fields.append(ProcessedField(element_field))
            return expanded_fields

        if field.is_custom_type():
            expanded_fields.extend(
                ProcessedField(bf) for bf in field.get_expanded_fields()
            )
        else:
            expanded_fields.append(ProcessedField(field))

        return expanded_fields

    def _create_array_element(
        self, original_field: StructField, element_name: str
    ) -> StructField:
        element_field = StructField(original_field._clang_field)
        element_field.name = element_name
        element_field.type = original_field.base_type
        element_field.base_type = original_field.base_type
        element_field.array_size = None
        return element_field

    def _convert_to_dict(self, processed_field: ProcessedField) -> Dict[str, Any]:
        result: Dict[str, Any] = {
            "name": processed_field.name,
            "xml_type": processed_field.xml_type,
            "bytes": processed_field.bytes,
        }

        if processed_field.bits is not None and processed_field.bits > 0:
            result["bits"] = processed_field.bits
        if processed_field.lookup:
            result["lookup"] = processed_field.lookup
        if processed_field.arg:
            result["arg"] = processed_field.arg

        return result
