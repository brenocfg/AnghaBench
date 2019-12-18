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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DRIVE_ACCESS_RETRIES ; 
 int DRIVE_ACCESS_TIMEOUT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FormatStatus ; 
 char* GetLogicalName (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetTickCount64 () ; 
 scalar_t__ IS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  groot_len ; 
 int /*<<< orphan*/  groot_name ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

BOOL WaitForLogical(DWORD DriveIndex, uint64_t PartitionOffset)
{
	uint64_t EndTime;
	char* LogicalPath = NULL;

	// GetLogicalName() calls may be slow, so use the system time to
	// make sure we don't spend more than DRIVE_ACCESS_TIMEOUT in wait.
	EndTime = GetTickCount64() + DRIVE_ACCESS_TIMEOUT;
	do {
		LogicalPath = GetLogicalName(DriveIndex, PartitionOffset, FALSE, TRUE);
		// Need to filter out GlobalRoot devices as we don't want to wait on those
		if ((LogicalPath != NULL) && (strncmp(LogicalPath, groot_name, groot_len) != 0)) {
			free(LogicalPath);
			return TRUE;
		}
		free(LogicalPath);
		if (IS_ERROR(FormatStatus))	// User cancel
			return FALSE;
		Sleep(DRIVE_ACCESS_TIMEOUT / DRIVE_ACCESS_RETRIES);
	} while (GetTickCount64() < EndTime);
	uprintf("Timeout while waiting for logical drive");
	return FALSE;
}