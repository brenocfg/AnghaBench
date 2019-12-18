#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cycle_port ;
struct TYPE_6__ {int /*<<< orphan*/  ConnectionIndex; } ;
typedef  TYPE_1__ USB_CYCLE_PORT_PARAMS ;
struct TYPE_7__ {int /*<<< orphan*/ ** String; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int,TYPE_1__*,int,int*,int /*<<< orphan*/ *) ; 
 TYPE_3__ DriveHub ; 
 int /*<<< orphan*/ * DrivePort ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_FLAG_OVERLAPPED ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetTickCount64 () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_USB_HUB_CYCLE_PORT ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL CyclePort(int index)
{
	static uint64_t LastReset = 0;
	BOOL r = FALSE;
	HANDLE handle = INVALID_HANDLE_VALUE;
	DWORD size;
	USB_CYCLE_PORT_PARAMS cycle_port;

	// Wait at least 10 secs between resets
	if (GetTickCount64() < LastReset + 10000ULL) {
		uprintf("You must wait at least 10 seconds before trying to reset a device");
		return FALSE;
	}

	if (DriveHub.String[index] == NULL) {
		uprintf("The device you are trying to reset does not appear to be a USB device...");
		return FALSE;
	}

	LastReset = GetTickCount64();

	handle = CreateFileA(DriveHub.String[index], GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		uprintf("Could not open %s: %s", DriveHub.String[index], WindowsErrorString());
		goto out;
	}

	size = sizeof(cycle_port);
	memset(&cycle_port, 0, size);
	cycle_port.ConnectionIndex = DrivePort[index];
	uprintf("Cycling port %d (reset) on %s", DrivePort[index], DriveHub.String[index]);
	// As per https://docs.microsoft.com/en-us/windows-hardware/drivers/ddi/content/usbioctl/ni-usbioctl-ioctl_usb_hub_cycle_port
	// IOCTL_USB_HUB_CYCLE_PORT is not supported on Windows 7, Windows Vista, and Windows Server 2008
	if (!DeviceIoControl(handle, IOCTL_USB_HUB_CYCLE_PORT, &cycle_port, size, &cycle_port, size, &size, NULL)) {
		uprintf("  Failed to cycle port: %s", WindowsErrorString());
		goto out;
	}
	uprintf("Please wait for the device to re-appear...");
	r = TRUE;

out:
	safe_closehandle(handle);
	return r;
}