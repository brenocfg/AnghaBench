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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DDD_NO_BROADCAST_SYSTEM ; 
 int DDD_REMOVE_DEFINITION ; 
 int /*<<< orphan*/  DefineDosDeviceA (int,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  suprintf (char*,char const*,...) ; 

BOOL AltUnmountVolume(const char* drive_name, BOOL bSilent)
{
	if (drive_name == NULL)
		return FALSE;
	if (!DefineDosDeviceA(DDD_REMOVE_DEFINITION | DDD_NO_BROADCAST_SYSTEM, drive_name, NULL)) {
		suprintf("Could not unmount '%s': %s", drive_name, WindowsErrorString());
		return FALSE;
	}
	suprintf("Successfully unmounted '%s'", drive_name);
	return TRUE;
}