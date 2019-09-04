#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {TYPE_2__ member_0; } ;
struct TYPE_6__ {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CreateDisk ;
typedef  TYPE_3__ CREATE_DISK ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IOCTL_DISK_CREATE_DISK ; 
 int /*<<< orphan*/  IOCTL_DISK_UPDATE_PROPERTIES ; 
 int /*<<< orphan*/  MSG_239 ; 
 int /*<<< orphan*/  PARTITION_STYLE_RAW ; 
 int /*<<< orphan*/  PrintInfoDebug (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  safe_closehandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*,int /*<<< orphan*/ ) ; 

BOOL InitializeDisk(HANDLE hDrive)
{
	BOOL r;
	DWORD size;
	CREATE_DISK CreateDisk = {PARTITION_STYLE_RAW, {{0}}};

	PrintInfoDebug(0, MSG_239);

	size = sizeof(CreateDisk);
	r = DeviceIoControl(hDrive, IOCTL_DISK_CREATE_DISK,
			(BYTE*)&CreateDisk, size, NULL, 0, &size, NULL );
	if (!r) {
		uprintf("Could not delete drive layout: %s", WindowsErrorString());
		safe_closehandle(hDrive);
		return FALSE;
	}

	r = DeviceIoControl(hDrive, IOCTL_DISK_UPDATE_PROPERTIES, NULL, 0, NULL, 0, &size, NULL );
	if (!r) {
		uprintf("Could not refresh drive layout: %s", WindowsErrorString());
		safe_closehandle(hDrive);
		return FALSE;
	}

	return TRUE;
}