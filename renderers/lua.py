from typing import List
from packet import Packet
import jinja2

class LuaRenderer:
    def __init__(self, filename):
        self.template = jinja2.Environment(loader=jinja2.FileSystemLoader('renderers/templates')).get_template('lua.j2')
        self.filename = filename

    def render(self, packets: List[Packet]):
        with open(self.filename, 'w') as f:
            lua_code = self.template.render(packets=packets)
            f.write(lua_code)
        print(f"Generated {self.filename} with {len(packets)} packets.")

