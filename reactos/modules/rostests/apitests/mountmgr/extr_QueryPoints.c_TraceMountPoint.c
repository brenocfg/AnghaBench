#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int SymbolicLinkNameLength; int DeviceNameLength; int /*<<< orphan*/  DeviceNameOffset; scalar_t__ SymbolicLinkNameOffset; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ PMOUNTMGR_MOUNT_POINTS ;
typedef  TYPE_1__* PMOUNTMGR_MOUNT_POINT ;

/* Variables and functions */
 int /*<<< orphan*/  trace (char*,...) ; 

VOID
TraceMountPoint(PMOUNTMGR_MOUNT_POINTS MountPoints,
                PMOUNTMGR_MOUNT_POINT MountPoint)
{
    trace("MountPoint: %p\n", MountPoint);
    trace("\tSymbolicOffset: %ld\n", MountPoint->SymbolicLinkNameOffset);
    trace("\tSymbolicLinkName: %.*S\n", MountPoint->SymbolicLinkNameLength / sizeof(WCHAR), (PWSTR)((ULONG_PTR)MountPoints + MountPoint->SymbolicLinkNameOffset));
    trace("\tDeviceOffset: %ld\n", MountPoint->DeviceNameOffset);
    trace("\tDeviceName: %.*S\n", MountPoint->DeviceNameLength / sizeof(WCHAR), (PWSTR)((ULONG_PTR)MountPoints + MountPoint->DeviceNameOffset));
}