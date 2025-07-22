from typing import List
from packets import Packet
import os


class ViewedLookupRenderer:
    """Generates lookup files for Viewed packet analysis tool"""

    def __init__(self, c2s_filename: str, s2c_filename: str):
        self.c2s_filename = c2s_filename
        self.s2c_filename = s2c_filename

    def render(self, c2s_packets: List[Packet], s2c_packets: List[Packet]):
        """Render both C2S and S2C lookup files"""
        self._render_file(self.c2s_filename, c2s_packets)
        self._render_file(self.s2c_filename, s2c_packets)

    def _render_file(self, filename: str, packets: List[Packet]):
        """Render a single lookup file"""
        # Create directory if it doesn't exist
        os.makedirs(os.path.dirname(filename), exist_ok=True)

        lines = []
        for packet in packets:
            # Format: 0xXXX;PACKET_NAME;Undocumented
            line = f"{packet.id};{packet.name};Undocumented"
            lines.append(line)

        with open(filename, 'w') as f:
            f.write('\n'.join(lines))
