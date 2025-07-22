# XiPackets-definitions

XiPackets definitions in various formats, ready to be used for various programs and addons.
- Lua definitions for Ashita addons
- Lua FFI definitions
- JSON definitions
- VieweD XML definitions

All credits [atom0s](https://github.com/atom0s/XiPackets/tree/main)

## Warning
- Not all packets are entirely defined in `XiPackets`.
- Not all packets are correctly defined in this project.
- Structures may slightly differ compared to `XiPackets` documentation but if possible it has only been done to break down several bitmaps into a structure that's easier to understand.

## Getting started
Download the [latest release](https://github.com/sruon/XiPackets-definitions/releases) and place the files in the relevant location for your program.

## Use with VieweD

Decompress the content of the `viewed` folder into your `VieweD` installation in the `data\ffxi` folder.

## Use with Lua

```lua
local c2s = require('c2s.lua')
```

## Custom notations
Mostly to tell VieweD how to handle specific fields.
### Unions
When a packet can take several different forms based on a field value, the variants can be specified as such:
```cpp
  union data {
    _GP_SERV_COMMAND_RECIPE_Type_1 Type_1;
    _GP_SERV_COMMAND_RECIPE_Type_2 Type_2;
    _GP_SERV_COMMAND_RECIPE_Type_3 Type_3;
  };
  uint16_t Type;
```
Each possible structure should be defined in the union, with a name following the format `<DISCRIMINATOR>_<VALUE>`. 

For example, `Type_1` indicates this structure is to be used if `Type` is equal to 1.
Note this doesn't support bitwise discriminators, only full values.

### Custom type for field
Tell VieweD to use a specific rendering type for a field.

Prefer breaking down the field into a struct defining the subfields if possible.
```cpp
uint32_t Flags; // type="bits" bits="32"
```
### Lookup tables
Tell VieweD to find the value in a lookup table.
```cpp
uint16_t PetActIndex; // lookup="@actindex"
```

### Save lookups
Tell VieweD to save the value in a lookup table.
Format: `save="@lookupname"`
Multiple lookup tables can be specified.

```cpp
uint32_t UniqueNo; // lookup="@uniqueno"
uint16_t ActIndex; // lookup="@actindex"
char name[16]; // save="@UniqueNo" save="@ActIndex"
```

## Contributing
`XiPackets` is the only acceptable source of truth.

If you find a packet that you feel is not correctly defined, please double check the `XiPackets` project first and open an issue there. 

If the structures in this project are wrong, feel free to open an issue or a pull request.

## Notes
- Certain structures may have been slightly modified when compared to the `XiPackets` project, to ease the parsing.
- Packets with no names in the `XiPackets` project have been given relatively meaningful name.
