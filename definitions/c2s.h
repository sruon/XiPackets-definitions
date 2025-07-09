#include "c2s.types.h"

/// 0x000A
struct GP_CLI_COMMAND_LOGIN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t LoginPacketCheck;
  uint8_t padding00;
  uint16_t unknown00;
  uint32_t unknown01;
  uint32_t UniqueNo;
  uint16_t GrapIDTbl[9];
  char sName[15];
  char sAccount[15];
  uint8_t Ticket[16];
  uint32_t Ver;
  uint8_t sPlatform[4];
  uint16_t uCliLang;
  uint16_t dammyArea;
};

/// 0x000B
struct GP_CLI_COMMAND_LOGOUT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ZoneNo; // lookup="zones"
  uint32_t MapNo;
  int32_t x;
  int32_t y;
  int32_t z;
  uint16_t State;
  uint8_t padding00;
  uint8_t dir;
};

/// 0x000C
struct GP_CLI_COMMAND_GAMEOK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ClientState;
  uint32_t DebugClientFlg : 1;
  uint32_t unused : 31;
};

/// 0x000D
struct GP_CLI_COMMAND_NETEND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t State;
  uint16_t padding00;
};

/// 0x000F
struct GP_CLI_COMMAND_CLSTAT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t stat[8];
};

/// 0x0011
struct GP_CLI_COMMAND_ZONE_IN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00;
  uint8_t unknown01;
};

/// 0x0015
struct GP_CLI_COMMAND_POS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  float x;
  float z;
  float y;
  uint16_t MovTime;
  uint16_t MoveFlame;
  int8_t dir;
  uint8_t TargetMode : 1;
  uint8_t RunMode : 1;
  uint8_t GroundMode : 1;
  uint8_t unused : 5;
  uint16_t facetarget;
  uint32_t TimeNow;
  uint32_t padding00;
};

/// 0x0016
struct GP_CLI_COMMAND_CHARREQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0017
struct GP_CLI_COMMAND_CHARREQ2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ActIndex;
  uint16_t padding00;
  uint32_t UniqueNo2;
  uint32_t UniqueNo3;
  uint16_t Flg;
  uint16_t Flg2;
};

/// 0x001A
struct GP_CLI_COMMAND_ACTION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t ActionID;
  uint32_t ActionBuf[4];
};

/// 0x001B
struct GP_CLI_COMMAND_FRIENDPASS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Para;
  uint16_t padding00;
};

/// 0x001C
struct GP_CLI_COMMAND_UNKNOWN_PET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t unknown00;
  uint16_t padding00;
  uint32_t unknown01;
};

/// 0x001E
struct GP_CLI_COMMAND_GM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Command[128];
};

/// 0x001F
struct GP_CLI_COMMAND_GMCOMMAND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t GMUniqueNo;
  uint8_t Command[128];
};

/// 0x0028
struct GP_CLI_COMMAND_ITEM_DUMP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint8_t Category;
  uint8_t ItemIndex;
};

/// 0x0029
struct GP_CLI_COMMAND_ITEM_MOVE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint8_t Category1;
  uint8_t Category2;
  uint8_t ItemIndex1;
  uint8_t ItemIndex2;
};

/// 0x002A
struct GP_CLI_COMMAND_ITEM_ATTR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Category;
  uint8_t ItemIndex;
};

/// 0x002B
struct GP_CLI_COMMAND_TRANSLATE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t FromIndex;
  uint8_t ToIndex;
  uint16_t padding00;
  uint8_t Name[64];
};

/// 0x002C
struct GP_CLI_COMMAND_ITEMSEARCH {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Language;
  uint8_t padding00[3];
  uint8_t Name[64];
};

/// 0x0032
struct GP_CLI_COMMAND_ITEM_TRADE_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0033
struct GP_CLI_COMMAND_ITEM_TRADE_RES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Kind;
  uint16_t TradeCounter;
};

/// 0x0034
struct GP_CLI_COMMAND_ITEM_TRADE_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo; // lookup="items"
  uint8_t ItemIndex;
  uint8_t TradeIndex;
};

/// 0x0035
struct GP_CLI_COMMAND_ITEM_PRESENT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Index;
  uint8_t ReqID;
  uint8_t TakeFlg;
};

/// 0x0036
struct GP_CLI_COMMAND_ITEM_TRANSFER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t ItemNumTbl[10];
  uint8_t PropertyItemIndexTbl[10];
  uint16_t ActIndex;
  uint8_t ItemNum;
  uint8_t padding00[3];
};

