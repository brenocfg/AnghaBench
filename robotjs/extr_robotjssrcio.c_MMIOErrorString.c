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
typedef  int MMImageType ;
typedef  int /*<<< orphan*/  MMIOError ;

/* Variables and functions */
 char const* MMBMPReadErrorString (int /*<<< orphan*/ ) ; 
 char const* MMPNGReadErrorString (int /*<<< orphan*/ ) ; 
#define  kBMPImageType 129 
#define  kPNGImageType 128 

const char *MMIOErrorString(MMImageType type, MMIOError error)
{
	switch (type) {
		case kBMPImageType:
			return MMBMPReadErrorString(error);
		case kPNGImageType:
			return MMPNGReadErrorString(error);
		default:
			return "Unsupported image type";
	}
}