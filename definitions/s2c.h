#include "s2c.types.h"

/// 0x0005
struct GP_SERV_COMMAND_PACKETCONTROL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t PacketCnt;
  uint32_t padding00[5];
};

/// 0x0006
struct GP_SERV_COMMAND_NARAKU {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0008
struct GP_SERV_COMMAND_ENTERZONE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t EnterZoneTbl[48];
};

/// 0x0009
struct GP_SERV_COMMAND_MESSAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t MesNo;
  uint8_t Attr;
  uint8_t Data[128];
};

/// 0x000A
struct GP_SERV_COMMAND_LOGIN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  _GP_SERV_POS_HEAD PosHead;
  uint32_t ZoneNo;
  uint32_t ntTime;
  uint32_t ntTimeSec;
  uint32_t GameTime;
  uint16_t EventNo;
  uint16_t MapNumber;
  uint16_t GrapIDTbl[9];
  uint16_t MusicNum[5];
  uint16_t SubMapNumber;
  uint16_t EventNum;
  uint16_t EventPara;
  uint16_t EventMode;
  uint16_t WeatherNumber;
  uint16_t WeatherNumber2;
  uint32_t WeatherTime;
  uint32_t WeatherTime2;
  uint32_t WeatherOffsetTime;
  uint32_t ShipStart;
  uint16_t ShipEnd;
  uint16_t IsMonstrosity;
  SAVE_LOGIN_STATE LoginState;
  char name[16];
  int32_t certificate[2];
  uint16_t unknown00;
  uint16_t ZoneSubNo;
  uint32_t PlayTime;
  uint32_t DeadCounter;
  uint8_t MyroomSubMapNumber;
  uint8_t unknown01;
  uint16_t MyroomMapNumber;
  uint16_t SendCount;
  uint8_t MyRoomExitBit;
  uint8_t MogZoneFlag;
  GP_MYROOM_DANCER_PKT Dancer;
  SAVE_CONF_PKT ConfData;
  uint32_t Ex;
};

/// 0x000B
struct GP_SERV_COMMAND_LOGOUT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  GP_GAME_LOGOUT_STATE LogoutState;
  uint8_t Iwasaki[16];
  GP_GAME_ECODE cliErrCode;
};

/// 0x000D
struct GP_SERV_COMMAND_CHAR_PC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  sendflags_t SendFlg;
  uint8_t dir;
  float x;
  float z;
  float y;
  flags0_t Flags0;
  uint8_t Speed;
  uint8_t SpeedBase;
  uint8_t Hpp;
  uint8_t server_status;
  flags1_t Flags1;
  flags2_t Flags2;
  flags3_t Flags3;
  uint32_t BtTargetID;
  uint16_t CostumeId;
  uint8_t BallistaInfo;
  flags4_t Flags4;
  uint32_t CustomProperties[2];
  uint16_t PetActIndex;
  uint16_t MonstrosityFlags;
  uint8_t MonstrosityNameId1;
  uint8_t MonstrosityNameId2;
  flags5_t Flags5;
  uint8_t ModelHitboxSize;
  flags6_t Flags6;
  uint16_t GrapIDTbl[9];
  uint8_t name[16];
};

typedef struct {
  uint16_t model_id;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_0_t;

typedef struct {
  uint16_t model_id;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_5_t;

typedef struct {
  uint16_t model_id;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_6_t;

typedef struct {
  uint16_t GrapIDTbl[9];
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_1_t;

typedef struct {
  uint16_t GrapIDTbl[9];
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_7_t;

typedef struct {
  uint16_t unused;
  uint32_t DoorId;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_2_t;

typedef struct {
  uint16_t unused;
  uint32_t DoorId;
  uint32_t Time;
  uint32_t EndTime;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_3_t;

typedef struct {
  uint16_t unused;
  uint32_t DoorId;
  uint32_t Time;
  uint32_t EndTime;
} _GP_SERV_COMMAND_CHAR_NPC_SubKind_4_t;

/// 0x000E
struct GP_SERV_COMMAND_CHAR_NPC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  sendflags_t SendFlg;
  uint8_t dir;
  float x;
  float z;
  float y;
  flags0_t Flags0;
  uint8_t Speed;
  uint8_t SpeedBase;
  uint8_t Hpp;
  uint8_t server_status;
  flags1_t Flags1;
  flags2_t Flags2;
  flags3_t Flags3;
  uint32_t BtTargetID;
  uint16_t SubKind : 3;
  uint16_t Status : 13;
  union Data {
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_0_t SubKind_0;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_1_t SubKind_1;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_2_t SubKind_2;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_3_t SubKind_3;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_4_t SubKind_4;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_5_t SubKind_5;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_6_t SubKind_6;
    _GP_SERV_COMMAND_CHAR_NPC_SubKind_7_t SubKind_7;
  };
};

/// 0x0011
struct GP_SERV_COMMAND_CHAR_DEL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0012
struct GP_SERV_COMMAND_GM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  char Mes[128];
};

/// 0x0013
struct GP_SERV_COMMAND_GMCOMMAND {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t GMUniqueNo;
  char Mes[128];
};

/// 0x0014
struct GP_SERV_COMMAND_TELL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Attr;
  uint8_t padding00;
  char Str[128];
};

/// 0x0016
struct GP_SERV_COMMAND_TALK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Attr;
  uint8_t Channel;
  uint8_t Type;
  char Str[128];
};

/// 0x0017
struct GP_SERV_COMMAND_CHAT_STD {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t Attr;
  uint16_t Data;
  char sName[15];
  char Mes[128];
};

/// 0x001B
struct GP_SERV_COMMAND_JOB_INFO {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t dancer[0x44];
  uint8_t job_lev2[0x18];
  uint32_t encumbrance;
  uint8_t can_thumbs_up_mentor;
  uint8_t mentor_rank;
  uint8_t mastery_rank;
  uint8_t padding00;
  uint32_t job_mastery_flags;
  uint8_t job_mastery_levels[0x18];
};

/// 0x001C
struct GP_SERV_COMMAND_ITEM_MAX {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t ItemNum[18];
  uint8_t padding00[14];
  uint16_t ItemNum2[18];
  uint8_t padding01[28];
};

/// 0x001D
struct GP_SERV_COMMAND_ITEM_SAME {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t State;
  uint8_t padding00[3];
  uint32_t Flags; // type="bits" bits="32"
};

/// 0x001E
struct GP_SERV_COMMAND_ITEM_NUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t LockFlg;
};

/// 0x001F
struct GP_SERV_COMMAND_ITEM_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t LockFlg;
};

/// 0x0020
struct GP_SERV_COMMAND_ITEM_ATTR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint32_t Price;
  uint16_t ItemNo;
  uint8_t Category;
  uint8_t ItemIndex;
  uint8_t LockFlg;
  uint8_t Attr[24];
  uint8_t padding00[3];
};

