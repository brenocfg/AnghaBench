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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetHandle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* GetLogicalName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

HANDLE GetLogicalHandle(DWORD DriveIndex, uint64_t PartitionOffset, BOOL bLockDrive, BOOL bWriteAccess, BOOL bWriteShare)
{
	HANDLE hLogical = INVALID_HANDLE_VALUE;
	char* LogicalPath = GetLogicalName(DriveIndex, PartitionOffset, FALSE, FALSE);

	if (LogicalPath == NULL) {
		uprintf("No logical drive found (unpartitioned?)");
		return NULL;
	}

	hLogical = GetHandle(LogicalPath, bLockDrive, bWriteAccess, bWriteShare);
	free(LogicalPath);
	return hLogical;
}