#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int MMIOError ;

/* Variables and functions */
#define  kBMPAccessError 134 
#define  kBMPInvalidColorPanesError 133 
#define  kBMPInvalidKeyError 132 
#define  kBMPInvalidPixelDataError 131 
#define  kBMPUnsupportedColorDepthError 130 
#define  kBMPUnsupportedCompressionError 129 
#define  kBMPUnsupportedHeaderError 128 

const char *MMBMPReadErrorString(MMIOError error)
{
	switch (error) {
		case kBMPAccessError:
			return "Could not open file";
		case kBMPInvalidKeyError:
			return "Not a BMP file";
		case kBMPUnsupportedHeaderError:
			return "Unsupported BMP header";
		case kBMPInvalidColorPanesError:
			return "Invalid number of color panes in BMP file";
		case kBMPUnsupportedColorDepthError:
			return "Unsupported color depth in BMP file";
		case kBMPUnsupportedCompressionError:
			return "Unsupported file compression in BMP file";
		case kBMPInvalidPixelDataError:
			return "Could not read BMP pixel data";
		default:
			return NULL;
	}
}