/// 0x0021
struct GP_SERV_COMMAND_ITEM_TRADE_REQ {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0022
struct GP_SERV_COMMAND_ITEM_TRADE_RES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t Kind;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0023
struct GP_SERV_COMMAND_ITEM_TRADE_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t TradeCounter;
  uint16_t ItemNo;
  uint8_t ItemFreeSpaceNum;
  uint8_t TradeIndex;
  uint8_t Attr[24];
};

/// 0x0025
struct GP_SERV_COMMAND_ITEM_TRADE_MYLIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo;
  uint8_t TradeIndex;
  uint8_t ItemIndex;
};

/// 0x0026
struct GP_SERV_COMMAND_ITEM_SUBCONTAINER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  _GP_SERV_COMMAND_ITEM_SUBCONTAINER_Data data;
};

/// 0x0027
struct GP_SERV_COMMAND_TALKNUMWORK2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t MesNum;
  uint16_t Type;
  uint8_t Flags;
  uint8_t padding00;
  uint32_t Num1[4];
  char String1[32];
  char String2[16];
  uint32_t Num2[8];
};

/// 0x0028
struct GP_SERV_COMMAND_BATTLE2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0029
struct GP_SERV_COMMAND_BATTLE_MESSAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNoCas;
  uint32_t UniqueNoTar;
  uint32_t Data;
  uint32_t Data2;
  uint16_t ActIndexCas;
  uint16_t ActIndexTar;
  uint16_t MessageNum;
  uint8_t Type;
  uint8_t padding00;
};

/// 0x002A
struct GP_SERV_COMMAND_TALKNUMWORK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  int32_t num[4];
  uint16_t ActIndex;
  uint16_t MesNum;
  uint8_t Type;
  uint8_t Flag;
  char String[32];
};

/// 0x002B
struct GP_SERV_COMMAND_CHANNEL_ITEM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t PropertyItemIndex;
  uint8_t ChannelIndex;
};

/// 0x002C
struct GP_SERV_COMMAND_CHANNEL_STATE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t ZoneNo;
  uint32_t IP;
  uint16_t ActIndex;
  uint16_t Port;
  uint8_t ChannelIndex;
  uint8_t HP;
};

/// 0x002D
struct GP_SERV_COMMAND_BATTLE_MESSAGE2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNoCas;
  uint32_t UniqueNoTar;
  uint16_t ActIndexCas;
  uint16_t ActIndexTar;
  uint32_t Data;
  uint32_t Data2;
  uint16_t MessageNum;
  uint8_t Type;
  uint8_t padding00;
};

/// 0x002E
struct GP_SERV_COMMAND_OPENMOGMENU {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x002F
struct GP_SERV_COMMAND_DIG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t TarUniqueNo;
  uint16_t TarActIndex;
  uint8_t Flags;
  uint8_t padding00;
};

/// 0x0030
struct GP_SERV_COMMAND_EFFECT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  int16_t EffectNum;
  int8_t Type;
  int8_t Status;
  uint16_t Timer;
};

/// 0x0031
struct GP_SERV_COMMAND_RECIPE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  union Data {
    _GP_SERV_COMMAND_RECIPE_Type_1 Type_1;
    _GP_SERV_COMMAND_RECIPE_Type_2 Type_2;
    _GP_SERV_COMMAND_RECIPE_Type_3 Type_3;
  };
  uint16_t Type;
  uint16_t Unknown00;
};

/// 0x0032
struct GP_SERV_COMMAND_EVENT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t EventNum;
  uint16_t EventPara;
  uint16_t Mode;
  uint16_t EventNum2;
  uint16_t EventPara2;
};

/// 0x0033
struct GP_SERV_COMMAND_EVENTSTR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t EventNum;
  uint16_t EventPara;
  uint16_t Mode;
  char String1[16];
  char String2[16];
  char String3[16];
  char String4[16];
  uint32_t Data[8];
};

/// 0x0034
struct GP_SERV_COMMAND_EVENTNUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  int32_t num[8];
  uint16_t ActIndex;
  uint16_t EventNum;
  uint16_t EventPara;
  uint16_t Mode;
  uint16_t EventNum2;
  uint16_t EventPara2;
};

