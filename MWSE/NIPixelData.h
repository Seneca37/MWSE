#pragma once

#include "NIDefines.h"

#include "NIObject.h"
#include "NIPixelFormat.h"

namespace NI {
	struct PixelData : Object {
		PixelFormat pixelFormat;
		void * palette; // 0x28
		unsigned char * pixels; // 0x2C // The raw pixel data, in the given format.
		unsigned int * widths; // 0x30 // An array of widths by mip map level.
		unsigned int * heights; // 0x34 // An array of heights by mip map level.
		unsigned int * offsets; // 0x38 // Offsets into 'pixels' for each mip map level, including 0 (length = mipMapLevels + 1).
		unsigned int mipMapLevels; // 0x3C // The number of mip map levels.
		unsigned int bytesPerPixel; // 0x40 // Determined by format data.
		unsigned int revisionID;

		static PixelData* create(unsigned int width, unsigned int height);
	};
	static_assert(sizeof(PixelData) == 0x48, "NI::PixelData failed size validation");

	struct PixelRGB {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
	static_assert(sizeof(PixelRGB) == 0x3, "NI::PixelRGB failed size validation");
}
