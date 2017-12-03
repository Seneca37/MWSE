/************************************************************************
	
	xSetCondition.cpp - Copyright (c) 2008 The MWSE Project
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

namespace mwse
{
	class xSetCondition : mwse::InstructionInterface_t
	{
	public:
		xSetCondition();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xSetConditionOpcode = 0x3E64;
	static xSetCondition xSetConditionInstance;

	xSetCondition::xSetCondition() : mwse::InstructionInterface_t(xSetConditionOpcode) {}

	void xSetCondition::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xSetCondition::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		// Get parameter.
		mwLong_t value = Stack::getInstance().popLong();

		// Get reference.
		REFRRecord_t* reference = virtualMachine.getReference();
		if (reference == NULL) {
			log::getLog() << "xSetCondition: No reference provided." << std::endl;
			Stack::getInstance().pushShort(0);
			return 0.0f;
		}

		// Get associated varnode, and the condition from it.
		mwVarHolderNode_t* varNode = tes3::getAttachedVarHolderNode(reference);
		if (varNode != NULL) {
			varNode->unknown_0x0C = value;
		}
		else {
			log::getLog() << "xSetCondition: Could not get attached VARNODE." << std::endl;
			Stack::getInstance().pushShort(0);
			return 0.0f;
		}

		Stack::getInstance().pushShort(1);

		return 0.0f;
	}
}