#include "typedefs.h"

// CLISTATUS struct for 0x0061 packet
struct CLISTATUS {
  int32_t hpmax;
  int32_t mpmax;
  uint8_t mjob_no; // lookup="jobs"
  uint8_t mjob_lv;
  uint8_t sjob_no; // lookup="jobs"
  uint8_t sjob_lv;
  uint16_t exp_now;  // report to atom0s the type change
  uint16_t exp_next; // report to atom0s the type change
  uint16_t bp_base[7];
  int16_t bp_adj[7];
  int16_t atk;
  int16_t def;
  int16_t def_elem[8];
  uint16_t designation;
  uint16_t rank;
  uint16_t rankbar;
  uint16_t BindZoneNo;
  uint32_t MonsterBuster;
  uint8_t nation; // lookup="nations"
  uint8_t myroom;
  uint8_t su_lv;
  uint8_t padding00;
  uint8_t highest_ilvl;
  uint8_t ilvl;
  uint8_t ilvl_mhand;
  uint8_t ilvl_ranged;
  uint32_t unity_info;
  uint16_t unity_points1;
  uint16_t unity_points2;
  uint32_t unity_chat_color_flag;
  uint32_t mastery_info;
  uint32_t mastery_exp_now;
  uint32_t mastery_exp_next;
};

// Enums for 0x000B packet
enum GP_GAME_LOGOUT_STATE : uint32_t {
  GP_GAME_LOGOUT_STATE_NONE,
  GP_GAME_LOGOUT_STATE_LOGOUT,
  GP_GAME_LOGOUT_STATE_ZONECHANGE,
  GP_GAME_LOGOUT_STATE_MYROOM,
  GP_GAME_LOGOUT_STATE_CANCELL,
  GP_GAME_LOGOUT_STATE_POLEXIT,
  GP_GAME_LOGOUT_STATE_JOBEXIT,
  GP_GAME_LOGOUT_STATE_POLEXIT_MYROOM,
  GP_GAME_LOGOUT_STATE_TIMEOUT,
  GP_GAME_LOGOUT_STATE_GMLOGOUT,
  GP_GAME_LOGOUT_STATE_END
};

enum GP_GAME_ECODE : uint32_t {
  GP_GAME_ECODE_NOERR,
  GP_GAME_ECODE_RESERR,
  GP_GAME_ECODE_ZONEDOWN,
  GP_GAME_ECODE_REGERR,
  GP_GAME_ECODE_CLIVERSERR,
  GP_GAME_ECODE_CLINOEXERR,
  GP_GAME_ECODE_UNKNOWN,
  GP_GAME_ECODE_MAX
};

// Structures for 0x000A LOGIN packet
struct _GP_SERV_POS_HEAD {
  uint32_t UniqueNo; // lookup="@uniqueno"
  uint16_t ActIndex; // lookup="@actindex"
  uint8_t padding00;
  int8_t dir;
  float x;
  float z;
  float y;
  uint32_t flags1;
  uint8_t Speed;
  uint8_t SpeedBase;
  uint8_t HpMax;
  uint8_t server_status;
  uint32_t flags2;
  uint32_t flags3;
  uint32_t flags4;
  uint32_t BtTargetID;
};

enum SAVE_LOGIN_STATE : uint32_t {
  SAVE_LOGIN_STATE_NONE = 0,
  SAVE_LOGIN_STATE_MYROOM = 1,
  SAVE_LOGIN_STATE_GAME = 2,
  SAVE_LOGIN_STATE_POLEXIT = 3,
  SAVE_LOGIN_STATE_JOBEXIT = 4,
  SAVE_LOGIN_STATE_POLEXIT_MYROOM = 5,
  SAVE_LOGIN_STATE_END = 6
};

struct GP_MYROOM_DANCER_PKT {
  uint16_t mon_no;
  uint16_t face_no;
  uint8_t mjob_no; // lookup="jobs"
  uint8_t hair_no;
  uint8_t size;
  uint8_t sjob_no; // lookup="jobs"
  uint32_t get_job_flag;
  int8_t job_lev[16];
  uint16_t bp_base[7];
  int16_t bp_adj[7];
  int32_t hpmax;
  int32_t mpmax;
  uint8_t sjobflg;
  uint8_t unknown00[3];
};

struct SAVE_CONF_PKT {
  uint32_t unknown00[3];
};

// Structures for 0x000D and 0x000E CHAR packets
struct sendflags_t {
  uint8_t Position : 1;
  uint8_t ClaimStatus : 1;
  uint8_t General : 1;
  uint8_t Name : 1;
  uint8_t Model : 1;
  uint8_t Despawn : 1;
  uint8_t Name2 : 1;
  uint8_t unused : 1;
};

struct flags0_t {
  uint32_t MovTime : 13;
  uint32_t RunMode : 1;
  uint32_t unknown_1_6 : 1;
  uint32_t GroundFlag : 1;
  uint32_t KingFlag : 1;
  uint32_t facetarget : 15; // lookup="@actindex"
};

