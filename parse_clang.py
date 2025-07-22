import clang.cindex as clang

from renderers.json import JsonRenderer
from renderers.lua import LuaRenderer
from renderers.lls import LLSRenderer
from renderers.ffi import FFIRenderer
from renderers.viewed.xml_builder import XMLRenderer
from renderers.viewed.lookup_renderer import ViewedLookupRenderer
from packets import Packet

index = clang.Index.create()


def parse_header(filename, match):
    res = []

    tu = index.parse(filename, args=['-std=c99'])
    for cursor in tu.cursor.walk_preorder():
        if cursor.kind == getattr(clang.CursorKind, 'STRUCT_DECL'):
            struct_name = cursor.spelling
            if struct_name.startswith(match) and "_COMMAND_" in struct_name:
                packet = Packet.from_cursor(cursor)
                res.append(packet)
    return res


if __name__ == "__main__":
    c2s_packets = parse_header('./definitions/c2s.h', 'GP_CLI')
    s2c_packets = parse_header('./definitions/s2c.h', 'GP_SERV')

    # Render .lua files
    lua_renderer = LuaRenderer('./generated/c2s.lua')
    lua_renderer.render(c2s_packets)

    lua_renderer = LuaRenderer('./generated/s2c.lua')
    lua_renderer.render(s2c_packets)

    json_renderer = JsonRenderer('./generated/c2s.json')
    json_renderer.render(c2s_packets)

    json_renderer = JsonRenderer('./generated/s2c.json')
    json_renderer.render(s2c_packets)

    # Render LLS definition files
    lls_renderer = LLSRenderer('./generated/c2s.d.lua', './generated/s2c.d.lua')
    lls_renderer.render(c2s_packets, s2c_packets)

    # Render LuaJIT FFI definition files
    ffi_renderer = FFIRenderer('./generated/c2s.ffi.lua', './generated/s2c.ffi.lua')
    ffi_renderer.render(c2s_packets, s2c_packets)

    # Render Viewed format lookup files
    lookup_renderer = ViewedLookupRenderer('./generated/viewed/lookup/out.txt', './generated/viewed/lookup/in.txt')
    lookup_renderer.render(c2s_packets, s2c_packets)

    # Render Viewed XML file using our new renderer
    xml_renderer = XMLRenderer('./generated/viewed/rules/ffxi.xml')
    xml_renderer.render(s2c_packets, c2s_packets)
