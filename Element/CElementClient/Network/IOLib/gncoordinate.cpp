#include "gncoordinate.h"
//#include <assert.h>

namespace 
{
	enum    
	{
		PLAYER_INFO_1,
		PLAYER_INFO_2,
		PLAYER_INFO_3,
		PLAYER_INFO_4,
		PLAYER_INFO_1_LIST,
		PLAYER_INFO_2_LIST,
		PLAYER_INFO_3_LIST,
		PLAYER_INFO_23_LIST,
		SELF_INFO_1,
		NPC_INFO_LIST,
		MATTER_INFO_LIST,
		NPC_ENTER_SLICE,
		PLAYER_ENTER_SLICE,
		OBJECT_LEAVE_SLICE,             
		OBJECT_NOTIFY_POS,
		OBJECT_MOVE,
		NPC_ENTER_WORLD,
		PLAYER_ENTER_WORLD,
		MATTER_ENTER_WORLD,
		PLAYER_LEAVE_WORLD,
		NPC_DEAD,
		OBJECT_DISAPPEAR,
		OBJECT_START_ATTACK, 
		SELF_STOP_ATTACK,
		SELF_ATTACK_RESULT,
		ERROR_MESSAGE,
		BE_ATTACKED,
		PLAYER_DEAD,
		BE_KILLED,
		PLAYER_REVIVAL,
		PICKUP_MONEY,
		PICKUP_ITEM,
		PLAYER_INFO_00,
		NPC_INFO_00,
		OUT_OF_SIGHT_LIST,
		OBJECT_STOP_MOVE, 
		RECEIVE_EXP,
		LEVEL_UP,
		SELF_INFO_00,
		UNSELECT,
		SELF_ITEM_INFO,
		SELF_ITEM_EMPTY_INFO,
		SELF_INVENTORY_DATA,
		SELF_INVENTORY_DETAIL_DATA,
		EXCHANGE_INVENTORY_ITEM,
		MOVE_INVENTORY_ITEM, 
		PLAYER_DROP_ITEM,
		EXCHANGE_EQUIPMENT_ITEM,
		EQUIP_ITEM,
		MOVE_EQUIPMENT_ITEM,
		SELF_GET_EXT_PROPERTY,
		SET_STATUS_POINT,
		SELECT_TARGET,
		PLAYER_EXTPROP_BASE,
		PLAYER_EXTPROP_MOVE,
		PLAYER_EXTPROP_ATTACK,
		PLAYER_EXTPROP_DEFENSE,
		TEAM_LEADER_INVITE,
		TEAM_REJECT_INVITE,
		TEAM_JOIN_TEAM,
		TEAM_MEMBER_LEAVE,
		TEAM_LEAVE_PARTY,
		TEAM_NEW_MEMBER,
		TEAM_LEADER_CANCEL_PARTY,
		TEAM_MEMBER_DATA,
		TEAMMATE_POS, 
		EQUIPMENT_DATA,
		EQUIPMENT_INFO_CHANGED,
		EQUIPMENT_DAMAGED, 
		TEAM_MEMBER_PICKUP, 
		NPC_GREETING,
		NPC_SERVICE_CONTENT,
		PURCHASE_ITEM,
		ITEM_TO_MONEY,
		REPAIR_ALL,
		REPAIR,
		RENEW,
		SPEND_MONEY,
		PICKUP_MONEY_IN_TRADE,
		PICKUP_ITEM_IN_TRADE,
		PICKUP_MONEY_AFTER_TRADE,
		PICKUP_ITEM_AFTER_TRADE,
		GET_OWN_MONEY,
		OBJECT_ATTACK_ONCE,
		SELF_START_ATTACK,
		OBJECT_CAST_SKILL,
		SKILL_INTERRUPTED,
		SELF_SKILL_INTERRUPTED,
		SKILL_PERFORM,
		OBJECT_BE_ATTACKED,
		SKILL_DATA,
		PLAYER_USE_ITEM,
		EMBED_ITEM,
		CLEAR_EMBEDDED_CHIP,                    
		COST_SKILL_POINT,
		LEARN_SKILL,
		OBJECT_TAKEOFF,
		OBJECT_LANDING,
		FLYSWORD_TIME_CAPACITY,                 
		OBTAIN_ITEM,
		PRODUCE_START,
		PRODUCE_ONCE,
		PRODUCE_END,
		DECOMPOSE_START,                        
		DECOMPOSE_END,
		TASK_DATA,
		TASK_VAR_DATA,
		OBJECT_START_USE,
		OBJECT_CANCEL_USE,                      
		OBJECT_USE_ITEM,
		OBJECT_START_USE_WITH_TARGET,
		OBJECT_SIT_DOWN,
		OBJECT_STAND_UP,
		OBJECT_DO_EMOTE,
		SERVER_TIMESTAMP,
		NOTIFY_ROOT,
		DISPEL_ROOT,
		INVADER_RISE,
		PARIAH_RISE,
		INVADER_FADE,
		OBJECT_ATTACK_RESULT,
		BE_HURT,
		HURT_RESULT,
		SELF_STOP_SKILL,
		UPDATE_VISIBLE_STATE,
		OBJECT_STATE_NOTIFY,
		PLAYER_GATHER_START,
		PLAYER_GATHER_STOP,
		TRASHBOX_PASSWD_CHANGED,
		TRASHBOX_PASSWD_STATE,
		TRASHBOX_OPEN,
		TRASHBOX_CLOSE,
		TRASHBOX_WEALTH,
		EXCHANGE_TRASHBOX_ITEM,
		MOVE_TRASHBOX_ITEM,
		EXCHANGE_TRASHBOX_INVENTORY,
		INVENTORY_ITEM_TO_TRASH,
		TRASH_ITEM_TO_INVENTORY,
		EXCHANGE_TRASH_MONEY,
		ENCHANT_RESULT,
		SELF_NOTIFY_ROOT,
		OBJECT_DO_ACTION,
		SELF_SKILL_ATTACK_RESULT,
		OBJECT_SKILL_ATTACK_RESULT,
		BE_SKILL_ATTACKED,
		PLAYER_SET_ADV_DATA,
		PLAYER_CLR_ADV_DATA,
		PLAYER_IN_TEAM,
		TEAM_APPLY_REQUEST,
		OBJECT_DO_EMOTE_RESTORE,
		CONCURRENT_EMOTE_REQUEST, 
		DO_CONCURRENT_EMOTE,
		MATTER_PICKUP,
	};
}

