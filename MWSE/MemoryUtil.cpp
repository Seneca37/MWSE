#include "MemoryUtil.h"

#include "MemAccess.h"

#include "Log.h"

namespace mwse {
	void genJump(DWORD Address, DWORD To) {
		MemAccess<unsigned char>::Set(Address, 0xE9);
		MemAccess<DWORD>::Set(Address + 1, To - Address - 0x5);
	}

	void genCall(DWORD Address, DWORD To) {
		MemAccess<unsigned char>::Set(Address, 0xE8);
		MemAccess<DWORD>::Set(Address + 1, To - Address - 0x5);
	}

	void genNOP(DWORD Address) {
		MemAccess<unsigned char>::Set(Address, 0x90);
	}

	void genJumpUnprotected(DWORD address, DWORD to, DWORD size) {
		// Unprotect memory.
		DWORD oldProtect;
		VirtualProtect((DWORD*)address, size, PAGE_READWRITE, &oldProtect);

		// Create our call.
		MemAccess<unsigned char>::Set(address, 0xE9);
		MemAccess<DWORD>::Set(address + 1, to - address - 0x5);

		// NOP out the rest of the block.
		for (DWORD i = address + 5; i < address + size; i++) {
			genNOP(i);
		}

		// Protect memory again.
		VirtualProtect((DWORD*)address, size, oldProtect, &oldProtect);
	}

	void genCallUnprotected(DWORD address, DWORD to, DWORD size) {
		// Unprotect memory.
		DWORD oldProtect;
		VirtualProtect((DWORD*)address, size, PAGE_READWRITE, &oldProtect);

		// Create our call.
		MemAccess<unsigned char>::Set(address, 0xE8);
		MemAccess<DWORD>::Set(address + 1, to - address - 0x5);

		// NOP out the rest of the block.
		for (DWORD i = address + 5; i < address + size; i++) {
			genNOP(i);
		}

		// Protect memory again.
		VirtualProtect((DWORD*)address, size, oldProtect, &oldProtect);
	}

	bool genCallEnforced(DWORD address, DWORD previousTo, DWORD to, DWORD size) {
		// Read previous call address to make sure it's what we are expecting.
		DWORD currentCallAddress = *reinterpret_cast<DWORD*>(address + 1) + address + 0x5;
		if (currentCallAddress != previousTo) {
#if _DEBUG
			log::getLog() << "[MemoryUtil] Skipping call generation at 0x" << std::hex << address << ". Expected previous call to 0x" << previousTo << ", found 0x" << currentCallAddress << "." << std::endl;
#endif
			return false;
		}

		// Unprotect memory.
		DWORD oldProtect;
		VirtualProtect((DWORD*)address, size, PAGE_READWRITE, &oldProtect);

		// Create our call.
		MemAccess<unsigned char>::Set(address, 0xE8);
		MemAccess<DWORD>::Set(address + 1, to - address - 0x5);

		// NOP out the rest of the block.
		for (DWORD i = address + 5; i < address + size; i++) {
			genNOP(i);
		}

		// Protect memory again.
		VirtualProtect((DWORD*)address, size, oldProtect, &oldProtect);

		return true;
	}

	void overrideVirtualTable(DWORD address, DWORD offset, DWORD to) {
		DWORD location = address + offset;

		// Unprotect memory.
		DWORD oldProtect;
		VirtualProtect((DWORD*)location, 0x4, PAGE_READWRITE, &oldProtect);

		// Create our call.
		MemAccess<DWORD>::Set(location, to);

		// Protect memory again.
		VirtualProtect((DWORD*)location, 0x4, oldProtect, &oldProtect);
	}
}