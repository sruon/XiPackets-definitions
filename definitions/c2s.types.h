#include "typedefs.h"

struct SAVE_BLACK {
  uint32_t ID;
  uint8_t Name[16];
};

typedef struct SAVE_BLACK SAVE_BLACK;

struct GP_BLACK_EDIT {
  uint32_t ID;
  uint8_t Name[16];
};

struct _GP_COMBINE_ASK {
  uint8_t HashNo;
  uint8_t padding00;
  uint16_t Crystal;
  uint8_t CrystalIdx;
  uint8_t Items;
  uint16_t ItemNo[8];
  uint8_t TableNo[8];
};

struct _GP_MYROOM_GATE_REQ {
  uint16_t unknown00;
  uint16_t unknown01;
  uint8_t unknown02;
  uint8_t unknown03;
};

struct _GP_MYROOM_DIARY_REQ {
  uint8_t unknown00;
  uint8_t unknown01;
  uint16_t unknown02;
};

struct _GP_MYROOM_PLACE_REQ {
  uint16_t ItemNo;
  int8_t X;
  int8_t Y;
  int8_t Z;
  int8_t V;
  uint8_t TableNo;
  uint8_t padding00;
};

struct _GP_MAP_GROUP_REQ {
  uint32_t ZoneNo;
};

struct FFGpGMReportBlockHdr {
  uint16_t type : 4;
  uint16_t vers : 4;
  uint16_t pktId : 8;
  uint16_t seq : 7;
  uint16_t eos : 1;
  uint16_t blkNum : 8;
  uint8_t Data[128];
};

struct FFGpGMReportLobbyStruct {
  uint16_t Id;
  uint16_t Option;
};

struct expansions_t {
  uint32_t has_final_fantasy_xi : 1;
  uint32_t has_rise_of_the_zilart : 1;
  uint32_t has_chains_of_promathia : 1;
  uint32_t has_treasures_of_aht_urhgan : 1;
  uint32_t has_wings_of_the_goddess : 1;
  uint32_t has_a_crystalline_prophecy : 1;
  uint32_t has_a_moogle_kupo_detat : 1;
  uint32_t has_a_shantotto_ascension : 1;
  uint32_t has_vision_of_abyssea : 1;
  uint32_t has_scars_of_abyssea : 1;
  uint32_t has_heroes_of_abyssea : 1;
  uint32_t has_seekers_of_adoulin : 1;
  uint32_t has_bit12 : 1;
  uint32_t has_bit13 : 1;
  uint32_t has_bit14 : 1;
  uint32_t has_bit15 : 1;
  uint32_t has_bit16 : 1;
  uint32_t has_bit17 : 1;
  uint32_t has_bit18 : 1;
  uint32_t has_bit19 : 1;
  uint32_t has_bit20 : 1;
  uint32_t has_bit21 : 1;
  uint32_t has_bit22 : 1;
  uint32_t has_bit23 : 1;
  uint32_t has_bit24 : 1;
  uint32_t has_bit25 : 1;
  uint32_t has_bit26 : 1;
  uint32_t has_bit27 : 1;
  uint32_t has_bit28 : 1;
  uint32_t has_bit29 : 1;
  uint32_t has_bit30 : 1;
  uint32_t has_bit31 : 1;
};

struct lockstyleitem_t {
  uint8_t ItemIndex;
  uint8_t EquipKind;
  uint8_t Category;
  uint8_t padding00;
  uint16_t ItemNo;
  uint16_t padding01;
};

struct equipsetrequestitem_t {
  uint8_t HasItemFlg : 1;
  uint8_t RemoveItemFlg : 1;
  uint8_t Category : 6;
  uint8_t ItemIndex;
  uint16_t ItemNo;
};

struct equipsetitem_t {
  uint8_t ItemIndex;
  uint8_t EquipKind;
  uint8_t Category;
  uint8_t padding00;
};