/// 0x0036
struct GP_SERV_COMMAND_TALKNUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t MesNum;
  uint8_t Type;
  uint8_t padding00;
  uint16_t padding01;
};

/// 0x0037
struct GP_SERV_COMMAND_SERVERSTATUS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t BufStatus[32];
  uint32_t UniqueNo;
  flags0_t Flags0;
  flags1_t Flags1;
  uint8_t server_status;
  uint8_t r;
  uint8_t g;
  uint8_t b;
  flags2_t Flags2;
  flags3_t Flags3;
  uint32_t dead_counter1;
  uint32_t dead_counter2;
  uint16_t costume_id;
  uint16_t warp_target_index;
  uint16_t fellow_target_index;
  uint8_t fishing_timer;
  uint8_t padding00;
  uint32_t BufStatusBits[2];
  uint16_t monstrosity_info;
  uint8_t monstrosity_name_id1;
  uint8_t monstrosity_name_id2;
  flags4_t Flags4;
  uint8_t model_hitbox_size;
  flags5_t Flags5;
  uint8_t mount_id;
  flags6_t Flags6;
};

/// 0x0038
struct GP_SERV_COMMAND_SCHEDULOR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNoCas;
  uint32_t UniqueNoTar;
  uint32_t ident;
  uint16_t ActIndexCast;
  uint16_t ActIndexTar;
};

/// 0x0039
struct GP_SERV_COMMAND_MAPSCHEDULOR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNoCas;
  uint32_t UniqueNoTar;
  uint32_t id_scheduler;
  uint16_t ActIndexCast;
  uint16_t ActIndexTar;
};

/// 0x003A
struct GP_SERV_COMMAND_MAGICSCHEDULOR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNoCas;
  uint32_t UniqueNoTar;
  uint16_t ActIndexCast;
  uint16_t ActIndexTar;
  uint16_t fileNum;
  uint8_t type;
  uint8_t padding00;
};

/// 0x003B
struct GP_SERV_COMMAND_EVENTMES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t Number;
};

/// 0x003C
struct GP_SERV_COMMAND_SHOP_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ShopItemOffsetIndex;
  uint8_t Flags;
  uint8_t padding00;
  GP_SHOP ShopItemTbl[8];
};

/// 0x003D
struct GP_SERV_COMMAND_SHOP_SELL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Price;
  uint8_t PropertyItemIndex;
  uint8_t Type;
  uint16_t padding00;
  uint32_t Count;
};

/// 0x003E
struct GP_SERV_COMMAND_SHOP_OPEN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ShopListNum;
  uint16_t padding00;
};

/// 0x003F
struct GP_SERV_COMMAND_SHOP_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ShopItemIndex;
  uint8_t BuyState;
  uint8_t padding00;
  uint32_t Count;
};

/// 0x0040
struct GP_SERV_COMMAND_SHOP_CLOSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0041
struct GP_SERV_COMMAND_BLACK_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  SAVE_BLACK List[12];
  int8_t Stat;
  int8_t Num;
  uint16_t padding00;
};

/// 0x0042
struct GP_SERV_COMMAND_BLACK_EDIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  SAVE_BLACK Data;
  int8_t Mode;
  uint8_t padding00[3];
};

/// 0x0043
struct GP_SERV_COMMAND_TALKNUMNAME {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t MesNum;
  uint8_t Type;
  uint8_t padding00;
  uint16_t padding01;
  char sName[16];
};

/// 0x0044
struct GP_SERV_COMMAND_JOB_EXTRA_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t JobId;
  uint8_t IsSubJob;
  uint8_t Data[154];
};

/// 0x0047
struct GP_SERV_COMMAND_TRANSLATE_RESPONSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo;
  uint8_t FromIndex;
  uint8_t ToIndex;
  char FromString[64];
  char ToString[64];
};

/// 0x0048
struct GP_SERV_COMMAND_LINKSHELL_CONCIERGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t data[124];
};

/// 0x0049
struct GP_SERV_COMMAND_ITEMSEARCH_RESPONSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo;
  uint8_t Flag;
  uint8_t padding00;
  uint8_t ItemName[64];
};

/// 0x004B
struct GP_SERV_COMMAND_PBX_RESULT {
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
  uint32_t Represent[128];
};

/// 0x004C
struct GP_SERV_COMMAND_AUC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Command;
  char AucWorkIndex;
  char Result;
  char ResultStatus;
  union param {
    GP_AUC_PARAM_LOT Command_0;
    GP_AUC_PARAM_BID Command_14;
    GP_AUC_PARAM_SUMMARY Command_5;
    GP_AUC_PARAM_HISTORY Command_15;
    GP_AUC_PARAM_ASKCOMMIT Command_4;
    GP_AUC_PARAM_TRANS Command_1;
  };
  GP_AUC_BOX Parcel;
};

/// 0x004D
struct GP_SERV_COMMAND_FRAGMENTS {
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
  uint8_t data[128];
};

/// 0x004F
struct GP_SERV_COMMAND_EQUIP_CLEAR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t padding00;
};

/// 0x0050
struct GP_SERV_COMMAND_EQUIP_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t PropertyItemIndex;
  SAVE_EQUIP_KIND EquipKind;
  uint8_t Category;
  uint8_t padding00;
};

/// 0x0051
struct GP_SERV_COMMAND_GRAP_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t GrapIDTbl[9];
  uint16_t padding00;
};

/// 0x0052
struct GP_SERV_COMMAND_EVENTUCOFF {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Mode;
};

/// 0x0053
struct GP_SERV_COMMAND_SYSTEMMES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t para;
  uint32_t para2;
  uint16_t Number;
  uint16_t padding00;
};