namespace GNET
{
int GetFirstVector( int type, const char * data, int len)
{
	switch(type)
	{
		case PLAYER_INFO_1:
		case SELF_INFO_1:
		case PLAYER_ENTER_SLICE:
		case PLAYER_ENTER_WORLD:
			return 6;
		case PLAYER_INFO_1_LIST:
			return 8;
		case NPC_INFO_LIST:
			return 12;
		case MATTER_INFO_LIST:
			return 12;

		case MATTER_ENTER_WORLD:
			return 10;

		case NPC_ENTER_SLICE:
		case NPC_ENTER_WORLD:
			return 10;
		case OBJECT_LEAVE_SLICE:
			return 6;
		case OBJECT_MOVE:
			return 6;
		case OBJECT_STOP_MOVE:
			return 6;
		case NOTIFY_ROOT:
			return 6;
		case SELF_NOTIFY_ROOT:
			return 2;
		default:
			return -1;
	}
}

int GetNextVector( int type, const char * data, int len)
{
	switch(type)
	{
		case PLAYER_INFO_1_LIST:
		{
			short state = *(short*)(data + 5);
			int offset = 0;
			if(state & 0x800) offset += 5;		//帮派
			if(state & 0x400) offset += 8;		//广告
			if(state & 0x001) offset += 1;		//变身
			if(state & 0x002) offset += 1;		//表情
			if(state & 0x040) offset += 4;		//扩展属性
			offset += 7;
			//assert( offset <= len);
			offset += 4;
			if(offset < len )
				return offset;
			else 
				return -1;
			
		}
		break;
		case NPC_INFO_LIST:
		{
			short state = *(short*)(data + 3);
			int offset = 0;
			if(state & 0x040) offset += 4;
			offset += 5;
			//assert( offset <= len);
			offset += 8;
			if(offset < len )
				return offset;
			else 
				return -1;
			
		}
		break;
		case MATTER_INFO_LIST:
		{
			if(len > 8 )
				return 8;
			else 
				return -1;
			
		}
		break;
		default:
			return -1;
	}

}
}

