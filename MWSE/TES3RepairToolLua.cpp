#include "TES3RepairToolLua.h"

#include "LuaManager.h"

#include "TES3RepairTool.h"
#include "TES3Script.h"

namespace mwse {
	namespace lua {
		void bindTES3RepairTool() {
			LuaManager::getInstance().getState().new_usertype<TES3::RepairTool>("TES3RepairTool",
				// Disable construction of this type.
				"new", sol::no_constructor,

				//
				// Properties.
				//

				"objectType", &TES3::RepairTool::objectType,

				"id", sol::readonly_property(&TES3::RepairTool::getObjectID),
				"name", sol::property(&TES3::RepairTool::getName, &TES3::RepairTool::setName),

				"icon", sol::readonly_property(&TES3::RepairTool::getIconPath),
				"model", sol::readonly_property(&TES3::RepairTool::getModelPath),

				"value", sol::readonly_property(&TES3::RepairTool::getValue),
				"weight", sol::readonly_property(&TES3::RepairTool::getWeight),
				"quality", &TES3::RepairTool::quality,
				"condition", &TES3::RepairTool::maxCondition,

				"script", sol::readonly_property(&TES3::RepairTool::getScript)

				);
		}
	}
}