/// 0x0054
struct GP_SERV_COMMAND_DEBUGPRINT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t data;
  uint8_t port;
  uint8_t padding00[3];
};

/// 0x0055
struct GP_SERV_COMMAND_SCENARIOITEM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t GetItemFlag[16];
  uint32_t LookItemFlag[16];
  uint16_t TableIndex;
  uint16_t padding00;
};

/// 0x0056
struct GP_SERV_COMMAND_MISSION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t data[8];
  uint16_t Port;
  uint16_t padding00;
};

/// 0x0057
struct GP_SERV_COMMAND_WEATHER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t StartTime;
  uint16_t WeatherNumber;
  uint16_t WeatherOffsetTime;
};

/// 0x0058
struct GP_SERV_COMMAND_ASSIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t AssistNo;
  uint16_t ActIndex;
  uint16_t padding00;
};

/// 0x0059
struct GP_SERV_COMMAND_FRIENDPASS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t leftNum;
  int32_t leftDays;
  int32_t passPop;
  char String[16];
  char Type;
  char unknown21;
  uint16_t padding00;
};

/// 0x005A
struct GP_SERV_COMMAND_MOTIONMES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t CasUniqueNo;
  uint32_t TarUniqueNo;
  uint16_t CasActIndex;
  uint16_t TarActIndex;
  uint16_t MesNum;
  uint16_t Param;
  uint16_t unknown14;
  uint8_t Mode;
  uint8_t padding00;
  uint32_t FaithUniqueNo[5];
  uint16_t FaithActIndex[5];
  uint16_t padding01;
};

/// 0x005B
struct GP_SERV_COMMAND_WPOS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  float x;
  float y;
  float z;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Mode;
  char dir;
  uint32_t padding00;
};

/// 0x005C
struct GP_SERV_COMMAND_PENDINGNUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t num[8];
};

/// 0x005D
struct GP_SERV_COMMAND_EVENT_PARAMS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t num[9];
  char string1[16];
  char string2[16];
  char string3[16];
  char string4[16];
};

/// 0x005E
struct GP_SERV_COMMAND_CONQUEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x005F
struct GP_SERV_COMMAND_MUSIC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Slot;
  uint16_t MusicNum;
};

/// 0x0060
struct GP_SERV_COMMAND_MUSICVOLUME {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t time;
  uint16_t volume;
};

/// 0x0061
struct GP_SERV_COMMAND_CLISTATUS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  CLISTATUS statusdata;
};

/// 0x0062
struct GP_SERV_COMMAND_CLISTATUS2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t CommandRecast[31];
  uint16_t skill_base[64];
};

/// 0x0063
struct GP_SERV_COMMAND_MULTI_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t type;
  uint16_t unknown00;
  uint8_t data[128];
};

/// 0x0064
struct GP_SERV_COMMAND_PREFERENCE_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t ContentLen;
  int32_t SegmentIndex;
  char PreferenceData[50];
  char SendDone;
};

/// 0x0065
struct GP_SERV_COMMAND_WPOS2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  float x;
  float y;
  float z;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Mode;
  char dir;
  uint32_t padding00;
};

/// 0x0067
struct GP_SERV_COMMAND_ENTITY_UPDATE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Mode : 6;
  uint16_t Length : 10;
  union Data {
    _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_2 Mode_2;
    _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_3 Mode_3;
    _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_4 Mode_4;
  };
};

/// 0x0068
struct GP_SERV_COMMAND_PET_UPDATE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Mode : 6;
  uint16_t Length : 10;
};

/// 0x0069
struct GP_SERV_COMMAND_CHOCOBO_RACING {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Mode;
};

/// 0x006F
struct GP_SERV_COMMAND_COMBINE_ANS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  int8_t Grade;
  uint8_t Count;
  uint8_t padding00;
  uint16_t ItemNo;
  uint16_t BreakNo[8];
  uint16_t UniqueNo;
  uint16_t ActIndex;
  uint8_t name[16];
  uint8_t padding01[2];
};

/// 0x0070
struct GP_SERV_COMMAND_COMBINE_INF {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;       // PS2: Result
  int8_t Grade;         // PS2: Grade
  uint8_t Count;        // PS2: Count
  uint8_t padding00;    // PS2: (New; did not exist.)
  uint16_t ItemNo;      // PS2: ItemNo
  uint16_t BreakNo[8];  // PS2: BreakNo
  uint16_t UniqueNo;    // PS2: UniqueNo
  uint16_t ActIndex;    // PS2: ActIndex
  uint8_t name[16];     // PS2: Name
  uint8_t padding01[2]; // PS2: (New; did not exist.)
};

/// 0x0071
struct GP_SERV_COMMAND_CAMPAIGN_MAP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Mode;
};

/// 0x0072
struct GP_SERV_COMMAND_UNKNOWN_0072 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0073
struct GP_SERV_COMMAND_UNKNOWN_0073 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0074
struct GP_SERV_COMMAND_UNKNOWN_0074 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0075
struct GP_SERV_COMMAND_UNKNOWN_0075 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0076
struct GP_SERV_COMMAND_UNKNOWN_0076 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0077
struct GP_SERV_COMMAND_ENTITY_VISIBILITY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Flags;
  uint8_t padding00[3];
  uint32_t Data[32];
};

/// 0x0078
struct GP_SERV_COMMAND_SWITCH_START {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t AllNum;
  uint16_t ActIndex;
  char sName[15];
  uint8_t Kind;
  char Str[128];
};

