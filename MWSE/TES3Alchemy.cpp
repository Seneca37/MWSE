#include "TES3Alchemy.h"

namespace TES3 {
	size_t Alchemy::getActiveEffectCount() {
		size_t count = 0;
		for (size_t i = 0; i < 8; i++) {
			if (effects[i].effectID != TES3::EffectID::None) {
				count++;
			}
		}
		return count;
	}

	int Alchemy::getFirstIndexOfEffect(int effectId) {
		for (size_t i = 0; i < 8; i++) {
			if (effects[i].effectID = effectId) {
				return i;
			}
		}
		return -1;
	}

	bool Alchemy::effectsMatchWith(Alchemy * other) {
		for (size_t i = 0; i < 8; i++) {
			if (effects[i].matchesEffectsWith(&other->effects[i])) {
				return false;
			}
		}
		return true;
	}
}
