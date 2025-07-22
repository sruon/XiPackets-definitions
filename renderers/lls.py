from typing import List
from packets import Packet
from fields import StructField
import os


class LLSRenderer:
    """Generates Lua Language Server definition files (.d.lua) for packet structures"""

    def __init__(self, c2s_filename: str, s2c_filename: str):
        self.c2s_filename = c2s_filename
        self.s2c_filename = s2c_filename
        self.custom_structs = {}  # Track unique custom struct types: name -> field

    def render(self, c2s_packets: List[Packet], s2c_packets: List[Packet]):
        """Render both C2S and S2C packet definitions"""
        self._render_file(self.c2s_filename, c2s_packets)
        self._render_file(self.s2c_filename, s2c_packets)

    def _render_file(self, filename: str, packets: List[Packet]):
        """Render a single definition file"""
        # Create directory if it doesn't exist
        os.makedirs(os.path.dirname(filename), exist_ok=True)

        # First pass: collect all custom struct types
        self.custom_structs.clear()
        for packet in packets:
            self._collect_custom_structs(packet)

        lines = [
            "---@meta",
            "",
            "-- Auto-generated Lua Language Server definitions",
            "-- Do not edit manually",
            ""
        ]

        # Render custom struct definitions first
        for struct_name in sorted(self.custom_structs.keys()):
            field = self.custom_structs[struct_name]
            lines.extend(self._render_custom_struct(struct_name, field))
            lines.append("")

        # Then render packet definitions
        for packet in packets:
            lines.extend(self._render_packet(packet))
            lines.append("")

        with open(filename, 'w') as f:
            f.write('\n'.join(lines))

    def _render_packet(self, packet: Packet) -> List[str]:
        """Render a single packet as a Lua class definition"""
        lines = [f"---@class {packet.name}"]

        for field in packet.fields:
            lines.extend(self._render_field_annotation(field))

        return lines

    def _render_field_annotation(self, field: StructField) -> List[str]:
        """Render field annotations for LLS"""
        lines = []

        if field.is_union:
            # Handle union fields
            lines.append(f"---@field {field.name} {self._get_union_type(field)}")
        elif field.has_nested_fields:
            # Handle nested structures
            nested_type = self._get_clean_struct_name(field.base_type)
            if field.is_array:
                lines.append(f"---@field {field.name} {nested_type}[]")
            else:
                lines.append(f"---@field {field.name} {nested_type}")
        else:
            # Handle primitive fields
            lua_type = self._map_type_to_lua(field)
            lines.append(f"---@field {field.name} {lua_type}")

        return lines

    def _map_type_to_lua(self, field: StructField) -> str:
        """Map C types to Lua types"""
        if field.is_array:
            element_type = self._get_primitive_lua_type(field.base_type)
            if field.base_type in ['char', 'signed char', 'unsigned char'] and field.array_size:
                # Treat char arrays as strings
                return "string"
            return f"{element_type}[]"

        return self._get_primitive_lua_type(field.base_type)

    def _get_primitive_lua_type(self, c_type: str) -> str:
        """Convert C primitive types to Lua types"""
        c_type = c_type.lower().strip()

        # Integer types
        if any(t in c_type for t in ['char', 'short', 'int', 'long', 'uint', 'int8', 'int16', 'int32', 'int64']):
            return "integer"

        # Floating point types
        if any(t in c_type for t in ['float', 'double']):
            return "number"

        # String types (handled by caller for arrays)
        if c_type in ['char*', 'string']:
            return "string"

        # Default to table for complex types
        return "table"

    def _get_union_type(self, field: StructField) -> str:
        """Generate union type annotation"""
        if not field.has_variants:
            return "table"

        # Create a union of all possible variant types
        variant_types = []
        for variant in field.union_variants:
            variant_type = f"{variant.name}"
            variant_types.append(variant_type)

        if variant_types:
            return " | ".join(variant_types)

        return "table"

    def _collect_custom_structs(self, packet: Packet):
        """Collect all custom struct types from a packet"""
        for field in packet.fields:
            self._collect_custom_structs_from_field(field)

    def _collect_custom_structs_from_field(self, field: StructField):
        """Recursively collect custom struct types from a field"""
        # If this field has nested fields, it's a custom struct
        if field.has_nested_fields and not field.is_primitive:
            struct_name = self._get_clean_struct_name(field.base_type)
            self.custom_structs[struct_name] = field

            # Recursively collect from nested fields
            for nested_field in field.nested_fields:
                self._collect_custom_structs_from_field(nested_field)

        # Also collect from union variants
        if field.has_variants:
            for variant in field.union_variants:
                # Add the variant itself as a custom struct
                variant_name = variant.name
                # Create a pseudo-field to represent the variant structure
                variant_struct_field = StructField(
                    name=variant_name,
                    type_name=f"struct {variant_name}",
                    bits=0,
                    signed=False,
                    size_bytes=0,
                    base_type=f"struct {variant_name}",
                    array_size=None,
                    hints=None,
                    is_enum=False,
                    enum_underlying_type=None,
                    is_union=False,
                    nested_fields=variant.fields,
                    union_variants=None,
                    discriminator_field=None
                )
                self.custom_structs[variant_name] = variant_struct_field

                # Recursively collect from variant fields
                for variant_field in variant.fields:
                    self._collect_custom_structs_from_field(variant_field)

    def _get_clean_struct_name(self, base_type: str) -> str:
        """Convert struct base_type to clean class name"""
        # Remove 'struct ' prefix and clean up underscores
        clean_name = base_type.replace('struct ', '').replace('union ', '')
        if clean_name.startswith('_'):
            clean_name = clean_name[1:]  # Remove leading underscore
        return clean_name

    def _render_custom_struct(self, struct_name: str, field: StructField) -> List[str]:
        """Render a custom struct definition"""
        lines = [f"---@class {struct_name}"]

        if field.has_nested_fields:
            for nested_field in field.nested_fields:
                lines.extend(self._render_field_annotation(nested_field))

        return lines
