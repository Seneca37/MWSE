/************************************************************************
	
	xGetWeight.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
	
**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"
#include "Reference.h"

using namespace mwse;

namespace mwse {
	class xGetWeight : mwse::InstructionInterface_t {
	public:
		xGetWeight();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xGetWeight xGetWeightInstance;

	xGetWeight::xGetWeight() : mwse::InstructionInterface_t(OpCode::xGetWeight) {}

	void xGetWeight::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xGetWeight::execute(mwse::VMExecuteInterface &virtualMachine) {
		// Get reference.
		REFRRecord_t* reference = virtualMachine.getReference();
		if (reference == NULL) {
#if _DEBUG
			mwse::log::getLog() << "xGetWeight: No reference provided." << std::endl;
#endif
			mwse::Stack::getInstance().pushFloat(0.0f);
			return 0.0f;
		}

		// Get weight.
		mwFloat_t weight = 0.0f;
		try {
			weight = tes3::getWeight(reference, true);
		}
		catch (std::exception& e) {
#if _DEBUG
			mwse::log::getLog() << "xGetWeight: " << e.what() << std::endl;
#endif
			mwse::Stack::getInstance().pushFloat(0.0f);
			return 0.0f;
		}

		mwse::Stack::getInstance().pushFloat(weight);

		return 0.0f;
	}
}