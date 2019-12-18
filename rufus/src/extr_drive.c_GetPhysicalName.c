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
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDriveIndex (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 char* safe_strdup (char*) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int /*<<< orphan*/ ) ; 

char* GetPhysicalName(DWORD DriveIndex)
{
	BOOL success = FALSE;
	char physical_name[24];

	CheckDriveIndex(DriveIndex);
	static_sprintf(physical_name, "\\\\.\\PhysicalDrive%lu", DriveIndex);
	success = TRUE;
out:
	return (success)?safe_strdup(physical_name):NULL;
}