/// 0x0079
struct GP_SERV_COMMAND_SWITCH_PROC {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t AllNum;
  uint16_t VoteNumTbl[9];
  uint8_t Kind;
  uint8_t State;
  uint8_t QuestionNum;
  uint8_t sPropName[15];
  char Str[128];
};

/// 0x0081
struct GP_SERV_COMMAND_UNKNOWN_0081 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
};

/// 0x0082
struct GP_SERV_COMMAND_GUILD_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo;
  uint8_t Count;
  int8_t Trade;
};

/// 0x0083
struct GP_SERV_COMMAND_GUILD_BUYLIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  _GP_GUILD_ITEM List[30];
  uint8_t Count;
  uint8_t Stat;
};

/// 0x0084
struct GP_SERV_COMMAND_GUILD_SELL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ItemNo;
  uint8_t Count;
  int8_t Trade;
};

/// 0x0085
struct GP_SERV_COMMAND_GUILD_SELLLIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  _GP_GUILD_ITEM List[30];
  uint8_t Count;
  uint8_t Stat;
};

/// 0x0086
struct GP_SERV_COMMAND_GUILD_OPEN {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Stat;
  uint8_t padding00[3];
  uint32_t Time;
};

/// 0x008C
struct GP_SERV_COMMAND_MERIT_POINTS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t merit_count;
  uint16_t padding00;
};

/// 0x008D
struct GP_SERV_COMMAND_JOB_POINTS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t points[128];
};

/// 0x0096
struct GP_SERV_COMMAND_MYROOM_ENTER {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x0097
struct GP_SERV_COMMAND_MYROOM_EXIT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x0098
struct GP_SERV_COMMAND_MYROOM_IS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x0099
struct GP_SERV_COMMAND_MYROOM_EXIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x009A
struct GP_SERV_COMMAND_MYROOM_PLANT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x009B
struct GP_SERV_COMMAND_MYROOM_RAISE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x009C
struct GP_SERV_COMMAND_MYROOM_HARVEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Result;
  uint8_t padding00[3];
};

/// 0x009D
struct GP_SERV_COMMAND_MYROOM_DIARY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  GP_MYROOM_DIARY_DATA data;
};

/// 0x009E
struct GP_SERV_COMMAND_MYROOM_PLACE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int8_t job_lev[16];
  int8_t curjob[2];
  int8_t second;
};

/// 0x00A0
struct GP_SERV_COMMAND_MAP_GROUP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueID;
  int16_t zone;
  uint16_t padding00;
  float x;
  float y;
  float z;
};

/// 0x00AA
struct GP_SERV_COMMAND_MAGIC_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t MagicDataTbl[128];
};

/// 0x00AB
struct GP_SERV_COMMAND_FEAT_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t FeatDataTbl[20];
};

/// 0x00AC
struct GP_SERV_COMMAND_COMMAND_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t CommandDataTbl[224];
};

/// 0x00AD
struct GP_SERV_COMMAND_MMM_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Vouchers[8];
  uint8_t Runes[64];
  uint8_t unused00[56];
};

/// 0x00AE
struct GP_SERV_COMMAND_MOUNT_DATA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t MountDataTbl[8];
};

/// 0x00B4
struct GP_SERV_COMMAND_CONFIG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  SAVE_CONF ConfData;
  uint8_t unknown00;
  languages_t PartyLanguages;
  uint8_t unknown01[3];
};

/// 0x00B5
struct GP_SERV_COMMAND_FAQ_GMPARAM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t RescueCount;
  uint32_t params[4];
  uint16_t Id;
  uint16_t Option;
  uint16_t Status;
  uint16_t RescueTime;
};

/// 0x00B6
struct GP_SERV_COMMAND_SET_GMMSG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t msgId;
  uint16_t seqId;
  uint16_t pktNum;
  uint8_t Msg[128];
};

/// 0x00B7
struct GP_SERV_COMMAND_GMSCITEM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemFlag[16];
  uint32_t UniqueNo;
  char sName[16];
  uint16_t TableIndex;
};

/// 0x00BF
struct GP_SERV_COMMAND_BATTLEFIELD_EVENT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t unknown04;
  uint16_t Result;
  uint32_t unknown08;
  uint32_t ActIndex;
};

/// 0x00C8
struct GP_SERV_COMMAND_GROUP_TBL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Kind;
  uint8_t padding00[3];
  GROUP_TBL GroupTbl[20];
};

/// 0x00C9
struct GP_SERV_COMMAND_EQUIP_INSPECT {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  // BEGIN eqHdr
  uint32_t UniqNo;    // PS2: UniqNo
  uint16_t ActIndex;  // PS2: ActIndex
  uint8_t OptionFlag; // PS2: OptionFlag
  // END eqHdr

  union Data {
    _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_0 OptionFlag_0;
    _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_1 OptionFlag_1;
    _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_2 OptionFlag_2;
    _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_3 OptionFlag_3;
  };
};

/// 0x00CA
struct GP_SERV_COMMAND_INSPECT_MESSAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t sInspectMessage[123];
  uint8_t BazaarFlag : 1;
  uint8_t MyFlag : 1;
  uint8_t Race : 6;
  char sName[16];
  uint32_t DesignationNo;
};

/// 0x00DD
struct GP_SERV_COMMAND_GROUP_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t Hp;
  uint32_t Mp;
  uint32_t Tp;
  GP_GROUP_ATTR GAttr;
  uint16_t ActIndex;
  uint8_t MemberNumber;
  uint8_t MoghouseFlg;
  uint8_t Kind;
  uint8_t Hpp;
  uint8_t Mpp;
  uint8_t padding00;
  uint16_t ZoneNo;
  uint8_t mjob_no;
  uint8_t mjob_lv;
  uint8_t sjob_no;
  uint8_t sjob_lv;
  uint8_t masterjob_lv;
  uint8_t masterjob_flags;
  uint8_t Name[16];
};

