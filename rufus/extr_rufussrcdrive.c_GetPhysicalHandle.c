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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetHandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* GetPhysicalName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  safe_free (char*) ; 

HANDLE GetPhysicalHandle(DWORD DriveIndex, BOOL bLockDrive, BOOL bWriteAccess, BOOL bWriteShare)
{
	HANDLE hPhysical = INVALID_HANDLE_VALUE;
	char* PhysicalPath = GetPhysicalName(DriveIndex);
	hPhysical = GetHandle(PhysicalPath, bLockDrive, bWriteAccess, bWriteShare);
	safe_free(PhysicalPath);
	return hPhysical;
}