/// 0x0037
struct GP_CLI_COMMAND_ITEM_USE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t ItemNum;
  uint16_t ActIndex;
  uint8_t PropertyItemIndex;
  uint8_t padding00;
  uint32_t Category; // lookup="containers"
};

/// 0x0038
struct GP_CLI_COMMAND_ITEM_MAKE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo; // lookup="items"
  uint16_t padding00;
};

/// 0x0039
struct GP_CLI_COMMAND_ITEM_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x003A
struct GP_CLI_COMMAND_ITEM_STACK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Category; // lookup="containers"
};

/// 0x003B
struct GP_CLI_COMMAND_MANNEQUIN_SET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Kind;
  uint32_t Category1;
  uint8_t ItemIndex1;
  uint8_t ContainerIndex;
  uint16_t padding00;
  uint32_t Category2;
  uint8_t ItemIndex2;
  uint8_t padding01[3];
  uint32_t unknown00;
  uint8_t unknown01;
  uint8_t padding02[3];
};

/// 0x003C
struct GP_CLI_COMMAND_BLACK_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t unknown00;
  uint32_t unknown01;
  uint32_t unknown02;
  uint32_t unknown03;
  uint32_t unknown04;
  uint8_t unknown05;
  uint8_t padding00[3];
};

/// 0x003D
struct GP_CLI_COMMAND_BLACK_EDIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  SAVE_BLACK Data;
  int8_t Mode;
  uint8_t padding00[3];
};

/// 0x0041
struct GP_CLI_COMMAND_TROPHY_ENTRY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t TrophyItemIndex;
  uint8_t PropertyItemIndex;
  uint8_t padding00[2];
};

/// 0x0042
struct GP_CLI_COMMAND_TROPHY_ABSENCE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t TrophyItemIndex;
  uint8_t padding00;
};

/// 0x004B
struct GP_CLI_COMMAND_FRAGMENTS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Command;
  int8_t Result;
  uint8_t value1;
  uint8_t value2;
  int32_t timestamp;
  int32_t size_total;
  int32_t offset;
  int32_t data_size;
};

/// 0x004D
struct GP_CLI_COMMAND_PBX {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Command;
  int8_t BoxNo;
  int8_t PostWorkNo;
  int8_t ItemWorkNo;
  int32_t ItemStacks;
  int8_t Result;
  int8_t ResParam1;
  int8_t ResParam2;
  int8_t ResParam3;
  uint8_t TargetName[16];
};

/// 0x004E
struct GP_CLI_COMMAND_AUC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0050
struct GP_CLI_COMMAND_EQUIP_SET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t PropertyItemIndex;
  uint8_t EquipKind;
  uint8_t Category;
};

/// 0x0051
struct GP_CLI_COMMAND_EQUIPSET_EQUIP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Count;
  uint8_t padding00[3];
  equipsetitem_t Equipment[16];
};

/// 0x0052
struct GP_CLI_COMMAND_EQUIPSET_SET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t EquipKind;
  uint8_t padding00[3];
  equipsetrequestitem_t ItemChange;
  equipsetrequestitem_t Equipment[16];
};

/// 0x0053
struct GP_CLI_COMMAND_LOCKSTYLE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Count;
  uint8_t Mode;
  uint8_t Flags;
  uint8_t padding00;
  lockstyleitem_t Items[16];
};

/// 0x0058
struct GP_CLI_COMMAND_RECIPE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t skill;
  uint16_t level;
  uint16_t Param0;
  uint16_t Mode;
  uint16_t Param1;
  uint16_t Param2;
  uint16_t Param3;
  uint16_t Param4;
};

/// 0x0059
struct GP_CLI_COMMAND_EFFECTEND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t effectpara;
  uint8_t padding00[8];
};

/// 0x005A
struct GP_CLI_COMMAND_REQCONQUEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x005B
struct GP_CLI_COMMAND_EVENTEND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t EndPara;
  uint16_t ActIndex;
  uint16_t Mode;
  uint16_t EventNum;
  uint16_t EventPara;
};

/// 0x005C
struct GP_CLI_COMMAND_EVENTENDXZY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  float x;
  float y;
  float z;
  uint32_t UniqueNo;
  uint32_t EndPara;
  uint16_t EventNum;
  uint16_t EventPara;
  uint16_t ActIndex;
  uint8_t Mode;
  int8_t dir;
};

/// 0x005D
struct GP_CLI_COMMAND_MOTION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Number;
  uint8_t Mode;
  uint16_t Param;
  uint16_t padding00;
};

