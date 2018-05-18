#pragma once

#include "sol.hpp"

#include "TES3Object.h"

#include "TES3Util.h"

#include <unordered_map>

namespace mwse {
	namespace lua {
		template <typename T>
		T getOptionalParam(sol::optional<sol::table> maybeParams, const char* key, T defaultValue) {
			T value = defaultValue;

			if (maybeParams) {
				sol::table params = maybeParams.value();
				sol::object maybeValue = params[key];
				if (maybeValue.valid() && maybeValue.is<T>()) {
					value = maybeValue.as<T>();
				}
			}

			return value;
		}

		template <typename T>
		T* getOptionalParamObject(sol::optional<sol::table> maybeParams, const char* key) {
			T* value = NULL;

			if (maybeParams) {
				sol::table params = maybeParams.value();
				sol::object maybeValue = params[key];
				if (maybeValue.valid()) {
					if (maybeValue.is<std::string>()) {
						value = tes3::getObjectById<T>(maybeValue.as<std::string>().c_str());
					}
					else if (maybeValue.is<T*>()) {
						value = maybeValue.as<T*>();
					}
				}
			}

			return value;
		}

		TES3::Script* getOptionalParamExecutionScript(sol::optional<sol::table> maybeParams);
		TES3::Reference* getOptionalParamExecutionReference(sol::optional<sol::table> maybeParams);
		TES3::Script* getOptionalParamScript(sol::optional<sol::table> maybeParams, const char* key);
		TES3::Reference* getOptionalParamReference(sol::optional<sol::table> maybeParams, const char* key);
		TES3::Spell* getOptionalParamSpell(sol::optional<sol::table> maybeParams, const char* key);
		TES3::DialogueInfo* getOptionalParamTopic(sol::optional<sol::table> maybeParams, const char* key);
		TES3::Sound* getOptionalParamSound(sol::optional<sol::table> maybeParams, const char* key);

		static std::unordered_map<unsigned long, sol::object> userdataMap;

		sol::object makeLuaObject(TES3::BaseObject* object);
		sol::object makeLuaObject(TES3::MobileObject* object);
	}
}