struct flags1_t {
  uint32_t MonsterFlag : 1;
  uint32_t HideFlag : 1;
  uint32_t SleepFlag : 1;
  uint32_t unknown_0_3 : 1;
  uint32_t unknown_0_4 : 1;
  uint32_t ChocoboIndex : 3;
  uint32_t CliPosInitFlag : 1;
  uint32_t GraphSize : 2;
  uint32_t LfgFlag : 1;
  uint32_t AnonymousFlag : 1;
  uint32_t YellFlag : 1;
  uint32_t AwayFlag : 1;
  uint32_t Gender : 1;
  uint32_t PlayOnelineFlag : 1;
  uint32_t LinkShellFlag : 1;
  uint32_t LinkDeadFlag : 1;
  uint32_t TargetOffFlag : 1;
  uint32_t TalkUcoffFlag : 1;
  uint32_t unknown_2_5 : 1;
  uint32_t unknown_2_6 : 1;
  uint32_t unknown_2_7 : 1;
  uint32_t GmLevel : 3;
  uint32_t HackMove : 1;
  uint32_t unknown_3_4 : 1;
  uint32_t InvisFlag : 1;
  uint32_t TurnFlag : 1;
  uint32_t BazaarFlag : 1;
};

struct flags2_t {
  uint32_t r : 8;
  uint32_t g : 8;
  uint32_t b : 8;
  uint32_t PvPFlag : 1;
  uint32_t ShadowFlag : 1;
  uint32_t ShipStartMode : 1;
  uint32_t CharmFlag : 1;
  uint32_t GmIconFlag : 1;
  uint32_t NamedFlag : 1;
  uint32_t SingleFlag : 1;
  uint32_t AutoPartyFlag : 1;
};

struct flags3_t {
  uint32_t TrustFlag : 1;
  uint32_t LfgMasterFlag : 1;
  uint32_t PetNewFlag : 1;
  uint32_t unknown_0_3 : 1;
  uint32_t MotStopFlag : 1;
  uint32_t CliPriorityFlag : 1;
  uint32_t PetFlag : 1;
  uint32_t OcclusionoffFlag : 1;
  uint32_t BallistaTeam : 8;
  uint32_t MonStat : 3;
  uint32_t unknown_2_3 : 1;
  uint32_t unknown_2_4 : 1;
  uint32_t SilenceFlag : 1;
  uint32_t unknown_2_6 : 1;
  uint32_t NewCharacterFlag : 1;
  uint32_t MentorFlag : 1;
  uint32_t unknown_3_1 : 1;
  uint32_t unknown_3_2 : 1;
  uint32_t unknown_3_3 : 1;
  uint32_t unknown_3_4 : 1;
  uint32_t unknown_3_5 : 1;
  uint32_t unknown_3_6 : 1;
  uint32_t unknown_3_7 : 1;
};

struct flags4_t {
  uint8_t unknown_0_0 : 1;
  uint8_t TrialFlag : 1;
  uint8_t unknown_0_2 : 2;
  uint8_t unknown_0_4 : 2;
  uint8_t JobMasterFlag : 1;
  uint8_t unknown_0_7 : 1;
};

struct flags5_t {
  uint8_t GeoIndiElement : 4;
  uint8_t GeoIndiSize : 2;
  uint8_t GeoIndiFlag : 1;
  uint8_t unknown_0_7 : 1;
};

struct flags6_t {
  uint32_t GateId : 4;
  uint32_t MountIndex : 8;
  uint32_t unknown_1_3 : 20;
};

// Structures for 0x0056 MISSION packet
struct MISSION_DATA {
  uint32_t QuestOffer[88];
  uint32_t QuestComplete[88];
  uint32_t MissionComplete[32];
  uint32_t Expansion_RotZ;
  uint16_t NationMission;
  uint8_t Nation;
  uint8_t RdyFlag;
  uint32_t Expansion_CoP;
  uint32_t Expansion_CoP2;
  uint32_t Expansion_Addons;
  uint32_t Expansion_SoA;
  uint32_t Expansion_RoV;
  uint32_t Expansion_TVR;
  uint32_t TalesBeginning;
  uint32_t RecBitFlag;
  uint32_t CallPtr;
};

// Enum for 0x0050 EQUIP_LIST packet
enum SAVE_EQUIP_KIND : uint8_t {
  SAVE_EQUIP_KIND_RIGHTHAND,
  SAVE_EQUIP_KIND_LEFTHAND,
  SAVE_EQUIP_KIND_BOW,
  SAVE_EQUIP_KIND_ARROW,
  SAVE_EQUIP_KIND_HEAD,
  SAVE_EQUIP_KIND_BODY,
  SAVE_EQUIP_KIND_ARM,
  SAVE_EQUIP_KIND_LEG,
  SAVE_EQUIP_KIND_FOOT,
  SAVE_EQUIP_KIND_NECK,
  SAVE_EQUIP_KIND_BELT,
  SAVE_EQUIP_KIND_RIGHTEAR,
  SAVE_EQUIP_KIND_LEFTEAR,
  SAVE_EQUIP_KIND_RIGHTFINGER,
  SAVE_EQUIP_KIND_LEFTFINGER,
  SAVE_EQUIP_KIND_BACKPACK,
  SAVE_EQUIP_KIND_END
};

