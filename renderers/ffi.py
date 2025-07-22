from typing import List, Set
from packets import Packet
from fields import StructField
import os


class FFIRenderer:
    """Generates LuaJIT FFI definitions for packet structures"""

    def __init__(self, c2s_filename: str, s2c_filename: str):
        self.c2s_filename = c2s_filename
        self.s2c_filename = s2c_filename
        self.defined_structs: Set[str] = set()

    def render(self, c2s_packets: List[Packet], s2c_packets: List[Packet]):
        """Render both C2S and S2C FFI definitions"""
        self._render_file(self.c2s_filename, c2s_packets, "c2s")
        self._render_file(self.s2c_filename, s2c_packets, "s2c")

    def _render_file(self, filename: str, packets: List[Packet], packet_type: str):
        """Render a single FFI definition file"""
        # Create directory if it doesn't exist
        os.makedirs(os.path.dirname(filename), exist_ok=True)
        
        # Reset defined structs for each file
        self.defined_structs.clear()
        
        lines = [
            "local ffi = require('ffi')",
            "",
            "-- Auto-generated LuaJIT FFI definitions",
            "-- Do not edit manually",
            "",
            "ffi.cdef[["
        ]

        # First pass: collect and render all custom structs
        struct_definitions = []
        for packet in packets:
            struct_definitions.extend(self._collect_struct_definitions(packet))

        # Add struct definitions
        lines.extend(struct_definitions)
        
        # Add packet definitions
        for packet in packets:
            lines.extend(self._render_packet_struct(packet))

        lines.extend([
            "]]",
            "",
            f"-- Packet constructors for {packet_type.upper()}",
            f"local {packet_type} = {{}}"
        ])

        # Add packet constructors
        for packet in packets:
            packet_name = packet.name
            lines.append(f"{packet_type}.{packet_name} = function() return ffi.new('{packet_name}') end")

        lines.extend([
            "",
            f"return {packet_type}"
        ])

        with open(filename, 'w') as f:
            f.write('\n'.join(lines))

    def _collect_struct_definitions(self, packet: Packet) -> List[str]:
        """Collect all custom struct definitions needed for this packet"""
        definitions = []
        
        for field in packet.fields:
            definitions.extend(self._collect_field_structs(field))
        
        return definitions

    def _collect_field_structs(self, field: StructField) -> List[str]:
        """Recursively collect struct definitions from a field"""
        definitions = []
        
        # Handle nested structures
        if field.has_nested_fields and not field.is_primitive:
            struct_name = self._get_clean_struct_name(field.base_type)
            if struct_name not in self.defined_structs:
                self.defined_structs.add(struct_name)
                definitions.extend(self._render_custom_struct(struct_name, field))
                
                # Recursively collect from nested fields
                for nested_field in field.nested_fields:
                    definitions.extend(self._collect_field_structs(nested_field))

        # Handle union variants
        if field.has_variants:
            for variant in field.union_variants:
                variant_name = variant.name
                if variant_name not in self.defined_structs:
                    self.defined_structs.add(variant_name)
                    definitions.extend(self._render_variant_struct(variant_name, variant.fields))
                    
                    # Recursively collect from variant fields
                    for variant_field in variant.fields:
                        definitions.extend(self._collect_field_structs(variant_field))

        return definitions

    def _render_packet_struct(self, packet: Packet) -> List[str]:
        """Render a packet as an FFI struct definition"""
        lines = [f"typedef struct {packet.name} {{"]
        
        for field in packet.fields:
            lines.extend(self._render_ffi_field(field, "    "))
        
        lines.extend([f"}} {packet.name};", ""])
        return lines

    def _render_custom_struct(self, struct_name: str, field: StructField) -> List[str]:
        """Render a custom struct definition"""
        lines = [f"typedef struct {struct_name} {{"]
        
        if field.has_nested_fields:
            for nested_field in field.nested_fields:
                lines.extend(self._render_ffi_field(nested_field, "    "))
        
        lines.extend([f"}} {struct_name};", ""])
        return lines

    def _render_variant_struct(self, variant_name: str, fields: List[StructField]) -> List[str]:
        """Render a union variant struct definition"""
        lines = [f"typedef struct {variant_name} {{"]
        
        for field in fields:
            lines.extend(self._render_ffi_field(field, "    "))
        
        lines.extend([f"}} {variant_name};", ""])
        return lines

    def _render_ffi_field(self, field: StructField, indent: str) -> List[str]:
        """Render a single field for FFI struct definition"""
        lines = []
        
        if field.is_union:
            # Handle union fields
            lines.append(f"{indent}union {{")
            if field.has_variants:
                for variant in field.union_variants:
                    lines.append(f"{indent}    {variant.name} {variant.name.lower()};")
            lines.append(f"{indent}}} {field.name};")
        elif field.has_nested_fields:
            # Handle nested structures
            struct_type = self._get_clean_struct_name(field.base_type)
            if field.is_array:
                lines.append(f"{indent}{struct_type} {field.name}[{field.array_size}];")
            else:
                lines.append(f"{indent}{struct_type} {field.name};")
        else:
            # Handle primitive fields
            ffi_type = self._map_to_ffi_type(field)
            if field.is_array:
                lines.append(f"{indent}{ffi_type} {field.name}[{field.array_size}];")
            else:
                lines.append(f"{indent}{ffi_type} {field.name};")
        
        return lines

    def _map_to_ffi_type(self, field: StructField) -> str:
        """Map C types to FFI-compatible types"""
        base_type = field.base_type.lower().strip()
        
        # Handle specific type mappings
        type_mappings = {
            'char': 'char',
            'signed char': 'int8_t',
            'unsigned char': 'uint8_t',
            'short': 'int16_t',
            'unsigned short': 'uint16_t',
            'signed short': 'int16_t',
            'int': 'int32_t',
            'unsigned int': 'uint32_t',
            'signed int': 'int32_t',
            'long': 'int32_t',
            'unsigned long': 'uint32_t',
            'signed long': 'int32_t',
            'long long': 'int64_t',
            'unsigned long long': 'uint64_t',
            'signed long long': 'int64_t',
            'float': 'float',
            'double': 'double',
            'uint8_t': 'uint8_t',
            'uint16_t': 'uint16_t', 
            'uint32_t': 'uint32_t',
            'uint64_t': 'uint64_t',
            'int8_t': 'int8_t',
            'int16_t': 'int16_t',
            'int32_t': 'int32_t',
            'int64_t': 'int64_t'
        }
        
        return type_mappings.get(base_type, base_type)

    def _get_clean_struct_name(self, base_type: str) -> str:
        """Convert struct base_type to clean struct name"""
        clean_name = base_type.replace('struct ', '').replace('union ', '')
        if clean_name.startswith('_'):
            clean_name = clean_name[1:]  # Remove leading underscore
        return clean_name