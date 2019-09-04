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
typedef  scalar_t__ uint64_t ;
typedef  double uint16_t ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* LEFT_TO_RIGHT_MARK ; 
 int MAX_SIZE_SUFFIXES ; 
 size_t MSG_000 ; 
 size_t MSG_020 ; 
 char** default_msg_table ; 
 float fabs (float) ; 
 double floor (double) ; 
 char** msg_table ; 
 scalar_t__ right_to_left_mode ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,...) ; 
 scalar_t__ upo2 (double) ; 

char* SizeToHumanReadable(uint64_t size, BOOL copy_to_log, BOOL fake_units)
{
	int suffix;
	static char str_size[32];
	const char* dir = ((right_to_left_mode) && (!copy_to_log)) ? LEFT_TO_RIGHT_MARK : "";
	double hr_size = (double)size;
	double t;
	uint16_t i_size;
	char **_msg_table = copy_to_log?default_msg_table:msg_table;
	const double divider = fake_units?1000.0:1024.0;

	for (suffix=0; suffix<MAX_SIZE_SUFFIXES-1; suffix++) {
		if (hr_size < divider)
			break;
		hr_size /= divider;
	}
	if (suffix == 0) {
		static_sprintf(str_size, "%s%d%s %s", dir, (int)hr_size, dir, _msg_table[MSG_020-MSG_000]);
	} else if (fake_units) {
		if (hr_size < 8) {
			static_sprintf(str_size, (fabs((hr_size*10.0)-(floor(hr_size + 0.5)*10.0)) < 0.5)?"%0.0f%s":"%0.1f%s",
				hr_size, _msg_table[MSG_020+suffix-MSG_000]);
		} else {
			t = (double)upo2((uint16_t)hr_size);
			i_size = (uint16_t)((fabs(1.0f-(hr_size / t)) < 0.05f)?t:hr_size);
			static_sprintf(str_size, "%s%d%s %s", dir, i_size, dir, _msg_table[MSG_020+suffix-MSG_000]);
		}
	} else {
		static_sprintf(str_size, (hr_size * 10.0 - (floor(hr_size) * 10.0)) < 0.5?
			"%s%0.0f%s %s":"%s%0.1f%s %s", dir, hr_size, dir, _msg_table[MSG_020+suffix-MSG_000]);
	}
	return str_size;
}