// Structures for 0x00C8 GROUP_TBL packet
struct GROUP_TBL {
  uint32_t UniqueNo; // lookup="@uniqueno"
  uint16_t ActIndex; // lookup="@actindex"
  uint8_t PartyNo : 2;
  uint8_t PartyLeaderFlg : 1;
  uint8_t AllianceLeaderFlg : 1;
  uint8_t PartyRFlg : 1;
  uint8_t AllianceRFlg : 1;
  uint8_t unknown06 : 1;
  uint8_t unknown07 : 1;
  uint8_t padding00;
  uint16_t ZoneNo;
  uint16_t padding01;
};

// Structures for 0x00C9 EQUIP_INSPECT packet
struct _GP_SERV_EQUIP_INSPECT_HDR {
  uint32_t UniqNo;   // lookup="@uniqueno"
  uint16_t ActIndex; // lookup="@actindex"
  uint8_t OptionFlag;
};

struct checkitem_t {
  uint16_t ItemNo;
  SAVE_EQUIP_KIND EquipKind;
  uint8_t padding00;
  uint8_t Data[24];
};

// Structure for group packets
struct GP_GROUP_ATTR {
  uint32_t PartyNo : 2;
  uint32_t PartyLeaderFlg : 1;
  uint32_t AllianceLeaderFlg : 1;
  uint32_t PartyRFlg : 1;
  uint32_t AllianceRFlg : 1;
  uint32_t unknown06 : 1;
  uint32_t unknown07 : 1;
  uint32_t padding00 : 24;
};

// Structures for tracking packets
struct GP_TRACKING {
  uint32_t ActIndex : 16; // lookup="@actindex"
  uint32_t Level : 8;
  uint32_t Type : 3;
  uint32_t unused : 5;
  int16_t x;
  int16_t z;
  char sName[16]; // save="@ActIndex"
};

enum GP_TRACKING_POS_STATE : uint32_t {
  GP_TRACKING_POS_STATE_NONE,
  GP_TRACKING_POS_STATE_START,
  GP_TRACKING_POS_STATE_LOSE,
  GP_TRACKING_POS_STATE_END
};

enum GP_TRACKING_STATE : uint32_t {
  GP_TRACKING_STATE_NONE,
  GP_TRACKING_STATE_LIST_START,
  GP_TRACKING_STATE_LIST_END,
  GP_TRACKING_STATE_ERR_ETC = 0x0A,
  GP_TRACKING_STATE_END
};

// Structures for myroom packet
enum GP_MYROOM_RESULT : uint32_t {
  GP_MYROOM_RESULT_OK,
  GP_MYROOM_RESULT_NG_PLANT_ADD_PARAM,
  GP_MYROOM_RESULT_NG_PLANT_CHECK_PARAM,
  GP_MYROOM_RESULT_NG_PLANT_CORP_PARAM,
  GP_MYROOM_RESULT_NG_PLANT_STOP_PARAM,
  GP_MYROOM_RESULT_NG_LAYOUT_PARAM,
  GP_MYROOM_RESULT_NG_BANKIN_PARAM,
  GP_MYROOM_RESULT_END
};

// Structures for bazaar packets
enum GP_BAZAAR_BUY_STATE : uint32_t {
  GP_BAZAAR_BUY_STATE_OK,
  GP_BAZAAR_BUY_STATE_ERR,
  GP_BAZAAR_BUY_STATE_END
};

enum GP_BAZAAR_SHOPPING_STATE : uint32_t {
  GP_BAZAAR_SHOPPING_STATE_ENTER,
  GP_BAZAAR_SHOPPING_STATE_EXIT,
  GP_BAZAAR_SHOPPING_STATE_END
};

// Structures for guild packets
struct _GP_GUILD_ITEM {
  uint16_t ItemNo; // lookup="items"
  uint8_t Count;
  uint8_t Max;
  int32_t Price;
};

struct GP_SHOP {
  uint32_t ItemPrice;
  uint16_t ItemNo; // lookup="items"
  uint8_t ShopIndex;
  uint8_t padding00;
  uint16_t Skill;
  uint16_t GuildInfo;
};

struct GP_MYROOM_GATE {
  uint8_t Result;
  uint8_t padding00[3];
};

// Structure for 0x0041 BLACK_LIST packet
struct SAVE_BLACK {
  uint32_t ID;
  char Name[16];
};

// Structures for 0x00B4 CONFIG packet
struct filters1_t {
  uint32_t say : 1;
  uint32_t shout : 1;
  uint32_t unused02 : 1;
  uint32_t emotes : 1;
  uint32_t special_actions_started_on_by_you : 1;
  uint32_t special_action_effects_on_by_you : 1;
  uint32_t attacks_by_you : 1;
  uint32_t missed_attacks_by_you : 1;
  uint32_t attacks_you_evade : 1;
  uint32_t damage_you_take : 1;
  uint32_t special_action_effects_on_by_npcs : 1;
  uint32_t attacks_by_npcs : 1;
  uint32_t missed_attacks_by_npcs : 1;
  uint32_t special_action_effects_on_by_party : 1;
  uint32_t attacks_by_party : 1;
  uint32_t missed_attacks_by_party : 1;
  uint32_t attacks_evaded_by_party : 1;
  uint32_t damage_taken_by_party : 1;
  uint32_t special_action_effects_on_by_allies : 1;
  uint32_t attacks_by_allies : 1;
  uint32_t missed_attacks_by_allies : 1;
  uint32_t attacks_evaded_by_allies : 1;
  uint32_t damage_taken_by_allies : 1;
  uint32_t special_actions_started_on_by_party : 1;
  uint32_t special_actions_started_on_by_allies : 1;
  uint32_t special_actions_started_on_by_npcs : 1;
  uint32_t others_synthesis_and_fishing_results : 1;
  uint32_t lot_results : 1;
  uint32_t attacks_by_others : 1;
  uint32_t missed_attacks_by_others : 1;
  uint32_t unused30 : 1;
  uint32_t unused31 : 1;
};

