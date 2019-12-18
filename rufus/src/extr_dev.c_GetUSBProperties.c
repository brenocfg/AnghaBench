#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ vid; scalar_t__ pid; int lower_speed; scalar_t__ speed; scalar_t__ port; } ;
typedef  TYPE_4__ usb_device_props ;
typedef  int /*<<< orphan*/  conn_info_v2 ;
typedef  int /*<<< orphan*/  conn_info ;
struct TYPE_13__ {scalar_t__ DeviceIsSuperSpeedCapableOrHigher; scalar_t__ DeviceIsSuperSpeedPlusCapableOrHigher; scalar_t__ DeviceIsOperatingAtSuperSpeedOrHigher; scalar_t__ DeviceIsOperatingAtSuperSpeedPlusOrHigher; } ;
struct TYPE_12__ {int Usb300; } ;
struct TYPE_11__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct TYPE_15__ {int Length; TYPE_3__ Flags; TYPE_2__ SupportedUsbProtocols; void* ConnectionIndex; scalar_t__ Speed; TYPE_1__ DeviceDescriptor; } ;
typedef  TYPE_5__ USB_NODE_CONNECTION_INFORMATION_EX_V2 ;
typedef  TYPE_5__ USB_NODE_CONNECTION_INFORMATION_EX ;
typedef  void* ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  DEVINST ;
typedef  scalar_t__ CONFIGRET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DRP_ADDRESS ; 
 int /*<<< orphan*/  CM_Get_DevNode_Registry_PropertyA ; 
 scalar_t__ CM_Locate_DevNodeA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CR_SUCCESS ; 
 int /*<<< orphan*/  Cfgmgr32 ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,TYPE_5__*,int,TYPE_5__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_FLAG_OVERLAPPED ; 
 int /*<<< orphan*/  FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX ; 
 int /*<<< orphan*/  IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2 ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ USB_SPEED_SUPER ; 
 scalar_t__ USB_SPEED_SUPER_PLUS ; 
 scalar_t__ WINDOWS_8 ; 
 scalar_t__ WindowsErrorString () ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nWindowsVersion ; 
 scalar_t__ pfCM_Get_DevNode_Registry_PropertyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  uprintf (char*,char*,scalar_t__) ; 

__attribute__((used)) static BOOL GetUSBProperties(char* parent_path, char* device_id, usb_device_props* props)
{
	BOOL r = FALSE;
	CONFIGRET cr;
	HANDLE handle = INVALID_HANDLE_VALUE;
	DWORD size;
	DEVINST device_inst;
	USB_NODE_CONNECTION_INFORMATION_EX conn_info;
	USB_NODE_CONNECTION_INFORMATION_EX_V2 conn_info_v2;
	PF_INIT(CM_Get_DevNode_Registry_PropertyA, Cfgmgr32);

	if ((parent_path == NULL) || (device_id == NULL) || (props == NULL) ||
		(pfCM_Get_DevNode_Registry_PropertyA == NULL)) {
		goto out;
	}

	cr = CM_Locate_DevNodeA(&device_inst, device_id, 0);
	if (cr != CR_SUCCESS) {
		uprintf("Could not get device instance handle for '%s': CR error %d", device_id, cr);
		goto out;
	}

	props->port = 0;
	size = sizeof(props->port);
	cr = pfCM_Get_DevNode_Registry_PropertyA(device_inst, CM_DRP_ADDRESS, NULL, (PVOID)&props->port, &size, 0);
	if (cr != CR_SUCCESS) {
		uprintf("Could not get port for '%s': CR error %d", device_id, cr);
		goto out;
	}

	handle = CreateFileA(parent_path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		uprintf("Could not open hub %s: %s", parent_path, WindowsErrorString());
		goto out;
	}
	size = sizeof(conn_info);
	memset(&conn_info, 0, size);
	conn_info.ConnectionIndex = (ULONG)props->port;
	// coverity[tainted_data_argument]
	if (!DeviceIoControl(handle, IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX, &conn_info, size, &conn_info, size, &size, NULL)) {
		uprintf("Could not get node connection information for '%s': %s", device_id, WindowsErrorString());
		goto out;
	}

	// Some poorly written proprietary Windows 7 USB 3.0 controller drivers (<cough>ASMedia<cough>)
	// have a screwed up implementation of IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX that succeeds
	// but returns zeroed data => Add a workaround so that we don't lose our VID:PID...
	if ((conn_info.DeviceDescriptor.idVendor != 0) || (conn_info.DeviceDescriptor.idProduct != 0)) {
		props->vid = conn_info.DeviceDescriptor.idVendor;
		props->pid = conn_info.DeviceDescriptor.idProduct;
		props->speed = conn_info.Speed + 1;
		r = TRUE;
	}

	// In their great wisdom, Microsoft decided to BREAK the USB speed report between Windows 7 and Windows 8
	if (nWindowsVersion >= WINDOWS_8) {
		size = sizeof(conn_info_v2);
		memset(&conn_info_v2, 0, size);
		conn_info_v2.ConnectionIndex = (ULONG)props->port;
		conn_info_v2.Length = size;
		conn_info_v2.SupportedUsbProtocols.Usb300 = 1;
		if (!DeviceIoControl(handle, IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2, &conn_info_v2, size, &conn_info_v2, size, &size, NULL)) {
			uprintf("Could not get node connection information (V2) for device '%s': %s", device_id, WindowsErrorString());
		} else if (conn_info_v2.Flags.DeviceIsOperatingAtSuperSpeedPlusOrHigher) {
			props->speed = USB_SPEED_SUPER_PLUS;
		} else if (conn_info_v2.Flags.DeviceIsOperatingAtSuperSpeedOrHigher) {
			props->speed = USB_SPEED_SUPER;
		} else if (conn_info_v2.Flags.DeviceIsSuperSpeedPlusCapableOrHigher) {
			props->lower_speed = 2;
		} else if (conn_info_v2.Flags.DeviceIsSuperSpeedCapableOrHigher) {
			props->lower_speed = 1;
		}
	}

out:
	safe_closehandle(handle);
	return r;
}