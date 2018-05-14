#include "TES3Cell.h"

#define TES3_Cell_getExteriorGridX 0x4DB9D0
#define TES3_Cell_getExteriorGridY 0x4DB9F0

#define TES3_Cell_getFirstObjectOfType 0x4DBEF0

#define TES3_Cell_addReference 0x4DC0A0

namespace TES3 {
	Reference * Cell::getFirstObjectOfType(ObjectType::ObjectType type, bool skipDeleted = true) {
		return reinterpret_cast<Reference*(__thiscall *)(Cell*, int, unsigned char)>(TES3_Cell_getFirstObjectOfType)(this, type, skipDeleted);
	}

	int Cell::getGridX() {
		return reinterpret_cast<int(__thiscall *)(Cell*)>(TES3_Cell_getExteriorGridX)(this);
	}

	int Cell::getGridY() {
		return reinterpret_cast<int(__thiscall *)(Cell*)>(TES3_Cell_getExteriorGridY)(this);
	}

	bool Cell::getCellFlag(unsigned int flag) {
		return (cellFlags & flag);
	}

	void Cell::setCellFlag(unsigned int flag, bool value) {
		if (value) {
			cellFlags |= flag;
		}
		else {
			cellFlags &= ~flag;
		}
	}

	int Cell::getFogDensity() {
		if (cellFlags & CellFlag::Interior) {
			return VariantData.interior.fogDensity;
		}
		else {
			return -1;
		}
	}

	void Cell::setFogDensity(int value) {
		if (cellFlags & CellFlag::Interior) {
			VariantData.interior.fogDensity = value;
		}
	}

	int Cell::getWaterLevel() {
		if (cellFlags & CellFlag::Interior) {
			return waterLevelOrRegion.waterLevel;
		}
		else {
			return -1;
		}
	}

	void Cell::setWaterLevel(int value) {
		if (cellFlags & CellFlag::Interior) {
			waterLevelOrRegion.waterLevel = value;
		}
	}

	Region * Cell::getRegion() {
		return waterLevelOrRegion.region;
	}
}
