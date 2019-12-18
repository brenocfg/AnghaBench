#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t USHORT ;
struct TYPE_2__ {scalar_t__ DiskSize; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SEVERITY_ERROR ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int /*<<< orphan*/  FALSE ; 
 int FP_LARGE_FAT32 ; 
 size_t FS_EXT2 ; 
 size_t FS_FAT32 ; 
 size_t FS_MAX ; 
 int /*<<< orphan*/ * FileSystemLabel ; 
 int /*<<< orphan*/  FormatExtFs (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FormatLargeFAT32 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FormatNative (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FormatNativeVds (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ LARGE_FAT32_SIZE ; 
 TYPE_1__ SelectedDrive ; 
 size_t actual_fs_type ; 
 scalar_t__ force_large_fat32 ; 
 scalar_t__ use_vds ; 

__attribute__((used)) static BOOL FormatPartition(DWORD DriveIndex, uint64_t PartitionOffset, DWORD UnitAllocationSize, USHORT FSType, LPCSTR Label, DWORD Flags)
{
	if ((DriveIndex < 0x80) || (DriveIndex > 0x100) || (FSType >= FS_MAX) ||
		// The following validates that UnitAllocationSize is a power of 2
		((UnitAllocationSize != 0) && (UnitAllocationSize & (UnitAllocationSize - 1)))) {
		ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | ERROR_INVALID_PARAMETER;
		return FALSE;
	}
	actual_fs_type = FSType;
	if ((FSType == FS_FAT32) && ((SelectedDrive.DiskSize > LARGE_FAT32_SIZE) || (force_large_fat32) || (Flags & FP_LARGE_FAT32)))
		return FormatLargeFAT32(DriveIndex, PartitionOffset, UnitAllocationSize, FileSystemLabel[FSType], Label, Flags);
	else if (FSType >= FS_EXT2)
		return FormatExtFs(DriveIndex, PartitionOffset, UnitAllocationSize, FileSystemLabel[FSType], Label, Flags);
	else if (use_vds)
		return FormatNativeVds(DriveIndex, PartitionOffset, UnitAllocationSize, FileSystemLabel[FSType], Label, Flags);
	else
		return FormatNative(DriveIndex, PartitionOffset, UnitAllocationSize, FileSystemLabel[FSType], Label, Flags);
}