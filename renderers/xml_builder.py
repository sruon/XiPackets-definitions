from typing import List, Optional, Dict, Any, Union, cast
from xml.etree.ElementTree import Element, SubElement, tostring
from xml.dom import minidom
from packet import Packet
from fields import StructField, BitField, UnionVariant


class XMLField:
    """Base class for XML field representations"""
    def __init__(self, name: str) -> None:
        self.name = name

    def to_xml(self, indent: str = "") -> Union[Element, List[Element]]:
        raise NotImplementedError()


class ArrayField(XMLField):
    """Represents an array field in XML with loop structure"""
    def __init__(self, name: str, base_type: str, array_size: int,
                 bits: Optional[int] = None, lookup: Optional[str] = None,
                 struct_fields: Optional[List[XMLField]] = None) -> None:
        super().__init__(name)
        self.base_type = base_type
        self.array_size = array_size
        self.bits = bits
        self.lookup = lookup
        self.struct_fields = struct_fields

    def to_xml(self, indent: str = "") -> List[Element]:
        """Convert to XML element"""
        result: List[Element] = []

        # <echo arg="GrapIDTbl[]">
        #     <mov dst="GrapIDTbl[]" val="0" />
        #     <loop>
        #         <ifgte arg1="#GrapIDTbl[]" arg2="9">
        #             <break />
        #         </ifgte>
        #         <echo name="Index" arg="GrapIDTbl[]">
        #             <data type="uint16" name="GrapIDTbl" />
        #         </echo>
        #         <add dst="GrapIDTbl[]" arg1="#GrapIDTbl[]" arg2="1" />
        #     </loop>
        # </echo>

        root_name = f"{self.name}[]"
        # Create root loop element
        root_echo = Element("echo")
        root_echo.set("arg", root_name)
        result.append(root_echo)

        # Initial mov instruction
        mov = Element("mov")
        mov.set("dst", root_name)
        mov.set("val", "0")
        root_echo.append(mov)

        # Loop tag
        loop = Element("loop")

        # Ifgte instruction
        ifgte = Element("ifgte")
        ifgte.set("arg1", f"#{root_name}")
        ifgte.set("arg2", str(self.array_size))
        break_elem = Element("break")
        ifgte.append(break_elem)
        loop.append(ifgte)

        # Echo instruction
        echo = Element("echo")
        echo.set("arg", root_name)
        echo.set("name", "Index")
        loop.append(echo)

        # For struct arrays, add the struct fields inside an echo tag
        if self.base_type == "struct" and self.struct_fields:
            echo_elem = Element("echo")
            echo_elem.set("arg", self.name)
            for field in self.struct_fields:
                field_result = field.to_xml(indent + "\t")
                if isinstance(field_result, list):
                    # Handle fields that return multiple elements (saves)
                    for element in field_result:
                        echo_elem.append(element)  # type: ignore
                else:
                    echo_elem.append(field_result)  # type: ignore
            echo.append(echo_elem)
        else:
            # Regular array field - use base type
            data = Element("data")
            data.set("type", self.base_type)
            data.set("name", self.name)
            if self.bits is not None:
                data.set("bits", str(self.bits))
            if self.lookup is not None:
                data.set("lookup", self.lookup)
            echo.append(data)

        # Add instruction
        add = Element("add")
        add.set("dst", root_name)
        add.set("arg1", f"#{root_name}")
        add.set("arg2", "1")
        loop.append(add)

        root_echo.append(loop)
        return result


class DataField(XMLField):
    """Represents a basic data field in XML"""
    def __init__(self, name: str, xml_type: str, bits: Optional[int] = None,
                 array_size: Optional[int] = None, lookup: Optional[str] = None,
                 save: Optional[List[str]] = None, base_type: Optional[str] = None) -> None:
        super().__init__(name)
        self.xml_type = xml_type
        self.bits = bits
        self.array_size = array_size
        self.lookup = lookup
        self.save = save
        self.base_type = base_type

    def to_xml(self, indent: str = "") -> Union[Element, List[Element]]:
        """Convert to XML element"""
        result: List[Element] = []

        # If this is an array, use ArrayField
        if self.array_size is not None and self.array_size > 0 and self.xml_type != "t":
            # Use the base type if provided, otherwise use char for text arrays and byte for other arrays
            base_type = self.base_type if self.base_type else ("char" if self.xml_type == "t" else "byte")
            array_field = ArrayField(self.name, base_type, self.array_size, self.bits, self.lookup)
            result.extend(array_field.to_xml(indent))
        else:
            # Non-array field or text field
            elem = Element("data")
            elem.set("type", self.xml_type)
            elem.set("name", self.name)

            # For text fields, set the arg attribute to the array size
            if self.xml_type == "t" and self.array_size is not None:
                elem.set("arg", str(self.array_size))

            if self.bits is not None:
                elem.set("bits", str(self.bits))
            if self.lookup is not None:
                elem.set("lookup", self.lookup)

            result.append(elem)

        # If we have save hints, add lookup tags after the data tag
        if self.save:
            for save_hint in self.save:
                lookup = Element("lookup")
                lookup.set("save", save_hint)  # Keep the original save hint as is
                lookup.set("source", save_hint.replace('@', ''))  # Use the field name for source
                lookup.set("val", self.name)
                result.append(lookup)

        return result if len(result) > 1 else result[0]

    def _get_base_type(self) -> str:
        """Get the base type for arrays"""
        # Map array type 'a' to the actual base type
        type_map = {
            "a": {
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
                "unsigned int": "uint32",
                "unsigned short": "uint16",
                "unsigned char": "byte",
                "unsigned long": "uint64",
                "long long": "int64",
            }
        }
        if self.xml_type == "a":
            # Extract the base type from the field type
            base_type = self.xml_type.split("[")[0] if "[" in self.xml_type else self.xml_type
            return type_map["a"].get(base_type, "byte")
        return self.xml_type


