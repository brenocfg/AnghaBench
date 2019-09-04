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
#define  kPNGAccessError 130 
#define  kPNGInvalidHeaderError 129 
#define  kPNGReadError 128 

const char *MMPNGReadErrorString(MMIOError error)
{
	switch (error) {
		case kPNGAccessError:
			return "Could not open file";
		case kPNGReadError:
			return "Could not read file";
		case kPNGInvalidHeaderError:
			return "Not a PNG file";
		default:
			return NULL;
	}
}