/// 0x005E
struct GP_CLI_COMMAND_MAPRECT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t RectID;
  float x;
  float y;
  float z;
  uint16_t ActIndex;
  uint8_t MyRoomExitBit;
  uint8_t MyRoomExitMode;
};

/// 0x0060
struct GP_CLI_COMMAND_PASSWARDS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t padding00;
  uint8_t String[16];
};

/// 0x0061
struct GP_CLI_COMMAND_CLISTATUS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00;
  uint8_t padding00;
};

/// 0x0063
struct GP_CLI_COMMAND_DIG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t para;
  uint16_t ActIndex;
  uint8_t mode;
  uint8_t padding00;
};

/// 0x0064
struct GP_CLI_COMMAND_SCENARIOITEM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t LookItemFlag[16];
  uint16_t ActIndex;
  uint16_t TableIndex;
};

/// 0x006E
struct GP_CLI_COMMAND_GROUP_SOLICIT_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Kind;
  uint8_t padding00;
};

/// 0x006F
struct GP_CLI_COMMAND_GROUP_LEAVE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
};

/// 0x0070
struct GP_CLI_COMMAND_GROUP_BREAKUP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
};

/// 0x0071
struct GP_CLI_COMMAND_GROUP_STRIKE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Kind;
  uint8_t padding00;
  uint8_t sName[15];
};

/// 0x0072
struct GP_CLI_COMMAND_GROUP_KICK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Kind;
  uint8_t padding00;
  uint8_t sName[15];
};

/// 0x0073
struct GP_CLI_COMMAND_GROUP_CHANGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Kind;
  uint8_t ChangeKind;
};

/// 0x0074
struct GP_CLI_COMMAND_GROUP_SOLICIT_RES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Res;
  uint8_t padding00;
};

/// 0x0075
struct GP_CLI_COMMAND_GROUP_TALK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t padding00;
  uint8_t Kind;
  uint8_t Attr;
  uint8_t Str[128];
};

/// 0x0076
struct GP_CLI_COMMAND_GROUP_LIST_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
};

/// 0x0077
struct GP_CLI_COMMAND_GROUP_CHANGE2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t sName[16];
  uint8_t Kind;
  uint8_t ChangeKind;
};

/// 0x0078
struct GP_CLI_COMMAND_GROUP_CHECKID {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0082
struct GP_CLI_COMMAND_SHOP_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ShopNo;
  uint8_t ShopItemOffsetIndex;
  uint8_t padding00;
};

/// 0x0083
struct GP_CLI_COMMAND_SHOP_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ShopNo;
  uint16_t ShopItemIndex;
  uint8_t PropertyItemIndex;
  uint8_t padding00[3];
};

/// 0x0084
struct GP_CLI_COMMAND_SHOP_SELL_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo; // lookup="items"
  uint8_t ItemIndex;
  uint8_t padding00;
};

/// 0x0085
struct GP_CLI_COMMAND_SHOP_SELL_SET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t SellFlag;
};

/// 0x008C
struct GP_CLI_COMMAND_PREFERENCE_READ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t padding00;
};

/// 0x008D
struct GP_CLI_COMMAND_PREFERENCE_SAVE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t ContentLen;
  int32_t SegmentIndex;
  char PreferenceData[50];
  char SendDone;
};

/// 0x0096
struct GP_CLI_COMMAND_COMBINE_ASK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t HashNo;
  uint8_t padding00;
  uint16_t Crystal;
  uint8_t CrystalIdx;
  uint8_t Items;
  uint16_t ItemNo[8]; // lookup="items"
  uint8_t TableNo[8];
};

/// 0x009B
struct GP_CLI_COMMAND_CHOCOBO_RACING {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Param;
  uint32_t Kind;
};

/// 0x00A0
struct GP_CLI_COMMAND_SWITCH_PROPOSAL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t Str[128];
};

/// 0x00A1
struct GP_CLI_COMMAND_SWITCH_VOTE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Index;
  uint8_t Name[128];
};

/// 0x00A2
struct GP_CLI_COMMAND_DICE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t unknown00;
};

/// 0x00AA
struct GP_CLI_COMMAND_GUILD_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo; // lookup="items"
  uint8_t PropertyItemIndex;
  uint8_t ItemNum;
};

/// 0x00AB
struct GP_CLI_COMMAND_GUILD_BUYLIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00AC
struct GP_CLI_COMMAND_GUILD_SELL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo; // lookup="items"
  uint8_t PropertyItemIndex;
  uint8_t ItemNum;
};

