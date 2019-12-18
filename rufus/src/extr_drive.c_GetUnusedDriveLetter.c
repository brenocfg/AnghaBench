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
typedef  int /*<<< orphan*/  drives ;
typedef  int DWORD ;

/* Variables and functions */
 int GetLogicalDriveStringsA (int,char*) ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  isalpha (char) ; 
 scalar_t__ safe_strlen (char*) ; 
 scalar_t__ toupper (int) ; 
 int /*<<< orphan*/  uprintf (char*,int,...) ; 

char GetUnusedDriveLetter(void)
{
	DWORD size;
	char drive_letter = 'Z'+1, *drive, drives[26*4 + 1];	/* "D:\", "E:\", etc., plus one NUL */

	size = GetLogicalDriveStringsA(sizeof(drives), drives);
	if (size == 0) {
		uprintf("GetLogicalDriveStrings failed: %s", WindowsErrorString());
		goto out;
	}
	if (size > sizeof(drives)) {
		uprintf("GetLogicalDriveStrings: Buffer too small (required %d vs. %d)", size, sizeof(drives));
		goto out;
	}

	for (drive_letter = 'C'; drive_letter <= 'Z'; drive_letter++) {
		for (drive = drives ;*drive; drive += safe_strlen(drive)+1) {
			if (!isalpha(*drive))
				continue;
			if (drive_letter == (char)toupper((int)*drive))
				break;
		}
		if (!*drive)
			break;
	}

out:
	return (drive_letter>'Z')?0:drive_letter;
}