#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int NumberOfDiskExtents; TYPE_1__* Extents; scalar_t__ DeviceNumber; } ;
typedef  TYPE_2__ VOLUME_DISK_EXTENTS_REDEF ;
struct TYPE_5__ {scalar_t__ DiskNumber; } ;
typedef  TYPE_2__ STORAGE_DEVICE_NUMBER_REDEF ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DiskExtents ;
typedef  int /*<<< orphan*/  DeviceNumber ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOCTL_STORAGE_GET_DEVICE_NUMBER ; 
 int /*<<< orphan*/  IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS ; 
 int MAX_DRIVES ; 
 int WindowsErrorString () ; 
 int /*<<< orphan*/  uprintf (char*,char*,...) ; 

int GetDriveNumber(HANDLE hDrive, char* path)
{
	STORAGE_DEVICE_NUMBER_REDEF DeviceNumber;
	VOLUME_DISK_EXTENTS_REDEF DiskExtents;
	DWORD size;
	int r = -1;

	if (!DeviceIoControl(hDrive, IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, NULL, 0,
		&DiskExtents, sizeof(DiskExtents), &size, NULL) || (size <= 0) || (DiskExtents.NumberOfDiskExtents < 1) ) {
		// DiskExtents are NO_GO (which is the case for external USB HDDs...)
		if(!DeviceIoControl(hDrive, IOCTL_STORAGE_GET_DEVICE_NUMBER, NULL, 0,
			&DeviceNumber, sizeof(DeviceNumber), &size, NULL ) || (size <= 0)) {
			uprintf("Could not get device number for device %s: %s", path, WindowsErrorString());
			return -1;
		}
		r = (int)DeviceNumber.DeviceNumber;
	} else if (DiskExtents.NumberOfDiskExtents >= 2) {
		uprintf("Ignoring drive '%s' as it spans multiple disks (RAID?)", path);
		return -1;
	} else {
		r = (int)DiskExtents.Extents[0].DiskNumber;
	}
	if (r >= MAX_DRIVES) {
		uprintf("Device Number for device %s is too big (%d) - ignoring device", path, r);
		return -1;
	}
	return r;
}