struct filters2_t {
  uint32_t attacks_evaded_by_others : 1;
  uint32_t damage_taken_by_others : 1;
  uint32_t special_action_effects_on_by_others : 1;
  uint32_t special_actions_started_on_by_others : 1;
  uint32_t attacks_by_foes : 1;
  uint32_t missed_attacks_by_foes : 1;
  uint32_t attacks_evaded_by_foes : 1;
  uint32_t damage_taken_by_foes : 1;
  uint32_t special_action_effects_on_by_foes : 1;
  uint32_t special_actions_started_on_by_foes : 1;
  uint32_t campaign_related_data : 1;
  uint32_t tell_messages_deemed_spam : 1;
  uint32_t shout_yell_messages_deemed_spam : 1;
  uint32_t unused13 : 1;
  uint32_t unused14 : 1;
  uint32_t job_specific_emote : 1;
  uint32_t yell : 1;
  uint32_t messages_from_alter_egos : 1;
  uint32_t unused18 : 1;
  uint32_t assist_j : 1;
  uint32_t assist_e : 1;
  uint32_t unused21 : 1;
  uint32_t unused22 : 1;
  uint32_t unused23 : 1;
  uint32_t unused24 : 1;
  uint32_t unused25 : 1;
  uint32_t unused26 : 1;
  uint32_t unused27 : 1;
  uint32_t unused28 : 1;
  uint32_t unused29 : 1;
  uint32_t unused30 : 1;
  uint32_t unused31 : 1;
};

struct SAVE_CONF {
  uint8_t InviteFlg : 1;
  uint8_t AwayFlg : 1;
  uint8_t AnonymityFlg : 1;
  uint8_t Language : 2;
  uint8_t unknown05 : 3;
  uint8_t unknown08 : 1;
  uint8_t unknown09 : 1;
  uint8_t unknown10 : 1;
  uint8_t SysMesFilterLevel : 2;
  uint8_t unknown13 : 1;
  uint8_t AutoTargetOffFlg : 1;
  uint8_t AutoPartyFlg : 1;
  uint8_t unknown16 : 8;
  uint8_t MentorUnlockedFlg : 1;
  uint8_t MentorFlg : 1;
  uint8_t NewAdventurerOffFlg : 1;
  uint8_t DisplayHeadOffFlg : 1;
  uint8_t unknown28 : 1;
  uint8_t RecruitFlg : 1;
  uint8_t unused : 2;
  filters1_t MassageFilter;
  filters2_t MassageFilter2;
  uint16_t PvpFlg;
  uint8_t AreaCode;
};

struct languages_t {
  uint8_t Japanese : 1;
  uint8_t English : 1;
  uint8_t German : 1;
  uint8_t French : 1;
  uint8_t Other : 1;
  uint8_t unused : 3;
};

// Structures for 0x004C AUC packet
struct GP_AUC_BOX {
  uint8_t Stat;
  uint8_t padding00;
  uint8_t ItemIndex;
  uint8_t padding01;
  char Name[16];
  uint16_t ItemNo; // lookup="items"
  uint8_t ItemQuantity;
  uint8_t ItemCategory;
  uint32_t Price;
  uint32_t MarketNo;
  uint32_t LotNo;
  uint32_t TimeStamp;
};

struct GP_AUC_PARAM_LOT {
  uint32_t LimitPrice;
  uint16_t ItemWorkIndex;
  uint16_t padding00;
  uint32_t ItemStacks;
};

struct GP_AUC_PARAM_BID {
  uint32_t BidPrice;
  uint16_t ItemNo; // lookup="items"
  uint16_t padding00;
  uint32_t ItemStacks;
};

struct GP_AUC_PARAM_SUMMARY {
  uint32_t Kind;
  uint16_t ItemNo; // lookup="items"
};

struct GP_AUC_PARAM_HISTORY {
  uint32_t Range;
  uint16_t ItemNo; // lookup="items"
};

struct GP_AUC_PARAM_ASKCOMMIT {
  uint32_t Commission;
  uint16_t ItemWorkIndex;
  uint16_t ItemNo; // lookup="items"
  uint32_t ItemStacks;
};

struct GP_AUC_PARAM_TRANS {
  uint16_t Signature;
  uint16_t TotalSize;
  uint16_t Offset;
  uint16_t Size;
  uint16_t FragmentNo;
  uint16_t TotalFragments;
};

