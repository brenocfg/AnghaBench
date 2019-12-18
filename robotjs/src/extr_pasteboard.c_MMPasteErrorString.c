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
typedef  int MMPasteError ;

/* Variables and functions */
#define  kMMPasteClearError 132 
#define  kMMPasteDataError 131 
#define  kMMPasteOpenError 130 
#define  kMMPastePasteError 129 
#define  kMMPasteUnsupportedError 128 

const char *MMPasteErrorString(MMPasteError err)
{
	switch (err) {
		case kMMPasteOpenError:
			return "Could not open pasteboard";
		case kMMPasteClearError:
			return "Could not clear pasteboard";
		case kMMPasteDataError:
			return "Could not create image data from bitmap";
		case kMMPastePasteError:
			return "Could not paste data";
		case kMMPasteUnsupportedError:
			return "Unsupported platform";
		default:
			return NULL;
	}
}