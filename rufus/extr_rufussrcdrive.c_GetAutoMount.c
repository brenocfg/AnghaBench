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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  IOCTL_MOUNTMGR_QUERY_AUTO_MOUNT ; 
 int /*<<< orphan*/  MOUNTMGR_DOS_DEVICE_NAME ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 

BOOL GetAutoMount(BOOL* enabled)
{
	HANDLE hMountMgr;
	DWORD size;
	BOOL ret = FALSE;

	if (enabled == NULL)
		return FALSE;
	hMountMgr = CreateFileA(MOUNTMGR_DOS_DEVICE_NAME, GENERIC_READ|GENERIC_WRITE,
		FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hMountMgr == NULL)
		return FALSE;
	ret = DeviceIoControl(hMountMgr, IOCTL_MOUNTMGR_QUERY_AUTO_MOUNT, NULL, 0, enabled, sizeof(*enabled), &size, NULL);
	CloseHandle(hMountMgr);
	return ret;
}