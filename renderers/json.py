from typing import List
from packets import Packet
from dataclasses import asdict
import json
import os


class JsonRenderer:
    def __init__(self, filename):
        self.filename = filename

    def render(self, packets: List[Packet]):
        # Create directory if it doesn't exist
        os.makedirs(os.path.dirname(self.filename), exist_ok=True)
        
        packets_dict = [asdict(packet) for packet in packets]

        with open(self.filename, 'w') as f:
            json.dump(packets_dict, f, indent=2)

