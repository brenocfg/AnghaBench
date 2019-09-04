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
typedef  char* DWORD ;

/* Variables and functions */
 int DDD_NO_BROADCAST_SYSTEM ; 
 int DDD_RAW_TARGET_PATH ; 
 int /*<<< orphan*/  DefineDosDeviceA (int,char*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 char* GetLogicalName (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char GetUnusedDriveLetter () ; 
 int /*<<< orphan*/  TRUE ; 
 char* WindowsErrorString () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  groot_len ; 
 int /*<<< orphan*/  groot_name ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

char* AltMountVolume(DWORD DriveIndex, DWORD PartitionIndex)
{
	char* ret = NULL, *volume_name = NULL;
	static char mounted_drive[] = "?:";

	mounted_drive[0] = GetUnusedDriveLetter();
	if (mounted_drive[0] == 0) {
		uprintf("Could not find an unused drive letter");
		goto out;
	}
	volume_name = GetLogicalName(DriveIndex, PartitionIndex, FALSE, TRUE);
	if ((volume_name == NULL) || (strncmp(volume_name, groot_name, groot_len) != 0)) {
		uprintf("Unexpected volume name: '%s'", volume_name);
		goto out;
	}

	// bcdboot sure won't like it if you forget the starting '\'
	if (!DefineDosDeviceA(DDD_RAW_TARGET_PATH | DDD_NO_BROADCAST_SYSTEM, mounted_drive, &volume_name[14])) {
		uprintf("Could not mount '%s' to '%s': %s", &volume_name[14], mounted_drive, WindowsErrorString());
		goto out;
	}

	uprintf("Successfully mounted '%s' (Partition %d) as '%s'", &volume_name[14], PartitionIndex, mounted_drive);
	ret = mounted_drive;

out:
	free(volume_name);
	return ret;
}