/// 0x00AD
struct GP_CLI_COMMAND_GUILD_SELLLIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00B5
struct GP_CLI_COMMAND_CHAT_STD {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t unknown00;
  uint8_t Str[128];
};

/// 0x00B6
struct GP_CLI_COMMAND_CHAT_NAME {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00;
  uint8_t unknown01;
  uint8_t sName[15];
  uint8_t Mes[128];
};

/// 0x00B7
struct GP_CLI_COMMAND_ASSIST_CHANNEL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t unknown00;
  uint8_t sName[15];
  uint8_t Mes[128];
};

/// 0x00BE
struct GP_CLI_COMMAND_MERIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t Param1;
  uint16_t Param2;
  uint32_t Param3;
};

/// 0x00BF
struct GP_CLI_COMMAND_JOB_POINTS_SPEND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Index;
  uint16_t padding00;
};

/// 0x00C0
struct GP_CLI_COMMAND_JOB_POINTS_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00C3
struct GP_CLI_COMMAND_GROUP_COMLINK_MAKE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t State;
  uint8_t LinkshellId;
};

/// 0x00C4
struct GP_CLI_COMMAND_GROUP_COMLINK_ACTIVE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t r : 4;
  uint16_t g : 4;
  uint16_t b : 4;
  uint16_t a : 4;
  uint8_t ItemIndex;
  uint8_t Category; // lookup="containers"
  uint8_t ActiveFlg;
  uint8_t padding00[3];
  uint8_t sComLinkName[15];
  uint8_t LinkshellId;
};

/// 0x00C9
struct GP_CLI_COMMAND_MYROOM_ENTER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t No;
  uint16_t unknown00;
};

/// 0x00CA
struct GP_CLI_COMMAND_MYROOM_EXIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t No;
  uint16_t unknown00;
};

/// 0x00CB
struct GP_CLI_COMMAND_MYROOM_IS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t Param1;
  uint16_t Param2;
};

/// 0x00CD
struct GP_CLI_COMMAND_MYROOM_PLANT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t unknown00;
  uint16_t unknown01;
  uint8_t unknown02;
  uint8_t unknown03;
};

/// 0x00CE
struct GP_CLI_COMMAND_MYROOM_RAISE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t unknown00;
  uint16_t unknown01;
  uint8_t unknown02;
  uint8_t unknown03;
};

/// 0x00CF
struct GP_CLI_COMMAND_MYROOM_HARVEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t unknown00;
  uint16_t unknown01;
  uint8_t unknown02;
  uint8_t unknown03;
};

/// 0x00D0
struct GP_CLI_COMMAND_MYROOM_DIARY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00D1
struct GP_CLI_COMMAND_MYROOM_PLACE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo; // lookup="items"
  int8_t X;
  int8_t Y;
  int8_t Z;
  int8_t V;
  uint8_t TableNo;
  uint8_t padding00;
};

/// 0x00D2
struct GP_CLI_COMMAND_MAP_GROUP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ZoneNo; // lookup="zones"
};

/// 0x00D3
struct GP_CLI_COMMAND_FAQ_GMCALL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t type : 4;
  uint16_t vers : 4;
  uint16_t pktId : 8;
  uint16_t seq : 7;
  uint16_t eos : 1;
  uint16_t blkNum : 8;
  uint8_t Data[128];
};

/// 0x00D4
struct GP_CLI_COMMAND_FAQ_GMPARAM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Id;
  uint16_t Option;
};

/// 0x00D5
struct GP_CLI_COMMAND_ACK_GMMSG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t msgId;
  uint16_t seqId;
  uint16_t seqNum;
};

/// 0x00D8
struct GP_CLI_COMMAND_PRIVATE_DUNGEON {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ActIndex;
  uint16_t Param1;
  uint8_t Param2;
  uint8_t padding00[3];
  uint32_t UniqueNo;
  uint8_t Data[24];
};

/// 0x00DB
struct GP_CLI_COMMAND_LANGUAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00;
  uint8_t unknown01;
  uint8_t Kind;
  uint8_t padding00;
  uint32_t ConfigSys[3];
  uint32_t padding01[4];
  uint32_t Param;
};

