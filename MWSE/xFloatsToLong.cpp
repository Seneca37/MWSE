/************************************************************************
	
	xFloatsToLong.cpp - Copyright (c) 2008 The MWSE Project
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

using namespace mwse;

namespace mwse
{
	class xFloatsToLong : mwse::InstructionInterface_t
	{
	public:
		xFloatsToLong();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xFloatsToLongOpcode = 0x3922;
	static xFloatsToLong xFloatsToLongInstance;

	xFloatsToLong::xFloatsToLong() : mwse::InstructionInterface_t(xFloatsToLongOpcode) {}

	void xFloatsToLong::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xFloatsToLong::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		if (mwse::Stack::getInstance().size() != 2) {
			return 0;
		}

		mwFloat_t param1 = mwse::Stack::getInstance().popFloat();
		mwFloat_t param2 = mwse::Stack::getInstance().popFloat();

		mwLong_t high = 0;
		mwLong_t low = 0;
		if (param1 >= 0x10000) {
			high = param1;
			low = param2;
		} else {
			high = param2;
			low = param1;
		}

		mwse::Stack::getInstance().pushLong(((high - 0x10000) << 16) + low);

		return 0.0;
	}
}