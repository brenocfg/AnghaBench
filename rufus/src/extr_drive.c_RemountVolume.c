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
typedef  int /*<<< orphan*/  volume_name ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int APPERR (int /*<<< orphan*/ ) ; 
 scalar_t__ DeleteVolumeMountPointA (char*) ; 
 int /*<<< orphan*/  ERROR_CANT_REMOUNT_VOLUME ; 
 int ERROR_SEVERITY_ERROR ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FlushDrive (char) ; 
 int FormatStatus ; 
 scalar_t__ GetVolumeNameForVolumeMountPointA (char*,char*,int) ; 
 scalar_t__ MountVolume (char*,char*) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  uprintf (char*,char*,char,...) ; 

BOOL RemountVolume(char* drive_name)
{
	char volume_name[51];

	// UDF requires a sync/flush, and it's also a good idea for other FS's
	FlushDrive(drive_name[0]);
	if (GetVolumeNameForVolumeMountPointA(drive_name, volume_name, sizeof(volume_name))) {
		if (DeleteVolumeMountPointA(drive_name)) {
			Sleep(200);
			if (MountVolume(drive_name, volume_name)) {
				uprintf("Successfully remounted %s as %C:", volume_name, drive_name[0]);
			} else {
				uprintf("Failed to remount %s as %C:", volume_name, drive_name[0]);
				// This will leave the drive inaccessible and must be flagged as an error
				FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|APPERR(ERROR_CANT_REMOUNT_VOLUME);
				return FALSE;
			}
		} else {
			uprintf("Could not remount %s as %C: %s", volume_name, drive_name[0], WindowsErrorString());
			// Try to continue regardless
		}
	}
	return TRUE;
}