struct GP_AUC_PARAM {
  union {
    GP_AUC_PARAM_LOT LotIn;
    GP_AUC_PARAM_BID Bid;
    GP_AUC_PARAM_SUMMARY Summary;
    GP_AUC_PARAM_HISTORY History;
    GP_AUC_PARAM_ASKCOMMIT AskCommit;
    GP_AUC_PARAM_TRANS Trans;
  } param;
};

// Structures for 0x004B PBX_RESULT packet
struct GC_PBOX_SEND {
  char To[16];
  uint32_t RequestID;
  uint32_t RequestTime;
  int32_t ItemWorkNo;
};

struct GC_PBOX_RECV {
  char From[16];
  uint32_t RequestID;
  uint32_t RequestTime;
  int32_t OpponentPBoxNo;
};

struct GC_PBOX {
  union {
    GC_PBOX_SEND Send;
    GC_PBOX_RECV Recv;
  } pbox;
};

struct GP_POST_BOX_STATE {
  uint32_t Stat;
  GC_PBOX box_state;
  uint16_t ItemNo; // lookup="items"
  uint16_t padding00;
  int32_t Kind;
  uint32_t Stack;
  uint8_t Data[28];
};

struct _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_2 {
  uint16_t ActIndex;       // lookup="@actindex"
  uint32_t UniqueNo;       // lookup="@uniqueno"
  uint16_t ActIndexFellow; // lookup="@actindex"
  uint16_t padding00;
  uint32_t NameFlags;
  uint32_t NameIcon;
  uint32_t CustomProperties;
  uint32_t unknown1C;
  uint32_t UniqueNoMog; // lookup="@uniqueno"
  uint8_t MogHouseFlag;
  uint8_t mjob_lv;
  uint8_t unknown26;
  uint8_t MogExpansionFlag;
};

struct _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_3 {
  uint16_t ActIndex;           // lookup="@actindex"
  uint32_t UniqueNo;           // lookup="@uniqueno"
  uint16_t ActIndexTrustOwner; // lookup="@actindex"
  uint16_t padding00;
  uint32_t NameFlags;
  char Name[15];
};

struct _GP_SERV_COMMAND_ENTITY_UPDATE_Mode_4 {
  uint16_t ActIndex;      // lookup="@actindex"
  uint32_t UniqueNo;      // lookup="@uniqueno"
  uint16_t ActIndexOwner; // lookup="@actindex"
  uint8_t Hpp;
  uint8_t Mpp;
  uint32_t Tp;
  uint32_t UniqueNoTarget; // lookup="@uniqueno"
  char Name[15];
};

struct _GP_SERV_COMMAND_RECIPE_Type_1 {
  uint16_t need_skill_1;
  uint16_t need_skill_2;
  uint16_t need_skill_3;
  uint16_t need_item; // lookup="items"
  uint16_t need_key_item;
  uint16_t itemnum[8]; // lookup="items"
  uint16_t itemcount[8];
};

struct _GP_SERV_COMMAND_RECIPE_Type_2 {
  uint16_t junk00[6];
  uint16_t itemnum[16]; // lookup="items"
};

struct _GP_SERV_COMMAND_RECIPE_Type_3 {
  uint16_t productitem; // lookup="items"
  uint16_t need_skill_1;
  uint16_t need_skill_2;
  uint16_t need_skill_3;
  uint16_t need_item; // lookup="items"
  uint16_t need_key_item;
  uint16_t itemnum[8]; // lookup="items"
  uint16_t itemcount[8];
};

struct _GP_SERV_COMMAND_ITEM_SUBCONTAINER_Data {
  uint8_t is_used;
  uint8_t container; // lookup="containers"
  uint8_t index;
  uint8_t unknown00;
  uint8_t unknown01[2];
  uint16_t model_id_race_hair;
  uint16_t model_id_head;
  uint16_t model_id_body;
  uint16_t model_id_hands;
  uint16_t model_id_legs;
  uint16_t model_id_feet;
  uint16_t model_id_main;
  uint16_t model_id_sub;
  uint16_t model_id_range;
};

struct _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_0 {
  uint8_t padding00;
  uint16_t ItemNo; // lookup="items"
  SAVE_EQUIP_KIND EquipKind;
};

struct _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_1 {
  uint8_t padding00[3];
  uint16_t ItemNo; // lookup="items"
  char sComLinkName[16];
  uint8_t sComColor[2];
  uint8_t job[2]; // lookup="jobs"
  uint8_t lvl[2];
  uint8_t mjob; // lookup="jobs"
  uint8_t mlvl;
  uint8_t mflags;
  uint8_t padding01[3];
  uint32_t BallistaChevronCount;
  uint8_t BallistaChevronFlags;
  uint8_t padding02;
  uint16_t BallistaFlags;
  uint32_t MesNo;
  int32_t Params[5];
  uint8_t padding03[8];
};

struct _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_2 {
  uint16_t ItemNo[8]; // lookup="items"
  uint8_t EquipKind[8];
};

struct _GP_SERV_COMMAND_EQUIP_INSPECT_Mode_3 {
  uint8_t EquipCount;
  checkitem_t Equip[16];
};

