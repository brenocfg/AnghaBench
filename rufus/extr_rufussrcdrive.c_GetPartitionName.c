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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDriveIndex (int) ; 
 scalar_t__ FALSE ; 
 int MAX_PARTITIONS ; 
 scalar_t__ TRUE ; 
 char* safe_strdup (char*) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int,int) ; 

char* GetPartitionName(DWORD DriveIndex, DWORD PartitionIndex)
{
	BOOL success = FALSE;
	char partition_name[32];

	CheckDriveIndex(DriveIndex);
	if (PartitionIndex >= MAX_PARTITIONS)
		goto out;
	if (PartitionIndex == 0)
		PartitionIndex = 1;
	
	static_sprintf(partition_name, "\\Device\\Harddisk%lu\\Partition%lu", DriveIndex, PartitionIndex);
	success = TRUE;
out:
	return (success) ? safe_strdup(partition_name) : NULL;
}