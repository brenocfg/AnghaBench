#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  geometry ;
struct TYPE_3__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_4__ {TYPE_1__ DiskSize; } ;
typedef  TYPE_2__* PDISK_GEOMETRY_EX ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetPhysicalHandle (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_GEOMETRY_EX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 

uint64_t GetDriveSize(DWORD DriveIndex)
{
	BOOL r;
	HANDLE hPhysical;
	DWORD size;
	BYTE geometry[256];
	PDISK_GEOMETRY_EX DiskGeometry = (PDISK_GEOMETRY_EX)(void*)geometry;

	hPhysical = GetPhysicalHandle(DriveIndex, FALSE, FALSE, TRUE);
	if (hPhysical == INVALID_HANDLE_VALUE)
		return FALSE;

	r = DeviceIoControl(hPhysical, IOCTL_DISK_GET_DRIVE_GEOMETRY_EX,
		NULL, 0, geometry, sizeof(geometry), &size, NULL);
	safe_closehandle(hPhysical);
	if (!r || size <= 0)
		return 0;
	return DiskGeometry->DiskSize.QuadPart;
}