class EchoField(XMLField):
    """Represents a struct group in XML with echo tag"""
    def __init__(self, name: str, fields: List[XMLField]) -> None:
        super().__init__(name)
        self.fields = fields

    def to_xml(self, indent: str = "") -> Element:
        """Convert to XML element"""
        elem = Element("echo")
        elem.set("arg", self.name)

        for field in self.fields:
            field_result = field.to_xml(indent + "\t")
            if isinstance(field_result, list):
                # Handle fields that return multiple elements (saves)
                for element in field_result:
                    elem.append(element)  # type: ignore
            else:
                elem.append(field_result)  # type: ignore

        return elem


class UnionField(XMLField):
    """Represents a union field in XML with ifeq tags"""
    def __init__(self, discriminator: str, cases: Dict[str, List[XMLField]]) -> None:
        super().__init__("")
        self.discriminator = discriminator
        self.cases = cases

    def to_xml(self, indent: str = "") -> List[Element]:
        """Convert to XML element"""
        # Create a list to hold the ifeq tags
        result = []
        for case_value, fields in self.cases.items():
            ifeq = Element("ifeq")
            ifeq.set("arg1", f"#{self.discriminator}")
            ifeq.set("arg2", case_value)
            for field in fields:
                field_result = field.to_xml(indent + "\t")
                if isinstance(field_result, list):
                    # Handle fields that return multiple elements (arrays and saves)
                    for element in field_result:
                        ifeq.append(element)  # type: ignore
                else:
                    ifeq.append(field_result)  # type: ignore
            result.append(ifeq)
        return result


class XMLPacket:
    """Represents a packet in XML"""
    def __init__(self, packet_id: str, description: str, fields: List[XMLField]) -> None:
        self.packet_id = packet_id
        self.description = description
        self.fields = fields

    def to_xml(self, indent: str = "") -> Element:
        """Convert to XML element"""
        root = Element("packet")
        root.set("type", self.packet_id)
        root.set("desc", self.description)

        for field in self.fields:
            result = field.to_xml(indent + "\t")
            if isinstance(result, list):
                # Handle fields that return multiple elements (unions and saves)
                for element in result:
                    root.append(element)  # type: ignore
            else:
                root.append(result)  # type: ignore

        return root