/// 0x00DE
struct GP_SERV_COMMAND_GROUP_SOLICIT_NO {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Reason;
  uint8_t padding00[3];
};

/// 0x00DF
struct GP_SERV_COMMAND_GROUP_ATTR {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t Hp;
  uint32_t Mp;
  uint32_t Tp;
  uint16_t ActIndex;
  uint8_t Hpp;
  uint8_t Mpp;
  uint8_t Kind;
  uint8_t MoghouseFlg;
  uint16_t ZoneNo;
  uint16_t MonstrosityFlag;
  uint16_t MonstrosityNameId;
  uint8_t mjob_no;
  uint8_t mjob_lv;
  uint8_t sjob_no;
  uint8_t sjob_lv;
  uint8_t masterjob_lv;
  uint8_t masterjob_flags;
};

/// 0x00E0
struct GP_SERV_COMMAND_GROUP_COMLINK {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t LinkshellNum;
  uint8_t ItemIndex;
  uint8_t Category;
  uint8_t padding00;
};

/// 0x00E1
struct GP_SERV_COMMAND_GROUP_CHECKID {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t GroupID;
};

/// 0x00E2
struct GP_SERV_COMMAND_GROUP_LIST2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t Hp;
  uint32_t Mp;
  uint32_t Tp;
  GP_GROUP_ATTR GAttr;
  uint16_t ActIndex;
  uint8_t MemberNumber;
  uint8_t MoghouseFlg;
  uint8_t Kind;
  uint8_t Hpp;
  uint8_t Mpp;
  uint8_t padding00;
  uint16_t ZoneNo;
  uint8_t mjob_no;
  uint8_t mjob_lv;
  uint8_t sjob_no;
  uint8_t sjob_lv;
  uint8_t masterjob_lv;
  uint8_t masterjob_flags;
  uint8_t Name[16];
};

/// 0x00E6
struct GP_SERV_COMMAND_BALLISTA {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t Flags : 6;
  uint16_t Mode : 10;
  uint8_t Data[128];
};

/// 0x00F4
struct GP_SERV_COMMAND_TRACKING_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  GP_TRACKING TrackingListTbl;
};

/// 0x00F5
struct GP_SERV_COMMAND_TRACKING_POS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  float x;
  float y;
  float z;
  uint8_t Level;
  uint8_t unused;
  uint16_t ActIndex;
  GP_TRACKING_POS_STATE State;
};

/// 0x00F6
struct GP_SERV_COMMAND_TRACKING_STATE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  GP_TRACKING_STATE State;
};

/// 0x00F9
struct GP_SERV_COMMAND_RES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint16_t type;
};

/// 0x00FA
struct GP_SERV_COMMAND_MYROOM_OPERATION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t MyroomItemNo;
  GP_MYROOM_RESULT Result;
  uint16_t unknown00;
  uint8_t MyroomItemIndex;
  uint8_t MyroomCategory;
  uint16_t unknown01;
};

/// 0x0105
struct GP_SERV_COMMAND_BAZAAR_LIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Price;
  uint32_t ItemNum;
  uint16_t TaxRate;
  uint16_t ItemNo;
  uint8_t ItemIndex;
  uint8_t Attr[24];
  uint8_t padding00[3];
};

/// 0x0106
struct GP_SERV_COMMAND_BAZAAR_BUY {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  GP_BAZAAR_BUY_STATE State;
  char sName[16];
};

/// 0x0107
struct GP_SERV_COMMAND_BAZAAR_CLOSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  char sName[16];
  uint8_t padding00[4];
};

/// 0x0108
struct GP_SERV_COMMAND_BAZAAR_SHOPPING {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  GP_BAZAAR_SHOPPING_STATE State;
  uint8_t HideLevel;
  uint8_t padding00;
  uint16_t ActIndex;
  char sName[16];
};

/// 0x0109
struct GP_SERV_COMMAND_BAZAAR_SELL {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint32_t ItemNum;
  uint16_t ActIndex;
  uint16_t BazaarActIndex;
  char sName[16];
  uint8_t ItemIndex;
  uint8_t padding00[3];
};

/// 0x010A
struct GP_SERV_COMMAND_BAZAAR_SALE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t ItemNum;
  uint16_t ItemNo;
  char sName[16];
  uint8_t padding00[2];
};

/// 0x010E
struct GP_SERV_COMMAND_REQSUBMAPNUM {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t MapNum;
};

/// 0x010F
struct GP_SERV_COMMAND_REQLOGOUTINFO {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Mode;
};

/// 0x0110
struct GP_SERV_COMMAND_UNITY_ROE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t Sparks : 24;
  uint32_t unused00 : 8;
  uint16_t Deeds;
  uint16_t padding00;
  uint8_t RoEUnityShared;
  uint8_t RoEUnityLeader;
  uint8_t unknown0E[6];
};

/// 0x0111
struct GP_SERV_COMMAND_ROE_RECORDS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t records[64];
};

/// 0x0112
struct GP_SERV_COMMAND_ROE_QUEST_LOG {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Data[128];
  uint16_t Offset;
  uint16_t padding00;
};