struct equipsetrequestitem_t {
  uint8_t HasItemFlg : 1;
  uint8_t RemoveItemFlg : 1;
  uint8_t Category : 6; // lookup="containers"
  uint8_t ItemIndex;
  uint16_t ItemNo; // lookup="items"
};

struct equipsetitem_t {
  uint8_t ItemIndex;
  uint8_t EquipKind; // lookup="equipslot"
  uint8_t Category;  // lookup="containers"
  uint8_t padding00;
};

struct jobemotes_t {
  uint32_t WAR : 1;
  uint32_t MNK : 1;
  uint32_t WHM : 1;
  uint32_t BLM : 1;
  uint32_t RDM : 1;
  uint32_t THF : 1;
  uint32_t PLD : 1;
  uint32_t DRK : 1;
  uint32_t BST : 1;
  uint32_t BRD : 1;
  uint32_t RNG : 1;
  uint32_t SAM : 1;
  uint32_t NIN : 1;
  uint32_t DRG : 1;
  uint32_t SMN : 1;
  uint32_t BLU : 1;
  uint32_t COR : 1;
  uint32_t PUP : 1;
  uint32_t DNC : 1;
  uint32_t SCH : 1;
  uint32_t GEO : 1;
  uint32_t RUN : 1;
  uint32_t unused : 10;
};

