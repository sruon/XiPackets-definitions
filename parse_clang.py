import clang.cindex as clang

from renderers.lua import LuaRenderer
from renderers.viewed import ViewedRenderer
from renderers.xml_builder import XMLRenderer  # Import our new renderer
from packet import Packet

index = clang.Index.create()


def parse_header(filename, match):
    res = []

    tu = index.parse(filename, args=['-std=c99'])
    for cursor in tu.cursor.walk_preorder():
        if cursor.kind == getattr(clang.CursorKind, 'STRUCT_DECL'):
            struct_name = cursor.spelling
            if struct_name.startswith(match) and "_COMMAND_" in struct_name:
                packet = Packet(cursor)
                res.append(packet)
    return res


if __name__ == "__main__":
    c2s_packets = parse_header('./definitions/c2s.h', 'GP_CLI')
    s2c_packets = parse_header('./definitions/s2c.h', 'GP_SERV')

    # Render .lua files
    lua_renderer = LuaRenderer('./generated/lua/c2s.lua')
    lua_renderer.render(c2s_packets)

    lua_renderer = LuaRenderer('./generated/lua/s2c.lua')
    lua_renderer.render(s2c_packets)

    # Render Viewed format lookup files
    viewed_renderer = ViewedRenderer('./generated/viewed/lookup/out.txt')
    viewed_renderer.render(c2s_packets)

    viewed_renderer = ViewedRenderer('./generated/viewed/lookup/in.txt')
    viewed_renderer.render(s2c_packets)

    # Render FFXI XML file using our new renderer
    xml_renderer = XMLRenderer('./generated/viewed/rules/ffxi.xml')
    xml_renderer.render(s2c_packets, c2s_packets)