class XMLRenderer:
    """Renders packets to XML format"""
    def __init__(self, output_file: str) -> None:
        self.output_file = output_file

    def render(self, s2c_packets: List[Packet], c2s_packets: List[Packet]) -> None:
        """Render the XML file"""
        root = Element("root")

        # Add standard elements
        SubElement(root, "version").set("client", "")
        SubElement(root, "templates")
        SubElement(root, "tools")

        # Add rule section
        rule = SubElement(root, "rule")
        server = SubElement(rule, "server")
        server.set("port", "0")
        server.set("name", "Game")
        SubElement(rule, "decryptor").set("name", "")

        # Add s2c section
        s2c = SubElement(rule, "s2c")
        for packet in s2c_packets:
            s2c.append(self._process_packet(packet).to_xml("\t\t"))

        # Add c2s section
        c2s = SubElement(rule, "c2s")
        for packet in c2s_packets:
            c2s.append(self._process_packet(packet).to_xml("\t\t"))

        # Write to file
        xml_str = tostring(root, encoding='unicode')
        pretty_xml = minidom.parseString(xml_str).toprettyxml(indent="\t")
        with open(self.output_file, 'w', encoding='utf-8') as f:
            f.write(pretty_xml)

    def _process_packet(self, packet: Packet) -> XMLPacket:
        """Process a packet into XML format"""
        fields = []
        for field in packet.fields:
            # Skip packet header fields (id, size, sync)
            if isinstance(field, StructField) and field.name not in ["id", "size", "sync"]:
                fields.append(self._convert_field(field))
        return XMLPacket(packet.id, packet.name, fields)

    def _convert_field(self, field: StructField) -> XMLField:
        """Convert a field to its XML representation"""
        # Handle union fields
        if field.is_union_type():
            # Get the discriminator field name from the hints or from the variant name prefix
            if field.union_variants:
                # Extract discriminator from the first variant name (e.g., "Mode_2" -> "Mode")
                first_variant = field.union_variants[0].name
                discriminator = first_variant.split("_")[0]
                discriminator = field.hints.get("discriminator", discriminator) if field.hints else discriminator

                cases = {}
                for variant in field.union_variants:
                    processed_fields = []
                    for variant_field in variant.fields:
                        if isinstance(variant_field, StructField):
                            processed_fields.append(self._convert_field(variant_field))
                    # Extract case number from variant name
                    case_value = variant.name.split("_")[-1]
                    cases[case_value] = processed_fields
                return UnionField(discriminator, cases)

        # Handle struct arrays - create an array field that contains an echo field
        if field.is_custom_type() and field.array_size is not None and field.array_size > 0:
            expanded_fields = field.get_expanded_fields()
            if expanded_fields and not isinstance(expanded_fields, dict):
                processed_fields = []
                for expanded_field in expanded_fields:
                    if isinstance(expanded_field, StructField):
                        processed_fields.append(self._convert_field(expanded_field))
                    elif isinstance(expanded_field, BitField):
                        # Only include bits if not -1
                        bits = None if expanded_field.bits == -1 else expanded_field.bits
                        processed_fields.append(DataField(expanded_field.name, "bitval", bits))
                if processed_fields:
                    # Create an array field that wraps an echo field
                    return ArrayField(field.name, "struct", field.array_size, None, None, processed_fields)

        # Handle struct groups
        if field.is_custom_type() and not field.is_enum and not field.array_size:
            expanded_fields = field.get_expanded_fields()
            if expanded_fields and not isinstance(expanded_fields, dict):
                processed_fields = []
                for expanded_field in expanded_fields:
                    if isinstance(expanded_field, StructField):
                        processed_fields.append(self._convert_field(expanded_field))
                    elif isinstance(expanded_field, BitField):
                        # Only include bits if not -1
                        bits = None if expanded_field.bits == -1 else expanded_field.bits
                        processed_fields.append(DataField(expanded_field.name, "bitval", bits))
                if processed_fields:
                    return EchoField(field.name, processed_fields)

        # Handle bit fields
        if isinstance(field, BitField):
            # Only include bits if not -1
            bits = None if field.bits == -1 else field.bits
            return DataField(field.name, "bitval", bits, None, None, None)

        # Handle basic fields
        xml_type = self._determine_xml_type(field)
        # Preserve the @ prefix from the original save hints
        save_hints = field.hints.get("save", []) if field.hints else None
        if isinstance(save_hints, str):
            save_hints = [save_hints]
        array_size = field.array_size if field.array_size is not None and field.array_size > 0 else None
        lookup = field.hints.get("lookup") if field.hints else None

        # For arrays, get the base type
        base_type = None
        if array_size is not None and array_size > 0:
            # Handle char arrays (strings) as text fields
            if field.base_type == "char":
                return DataField(field.name, "t", None, array_size, lookup, save_hints, None)

            # Handle other arrays
            base_type = self._map_type(field.base_type)
            if base_type is None:
                raise ValueError(f"Unknown base type: {field.base_type} for field {field.name}")
            xml_type = "a"

        # Handle bit fields at the top level
        if hasattr(field, 'bits') and field.bits is not None:
            # Only include bits if not -1
            bits = None if field.bits == -1 else field.bits
            return DataField(field.name, "bitval" if bits is not None else xml_type, bits, array_size, lookup, save_hints, base_type)

        return DataField(field.name, xml_type, None, array_size, lookup, save_hints, base_type)

    def _determine_xml_type(self, field: StructField) -> str:
        """Determine the XML type for a field"""
        # Handle explicit type hints
        if field.hints and "type" in field.hints:
            return field.hints["type"]

        # Handle arrays
        if field.array_size is not None and field.array_size > 0:
            return "t" if field.base_type == "char" else "a"

        # Handle direction fields
        if field.name == "dir":
            return "dir"

        # Handle enums
        if field.is_enum:
            if field.enum_type:
                mapped_type = self._map_type(field.enum_type)
                if mapped_type is None:
                    # Default to uint32 if we can't determine the enum's underlying type
                    return "uint32"
                return mapped_type
            return "uint32"  # Default for enums without explicit type

        field_type = field.type if hasattr(field, "type") else field.base_type
        mapped_type = self._map_type(field_type)
        if mapped_type is None:
            # For enums, try to extract the underlying type from the field_type string
            if field_type.startswith("enum "):
                return "uint32"  # Default for enums without explicit type
            raise ValueError(f"Unknown type: {field_type} for field {field.name}")
        return mapped_type

    def _map_type(self, type_name: str) -> Optional[str]:
        """Map C types to XML types"""
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
            "unsigned int": "uint32",
            "unsigned short": "uint16",
            "unsigned char": "byte",
            "unsigned long": "uint64",
            "long long": "int64",
        }
        return type_map.get(type_name)