/// 0x0113
struct GP_SERV_COMMAND_CURRENCIES {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t conquest_points_sandoria;
  int32_t conquest_points_bastok;
  int32_t conquest_points_windurst;
  uint16_t beastmans_seals_stored;
  uint16_t kindreds_seals_stored;
  uint16_t kindreds_crests_stored;
  uint16_t high_kindreds_crests_stored;
  uint16_t sacred_kindreds_crests_stored;
  uint16_t ancient_beastcoins_stored;
  uint16_t valor_points;
  uint16_t scylds;
  int32_t guild_points_fishing;
  int32_t guild_points_woodworking;
  int32_t guild_points_smithing;
  int32_t guild_points_goldsmithing;
  int32_t guild_points_weaving;
  int32_t guild_points_leathercraft;
  int32_t guild_points_bonecraft;
  int32_t guild_points_alchemy;
  int32_t guild_points_cooking;
  int32_t cinders;
  uint8_t synergy_fewell_fire;
  uint8_t synergy_fewell_ice;
  uint8_t synergy_fewell_wind;
  uint8_t synergy_fewell_earth;
  uint8_t synergy_fewell_lightning;
  uint8_t synergy_fewell_water;
  uint8_t synergy_fewell_light;
  uint8_t synergy_fewell_dark;
  int32_t ballista_points;
  int32_t fellow_points;
  uint16_t chocobucks_sandoria_team;
  uint16_t chocobucks_bastok_team;
  uint16_t chocobucks_windurst_team;
  uint16_t daily_tally;
  int32_t research_marks;
  uint8_t wizened_tunnel_worms;
  uint8_t wizened_morion_worms;
  uint8_t wizened_phantom_worms;
  uint8_t unknown67;
  int32_t moblin_marbles;
  uint16_t infamy;
  uint16_t prestige;
  int32_t legion_points;
  int32_t sparks_of_eminence;
  int32_t shining_stars;
  int32_t imperial_standing;
  int32_t assault_points_l_sanctum;
  int32_t assault_points_mjtg;
  int32_t assault_points_l_cavern;
  int32_t assault_points_periqia;
  int32_t assault_points_ilrusi_atoll;
  int32_t tokens;
  int32_t zeni;
  int32_t jettons;
  int32_t therion_ichor;
  int32_t allied_notes;
  uint16_t copper_aman_vouchers_stored;
  uint16_t login_points;
  int32_t cruor;
  int32_t resistance_credits;
  int32_t dominion_notes;
  uint8_t echelon_battle_trophies_5th;
  uint8_t echelon_battle_trophies_4th;
  uint8_t echelon_battle_trophies_3rd;
  uint8_t echelon_battle_trophies_2nd;
  uint8_t echelon_battle_trophies_1st;
  uint8_t cave_conservation_points;
  uint8_t imperial_army_id_tags;
  uint8_t op_credits;
  int32_t traverser_stones;
  int32_t voidstones;
  int32_t kupofrieds_corundums;
  uint8_t moblin_pheromone_sacks;
  uint8_t unknownCD;
  uint8_t rems_tale_chapters_1_stored;
  uint8_t rems_tale_chapters_2_stored;
  uint8_t rems_tale_chapters_3_stored;
  uint8_t rems_tale_chapters_4_stored;
  uint8_t rems_tale_chapters_5_stored;
  uint8_t rems_tale_chapters_6_stored;
  uint8_t rems_tale_chapters_7_stored;
  uint8_t rems_tale_chapters_8_stored;
  uint8_t rems_tale_chapters_9_stored;
  uint8_t rems_tale_chapters_10_stored;
  uint64_t bloodshed_plans_stored : 9;
  uint64_t umbrage_plans_stored : 9;
  uint64_t ritualistic_plans_stored : 9;
  uint64_t tutelary_plans_stored : 9;
  uint64_t primacy_plans_stored : 9;
  uint64_t unused : 19;
  uint16_t reclamation_marks;
  uint16_t padding00;
  int32_t unity_accolades;
  uint16_t fire_crystals_stored;
  uint16_t ice_crystals_stored;
  uint16_t wind_crystals_stored;
  uint16_t earth_crystals_stored;
  uint16_t lightning_crystals_stored;
  uint16_t water_crystals_stored;
  uint16_t light_crystals_stored;
  uint16_t dark_crystals_stored;
  uint16_t deeds;
  uint16_t padding01;
};

/// 0x0115
struct GP_SERV_COMMAND_FISHING_MINIGAME {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t stamina;
  uint16_t arrow_delay;
  uint16_t regen;
  uint16_t move_frequency;
  uint16_t arrow_damage;
  uint16_t arrow_regen;
  uint16_t time;
  uint8_t angler_sense;
  uint8_t padding00;
  uint32_t intuition;
};

/// 0x0116
struct GP_SERV_COMMAND_EQUIPMENT_SET_RESPONSE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Items[68];
};

/// 0x0117
struct GP_SERV_COMMAND_EQUIPSET_VALIDATION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Count;
  uint8_t padding00[3];
  uint8_t ItemsChanged[64];
  uint8_t ItemsEquipped[64];
};