/// 0x00DC
struct GP_CLI_COMMAND_CONFIG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t InviteFlg : 1;
  uint8_t AwayFlg : 1;
  uint8_t AnonymityFlg : 1;
  uint8_t Language : 2;
  uint8_t unused05 : 3;
  uint8_t unused08 : 1;
  uint8_t unused09 : 1;
  uint8_t unused10 : 1;
  uint8_t unused11 : 2;
  uint8_t unused13 : 1;
  uint8_t AutoTargetOffFlg : 1;
  uint8_t AutoPartyFlg : 1;
  uint8_t unused16 : 8;
  uint8_t unused24 : 1;
  uint8_t MentorFlg : 1;
  uint8_t NewAdventurerOffFlg : 1;
  uint8_t DisplayHeadOffFlg : 1;
  uint8_t unused28 : 1;
  uint8_t RecruitFlg : 1;
  uint8_t unused30 : 2;
  uint32_t unused00;
  uint32_t unused01;
  uint8_t SetFlg;
  uint8_t padding00[3];
};

/// 0x00DD
struct GP_CLI_COMMAND_EQUIP_INSPECT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t ActIndex;
  uint8_t Kind;
  uint8_t padding00[3];
};

/// 0x00DE
struct GP_CLI_COMMAND_INSPECT_MESSAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t sInspectMessage[123];
  uint8_t padding00;
};

/// 0x00E0
struct GP_CLI_COMMAND_SET_USERMSG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t sMessage[128];
  uint32_t installTime;
  uint8_t platform[4];
  uint32_t srvExCode;
  uint32_t cliExCode;
  uint32_t msgType;
};

/// 0x00E1
struct GP_CLI_COMMAND_GET_LSMSG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00 : 4;
  uint8_t unknown01 : 1;
  uint8_t unknown02 : 1;
  uint8_t unknown03 : 1;
  uint8_t unknown04 : 1;
  uint8_t readLevel : 2;
  uint8_t writeLevel : 2;
  uint8_t pubEditLevel : 2;
  uint8_t LinkshellId : 2;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t padding00[2];
  uint16_t seqId;
  uint32_t uniqNo;
  uint8_t sMessage[128];
};

/// 0x00E2
struct GP_CLI_COMMAND_SET_LSMSG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00 : 4;
  uint8_t unknown01 : 1;
  uint8_t unknown02 : 1;
  uint8_t unknown03 : 1;
  uint8_t unknown04 : 1;
  uint8_t readLevel : 2;
  uint8_t writeLevel : 2;
  uint8_t pubEditLevel : 2;
  uint8_t LinkshellId : 2;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t padding00[2];
  uint16_t seqId;
  uint32_t uniqNo;
  uint8_t sMessage[128];
};

/// 0x00E4
struct GP_CLI_COMMAND_GET_LSPRIV {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t unknown00 : 4;
  uint8_t unknown01 : 1;
  uint8_t unknown02 : 1;
  uint8_t unknown03 : 1;
  uint8_t unknown04 : 1;
  uint8_t readLevel : 2;
  uint8_t writeLevel : 2;
  uint8_t pubEditLevel : 2;
  uint8_t LinkshellId : 2;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t padding00[2];
  uint16_t seqId;
  uint32_t uniqNo;
  uint8_t sMessage[128];
};

/// 0x00E7
struct GP_CLI_COMMAND_REQLOGOUT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Mode;
  uint16_t Kind;
};

/// 0x00E8
struct GP_CLI_COMMAND_CAMP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Mode;
};

/// 0x00E9
struct GP_CLI_COMMAND_GLOBALUNIQUENO_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x00EA
struct GP_CLI_COMMAND_SIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Mode;
};

/// 0x00EB
struct GP_CLI_COMMAND_REQSUBMAPNUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00EC
struct GP_CLI_COMMAND_REQLOGOUTINFO {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x00F0
struct GP_CLI_COMMAND_RESCUE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t State;
};

/// 0x00F1
struct GP_CLI_COMMAND_BUFFCANCEL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t BuffNo;
  uint16_t padding00;
};

/// 0x00F2
struct GP_CLI_COMMAND_SUBMAPCHANGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t State;
  uint16_t SubMapNumber;
};

/// 0x00F4
struct GP_CLI_COMMAND_TRACKING_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t SendFlg;
};

/// 0x00F5
struct GP_CLI_COMMAND_TRACKING_START {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ActIndex;
};

/// 0x00F6
struct GP_CLI_COMMAND_TRACKING_END {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t padding00;
};

/// 0x00FA
struct GP_CLI_COMMAND_MYROOM_LAYOUT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomItemNo;
  uint8_t MyroomItemIndex;
  uint8_t MyroomCategory;
  uint8_t MyroomFloorFlg;
  uint8_t x;
  uint8_t y;
  uint8_t z;
  uint8_t v;
  uint8_t padding00[3];
};