// PS2: (New; did not exist.)
struct chairemotes_t {
  uint16_t ImperialChair : 1;     // Chair: Imperial Chair
  uint16_t DecorativeChair : 1;   // Chair: Decorative Chair
  uint16_t OrnateStool : 1;       // Chair: Ornate Stool
  uint16_t RefinedChair : 1;      // Chair: Refined Chair
  uint16_t PortableContainer : 1; // Chair: Portable Container
  uint16_t ChocoboChair : 1;      // Chair: Chocobo Chair
  uint16_t EphramadianThrone : 1; // Chair: Ephramadian Throne
  uint16_t ShadowThrone : 1;      // Chair: Shadow Throne
  uint16_t LeafBench : 1;         // Chair: Leaf Bench
  uint16_t AstralCube : 1;        // Chair: Astral Cube
  uint16_t ChocoboChairII : 1;    // Chair: Chocobo Chair II
  uint16_t unused : 5;
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_0_t {
  uint16_t model_id;
  char name[16];
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_5_t {
  uint16_t model_id;
  char name[16];
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_6_t {
  uint16_t model_id;
  char name[16];
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_1_t {
  uint16_t GrapIDTbl[9];
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_7_t {
  uint16_t GrapIDTbl[9];
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_2_t {
  uint16_t unused;
  uint32_t DoorId;
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_3_t {
  uint16_t unused;
  uint32_t DoorId;
  uint32_t Time;
  uint32_t EndTime;
};

struct _GP_SERV_COMMAND_CHAR_NPC_SubKind_4_t {
  uint16_t unused;
  uint32_t DoorId;
  uint32_t Time;
  uint32_t EndTime;
};

struct joblevels_t {
  uint8_t WAR;
  uint8_t MNK;
  uint8_t WHM;
  uint8_t BLM;
  uint8_t RDM;
  uint8_t THF;
  uint8_t PLD;
  uint8_t DRK;
  uint8_t BST;
  uint8_t BRD;
  uint8_t RNG;
  uint8_t SAM;
  uint8_t NIN;
  uint8_t DRG;
  uint8_t SMN;
  uint8_t BLU;
  uint8_t COR;
  uint8_t PUP;
  uint8_t DNC;
  uint8_t SCH;
  uint8_t GEO;
  uint8_t RUN;
};

struct chocobo_t {
  uint8_t unk1;
  uint8_t unk2;
  uint8_t unk3;
  uint8_t unk4;
};

struct flags37_0_t {
  uint32_t HideFlag : 1;
  uint32_t SleepFlag : 1;
  uint32_t GroundFlag : 1;
  uint32_t CliPosInitFlag : 1;
  uint32_t LfgFlag : 1;
  uint32_t AnonymousFlag : 1;
  uint32_t CfhFlag : 1;
  uint32_t AwayFlag : 1;
  uint32_t Gender : 1;
  uint32_t unknown_1_9 : 1;
  uint32_t unknown_1_10 : 1;
  uint32_t GraphSize : 2;
  uint32_t Chocobo_Index : 3;
  uint32_t hpp : 8;
  uint32_t PlayOnelineFlag : 1;
  uint32_t LinkShellFlag : 1;
  uint32_t LinkDeadFlag : 1;
  uint32_t TargetOffFlag : 1;
  uint32_t unknown_3_28 : 1;
  uint32_t GmLevel : 3;
};

struct flags37_1_t {
  uint32_t Speed : 12;
  uint32_t Hackmove : 1;
  uint32_t FreezeFlag : 1;
  uint32_t unknown_1_14 : 1;
  uint32_t InvisFlag : 1;
  uint32_t GateBreachFlg : 1;
  uint32_t SpeedBase : 8;
  uint32_t unknown_3_25 : 4;
  uint32_t BazaarFlag : 1;
  uint32_t CharmFlag : 1;
  uint32_t GmIconFlag : 1;
};

struct flags37_2_t {
  uint32_t NamedFlag : 1;
  uint32_t SingleFlag : 1;
  uint32_t AutoPartyFlag : 1;
  uint32_t PetIndex : 16;
  uint32_t MotStopFlag : 1;
  uint32_t CliPriorityFlag : 1;
  uint32_t BallistaFlg : 8;
  uint32_t unknown_3_29 : 3;
};

struct flags37_3_t {
  uint32_t LfgMasterFlag : 1;
  uint32_t TrialFlag : 1;
  uint32_t unknown_0_2 : 1;
  uint32_t NewCharacterFlag : 1;
  uint32_t MentorFlag : 1;
  uint32_t unknown_0_5 : 1;
  uint32_t unknown_0_6 : 1;
  uint32_t unknown_0_7 : 1;
  uint32_t BallistaTeam : 8;
  uint32_t unknown_2_16 : 16;
};

struct flags37_4_t {
  uint8_t GeoIndiElement : 4;
  uint8_t GeoIndiSize : 2;
  uint8_t GeoIndiFlag : 1;
  uint8_t JobMasterFlag : 1;
};

struct flags37_5_t {
  uint8_t unknown_0_0 : 2;
  uint8_t unknown_0_2 : 2;
  uint8_t unknown_0_4 : 4;
};

struct flags37_6_t {
  uint32_t unknown_0_0 : 1;
  uint32_t unknown_0_1 : 1;
  uint32_t unknown_0_2 : 1;
  uint32_t unknown_0_3 : 1;
  uint32_t unknown_0_4 : 1;
  uint32_t unknown_0_5 : 1;
  uint32_t unknown_0_6 : 1;
  uint32_t unknown_0_7 : 25;
};

struct status_bits_t {
  uint8_t Status1 : 2;
  uint8_t Status2 : 2;
  uint8_t Status3 : 2;
  uint8_t Status4 : 2;
  uint8_t Status5 : 2;
  uint8_t Status6 : 2;
  uint8_t Status7 : 2;
  uint8_t Status8 : 2;
  uint8_t Status9 : 2;
  uint8_t Status10 : 2;
  uint8_t Status11 : 2;
  uint8_t Status12 : 2;
  uint8_t Status13 : 2;
  uint8_t Status14 : 2;
  uint8_t Status15 : 2;
  uint8_t Status16 : 2;
  uint8_t Status17 : 2;
  uint8_t Status18 : 2;
  uint8_t Status19 : 2;
  uint8_t Status20 : 2;
  uint8_t Status21 : 2;
  uint8_t Status22 : 2;
  uint8_t Status23 : 2;
  uint8_t Status24 : 2;
  uint8_t Status25 : 2;
  uint8_t Status26 : 2;
  uint8_t Status27 : 2;
  uint8_t Status28 : 2;
  uint8_t Status29 : 2;
  uint8_t Status30 : 2;
  uint8_t Status31 : 2;
  uint8_t Status32 : 2;
};

struct _GP_SERV_COMMAND_JOB_EXTRA_DATA_PUP {
  uint8_t padding00[2];
  uint8_t AutomatonHead;
  uint8_t AutomatonFrame;
  uint8_t EquippedAttachments[12];
  uint16_t padding01;
  uint32_t UnlockedHeads;
  uint32_t UnlockedFrames;
  uint8_t padding02[24];
  uint32_t UnlockedAttachments[8];
  char AutomatonName[16];
  uint16_t AutomatonHP;
  uint16_t AutomatonMaxHP;
  uint16_t AutomatonMP;
  uint16_t AutomatonMaxMP;
  uint16_t MeleeSkill;
  uint16_t MeleeSkillCap;
  uint16_t RangedSkill;
  uint16_t RangedSkillCap;
  uint16_t MagicSkill;
  uint16_t MagicSkillCap;
  uint8_t padding03[10];
  uint16_t BaseSTR;
  uint16_t BonusSTR;
  uint16_t BaseDEX;
  uint16_t BonusDEX;
  uint16_t BaseVIT;
  uint16_t BonusVIT;
  uint16_t BaseAGI;
  uint16_t BonusAGI;
  uint16_t BaseINT;
  uint16_t BonusINT;
  uint16_t BaseMND;
  uint16_t BonusMND;
  uint16_t BaseCHR;
  uint16_t BonusCHR;
  uint8_t ElemCapacity;
};

struct _GP_SERV_COMMAND_JOB_EXTRA_DATA_BLU {
  uint8_t padding00[2];
  uint8_t EquippedSpells[20];
};

struct _GP_SERV_COMMAND_JOB_EXTRA_DATA_MON {
  uint8_t padding00[2];
  uint16_t SpeciesId;
  uint16_t EquippedInstincts[12];
};

struct coalitionranks_t {
  uint32_t Pioneers : 4;
  uint32_t Peacekeepers : 4;
  uint32_t Couriers : 4;
  uint32_t Scouts : 4;
  uint32_t Inventors : 4;
  uint32_t Mummers : 4;
  uint32_t unused : 8;
};

struct colonizationzone_t {
  uint32_t ColonizationRate : 7;
  uint32_t CurrentBivouacs : 3;
  uint32_t MaxBivouacs : 3;
  uint32_t unused : 19;
};

struct colonizationzones_t {
  colonizationzone_t unused;
  colonizationzone_t YahseHuntingGrounds;
  colonizationzone_t CeizakBattlegrounds;
  colonizationzone_t ForetDeHennetiel;
  colonizationzone_t YorciaWeald;
  colonizationzone_t MorimarBasaltFields;
  colonizationzone_t MarjamiRavine;
  colonizationzone_t KamihrDrifts;
  colonizationzone_t RaKaznar;
};

struct _GP_SERV_COMMAND_CAMPAIGN_MAP_Mode_3 {
  uint8_t padding00;
  uint8_t Length;
  uint8_t padding01;
  uint32_t unknown00;
  uint32_t unknown01;
  coalitionranks_t Ranks;
  colonizationzones_t Zones;
  int32_t Bayld;
};
struct campaigncontrolledareas_t {
  uint32_t Sandoria : 5;
  uint32_t Bastok : 5;
  uint32_t Windurst : 5;
  uint32_t Beastman : 5;
  uint32_t unused : 12;
};

struct campaignnation_t {
  uint32_t Reconnaissance : 4;
  uint32_t unused : 14;
  uint32_t Morale : 7;
  uint32_t Prosperity : 7;
};

struct campaignnations_t {
  campaignnation_t Sandoria;
  campaignnation_t Bastok;
  campaignnation_t Windurst;
  campaignnation_t BeastmanOrc;
  campaignnation_t BeastmanQuadav;
  campaignnation_t BeastmanYagudo;
  campaignnation_t BeastmanDarkKindred;
};

struct campaignzone_t {
  uint32_t unused00 : 1;
  uint32_t Owner : 3;
  uint32_t CurrentFortifications : 10;
  uint32_t CurrentResources : 10;
  uint32_t Heroism : 8;
  uint8_t InfluenceSandoria;
  uint8_t InfluenceBastok;
  uint8_t InfluenceWindurst;
  uint8_t InfluenceBeastman;
  uint32_t MaxFortifications : 10;
  uint32_t MaxResources : 10;
  uint32_t unused01 : 12;
};

struct _GP_SERV_COMMAND_CAMPAIGN_MAP_Mode_2 {
  uint8_t padding00;
  uint8_t Length;
  uint8_t padding01;
  uint8_t padding02;
  uint8_t ZoneOffset;
  uint8_t padding03[2];
  int32_t AlliedNotes;
  campaigncontrolledareas_t ControlledAreas;
  campaignnations_t Nations;
  campaignzone_t Zones[13];
};

struct _GP_SERV_COMMAND_MULTI_DATA_merit
{
    uint8_t unknown[128];
};

struct _GP_SERV_COMMAND_MULTI_DATA_mon1
{
    uint32_t    data;
    uint32_t    flags;
    uint16_t    unknown00; // Unused.
    uint16_t    infamy;
    uint32_t    prestige;
    uint32_t    unknown01; // Unused.
    uint8_t     instincts[64];
    uint8_t     levels[128];
};

struct _GP_SERV_COMMAND_MULTI_DATA_mon2
{
    uint8_t     unknown00[128];
    uint32_t    unknown01[3];
    uint32_t    unknown02[8];
};

struct jobpointentry_t
{
    uint16_t        capacity_points;
    uint16_t        points;
    uint16_t        points_spent;
};

struct _GP_SERV_COMMAND_MULTI_DATA_job_points
{
    uint8_t         flags;
    uint8_t         unknown00[3];
    jobpointentry_t jobs[24];
};

struct _GP_SERV_COMMAND_MULTI_DATA_homepoints
{
    uint32_t home_point[4];
    uint32_t survival_guide[4];
    uint32_t waypoint[4];
    uint32_t telepoint;
    uint32_t atmos;
    uint32_t eschan_portal;
    uint32_t unknown00;     // Unsure if Eschal Portal uses this as well.
};

struct _GP_SERV_COMMAND_MULTI_DATA_unity {
    uint8_t unknown[128];
};

struct _GP_SERV_COMMAND_MULTI_DATA_status_icons
{
    int16_t     icon[32];
    uint32_t    timestamp[32];
};

struct partymemberbuffs_t
{
    uint32_t    UniqueNo;
    uint16_t    ActIndex;
    uint16_t    padding00;
    uint64_t    Bits;
    uint8_t     Buffs[32];
};

struct jobpoint_t
{
    uint16_t    index: 5;
    uint16_t    job_no: 11; // lookup="jobs"
    uint16_t    next: 10;
    uint16_t    level: 6;
};

struct _GP_SERV_COMMAND_CHOCOBO_RACING_Mode_1 {
  uint8_t padding00[3];
  uint32_t RaceParams[2];
  uint8_t junk00[4];
};

struct _GP_SERV_COMMAND_CHOCOBO_RACING_Mode_2 {
  uint8_t ParamIndex;
  uint8_t ParamSize;
  uint8_t padding00;
  uint8_t ParamData[192];
};

struct _GP_SERV_COMMAND_CHOCOBO_RACING_Mode_4 {
  uint8_t padding00;
  uint8_t ParamSize;
  uint8_t padding01;
  uint8_t ParamData1[192];
};