/// 0x0118
struct GP_SERV_COMMAND_CURRENCIES2 {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  int32_t bayld;
  uint16_t kinetic_units;
  uint8_t coalition_imprimaturs;
  uint8_t mystical_canteens;
  int32_t obsidian_fragments;
  uint16_t lebondopt_wings_stored;
  uint16_t pulchridopt_wings_stored;
  int32_t mweya_plasm_corpuscles;
  uint8_t ghastly_stones_stored;
  uint8_t ghastly_stones_plus1_stored;
  uint8_t ghastly_stones_plus2_stored;
  uint8_t verdigris_stones_stored;
  uint8_t verdigris_stones_plus1_stored;
  uint8_t verdigris_stones_plus2_stored;
  uint8_t wailing_stones_stored;
  uint8_t wailing_stones_plus1_stored;
  uint8_t wailing_stones_plus2_stored;
  uint8_t snowslit_stones_stored;
  uint8_t snowslit_stones_plus1_stored;
  uint8_t snowslit_stones_plus2_stored;
  uint8_t snowtip_stones_stored;
  uint8_t snowtip_stones_plus1_stored;
  uint8_t snowtip_stones_plus2_stored;
  uint8_t snowdim_stones_stored;
  uint8_t snowdim_stones_plus1_stored;
  uint8_t snowdim_stones_plus2_stored;
  uint8_t snoworb_stones_stored;
  uint8_t snoworb_stones_plus1_stored;
  uint8_t snoworb_stones_plus2_stored;
  uint8_t leafslit_stones_stored;
  uint8_t leafslit_stones_plus1_stored;
  uint8_t leafslit_stones_plus2_stored;
  uint8_t leaftip_stones_stored;
  uint8_t leaftip_stones_plus1_stored;
  uint8_t leaftip_stones_plus2_stored;
  uint8_t leafdim_stones_stored;
  uint8_t leafdim_stones_plus1_stored;
  uint8_t leafdim_stones_plus2_stored;
  uint8_t leaforb_stones_stored;
  uint8_t leaforb_stones_plus1_stored;
  uint8_t leaforb_stones_plus2_stored;
  uint8_t duskslit_stones_stored;
  uint8_t duskslit_stones_plus1_stored;
  uint8_t duskslit_stones_plus2_stored;
  uint8_t dusktip_stones_stored;
  uint8_t dusktip_stones_plus1_stored;
  uint8_t dusktip_stones_plus2_stored;
  uint8_t duskdim_stones_stored;
  uint8_t duskdim_stones_plus1_stored;
  uint8_t duskdim_stones_plus2_stored;
  uint8_t duskorb_stones_stored;
  uint8_t duskorb_stones_plus1_stored;
  uint8_t duskorb_stones_plus2_stored;
  uint8_t pellucid_stones_stored;
  uint8_t fern_stones_stored;
  uint8_t taupe_stones_stored;
  uint16_t mellidopt_wings_stored;
  uint16_t escha_beads;
  int32_t escha_silt;
  int32_t potpourri;
  int32_t hallmarks;
  int32_t total_hallmarks;
  int32_t badges_of_gallantry;
  int32_t crafter_points;
  uint8_t fire_crystals_set;
  uint8_t ice_crystals_set;
  uint8_t wind_crystals_set;
  uint8_t earth_crystals_set;
  uint8_t lightning_crystals_set;
  uint8_t water_crystals_set;
  uint8_t light_crystals_set;
  uint8_t dark_crystals_set;
  uint8_t mc_i_sr01s_set;
  uint8_t mc_i_sr02s_set;
  uint8_t mc_i_sr03s_set;
  uint8_t liquefactions_spheres_set;
  uint8_t induration_spheres_set;
  uint8_t dentonation_spheres_set;
  uint8_t scission_spheres_set;
  uint8_t impaction_spheres_set;
  uint8_t reverberation_spheres_set;
  uint8_t transfixion_spheres_set;
  uint8_t compression_spheres_set;
  uint8_t fusion_spheres_set;
  uint8_t distortion_spheres_set;
  uint8_t fragmentation_spheres_set;
  uint8_t gravitation_spheres_set;
  uint8_t light_spheres_set;
  uint8_t darkness_spheres_set;
  uint8_t padding00[3];
  int32_t silver_aman_vouchers_stored;
  int32_t domain_points;
  int32_t domain_points_earned_today;
  int32_t mog_segments;
  int32_t gallimaufry;
};

/// 0x0119
struct GP_SERV_COMMAND_RECAST_TIMERS {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Timers[248];
  uint32_t MountRecast;
  uint32_t MountRecastId;
};

/// 0x011A
struct GP_SERV_COMMAND_EMOTELIST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t JobEmotes;
  uint16_t Chairs;
  uint16_t padding00;
};

/// 0x011B
struct GP_SERV_COMMAND_LOCKSTYLE_TOGGLE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Status;
  uint8_t padding00[3];
};

/// 0x011C
struct GP_SERV_COMMAND_LOCKSTYLE_VALIDATION {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t Count;
  uint8_t padding00[3];
  uint16_t ItemNo[16];
};

/// 0x011D
struct GP_SERV_COMMAND_PARTY_REQUEST {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint32_t UniqueNo;
  uint16_t ActIndex;
  uint8_t Flags;
  uint8_t Status;
  char sName[16];
  uint16_t Race;
  uint8_t padding00[2];
};

/// 0x011E
struct GP_SERV_COMMAND_JUMP {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint16_t ActIndex;
  uint8_t padding00[2];
};

/// 0x00CC
struct GP_SERV_COMMAND_LINKSHELL_MESSAGE {
  uint16_t id : 9;
  uint16_t size : 7;
  uint16_t sync;
  uint8_t stat : 4;
  uint8_t attr : 4;
  uint8_t readLevel : 2;
  uint8_t writeLevel : 2;
  uint8_t pubEditLevel : 2;
  uint8_t linkshell_index : 2;
  uint16_t seqId;
  uint8_t sMessage[128];
  uint32_t updateTime;
  uint8_t modifier[16];
  uint16_t opType;
  uint16_t padding00;
  uint8_t encodedLsName[16];
};