/// 0x00FB
struct GP_CLI_COMMAND_MYROOM_BANKIN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomItemNo;
  uint8_t MyroomItemIndex;
  uint8_t MyroomCategory;
};

/// 0x00FC
struct GP_CLI_COMMAND_MYROOM_PLANT_ADD {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomPlantItemNo; // lookup="items"
  uint16_t MyroomAddItemNo; // lookup="items"
  uint8_t MyroomPlantItemIndex;
  uint8_t MyroomAddItemIndex;
  uint8_t MyroomPlantCategory; // lookup="containers"
  uint8_t MyroomAddCategory; // lookup="containers"
};

/// 0x00FD
struct GP_CLI_COMMAND_MYROOM_PLANT_CHECK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomPlantItemNo; // lookup="items"
  uint8_t MyroomPlantItemIndex;
  uint8_t MyroomPlantCategory; // lookup="containers"
};

/// 0x00FE
struct GP_CLI_COMMAND_MYROOM_PLANT_CROP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomPlantItemNo; // lookup="items"
  uint8_t MyroomPlantItemIndex;
  uint8_t MyroomPlantCategory; // lookup="containers"
  uint8_t CancellFlg;
  uint8_t padding00[3];
};

/// 0x00FF
struct GP_CLI_COMMAND_MYROOM_PLANT_STOP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomPlantItemNo; // lookup="items"
  uint8_t MyroomPlantItemIndex;
  uint8_t MyroomPlantCategory; // lookup="containers"
};

/// 0x0100
struct GP_CLI_COMMAND_MYROOM_JOB {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t MainJobIndex;
  uint8_t SupportJobIndex;
};

/// 0x0101
struct GP_CLI_COMMAND_MYROOM_DANCER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0102
struct GP_CLI_COMMAND_EXTENDED_JOB {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Data[160];
};

/// 0x0104
struct GP_CLI_COMMAND_BAZAAR_EXIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0105
struct GP_CLI_COMMAND_BAZAAR_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0106
struct GP_CLI_COMMAND_BAZAAR_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t BazaarItemIndex;
  uint8_t padding00[3];
  uint32_t BuyNum;
};

/// 0x0109
struct GP_CLI_COMMAND_BAZAAR_OPEN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x010A
struct GP_CLI_COMMAND_BAZAAR_ITEMSET {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t ItemIndex;
  uint8_t padding00[3];
  uint32_t Price;
};

/// 0x010B
struct GP_CLI_COMMAND_BAZAAR_CLOSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t AllListClearFlg;
};

/// 0x010C
struct GP_CLI_COMMAND_ROE_START {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ObjectiveId;
  uint16_t padding00;
};

/// 0x010D
struct GP_CLI_COMMAND_ROE_REMOVE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ObjectiveId;
  uint16_t padding00;
};

/// 0x010E
struct GP_CLI_COMMAND_ROE_CLAIM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ObjectiveId;
  uint16_t padding00;
};

/// 0x010F
struct GP_CLI_COMMAND_CURRENCIES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0110
struct GP_CLI_COMMAND_FISHING {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  int32_t para;
  uint16_t ActIndex;
  int8_t mode;
  uint8_t padding00;
  int32_t para2;
};

/// 0x0112
struct GP_CLI_COMMAND_BATTLEFIELD {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t padding00;
};

/// 0x0113
struct GP_CLI_COMMAND_SITCHAIR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Mode;
  uint32_t ChairId;
};

/// 0x0114
struct GP_CLI_COMMAND_MAP_MARKERS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0115
struct GP_CLI_COMMAND_CURRENCIES2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0116
struct GP_CLI_COMMAND_UNITY_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Kind;
};

/// 0x0117
struct GP_CLI_COMMAND_UNITYQUEST_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Kind;
};

/// 0x0118
struct GP_CLI_COMMAND_UNITY_CHAT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Mode;
  uint8_t padding00[3];
};

/// 0x0119
struct GP_CLI_COMMAND_EMOTELIST_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x011B
struct GP_CLI_COMMAND_MASTERY_DISPLAY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Mode;
  uint8_t padding00[3];
};

/// 0x011C
struct GP_CLI_COMMAND_PARTYREQUEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Kind;
  uint8_t padding00;
};

/// 0x011D
struct GP_CLI_COMMAND_JUMP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t padding00[2];
};
