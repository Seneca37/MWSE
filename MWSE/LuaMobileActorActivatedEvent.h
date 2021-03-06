#pragma once

#include "LuaObjectFilteredEvent.h"
#include "LuaDisableableEvent.h"

namespace mwse {
	namespace lua {
		namespace event {
			class MobileActorActivatedEvent : public ObjectFilteredEvent, public DisableableEvent<MobileActorActivatedEvent> {
			public:
				MobileActorActivatedEvent(TES3::Reference * reference);
				sol::table createEventTable();

			protected:
				TES3::Reference* m_Reference;
			};
		}
	}
}
