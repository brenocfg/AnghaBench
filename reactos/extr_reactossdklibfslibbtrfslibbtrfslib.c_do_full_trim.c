#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Size; int Flags; scalar_t__ DataSetRangesLength; scalar_t__ DataSetRangesOffset; scalar_t__ ParameterBlockLength; scalar_t__ ParameterBlockOffset; int /*<<< orphan*/  Action; } ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ DEVICE_MANAGE_DATA_SET_ATTRIBUTES ;

/* Variables and functions */
 int DEVICE_DSM_FLAG_ENTIRE_DATA_SET_RANGE ; 
 int DEVICE_DSM_FLAG_TRIM_NOT_FS_ALLOCATED ; 
 int /*<<< orphan*/  DeviceDsmAction_Trim ; 
 int /*<<< orphan*/  IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 

__attribute__((used)) static void do_full_trim(HANDLE h) {
    IO_STATUS_BLOCK iosb;
    DEVICE_MANAGE_DATA_SET_ATTRIBUTES dmdsa;

    RtlZeroMemory(&dmdsa, sizeof(DEVICE_MANAGE_DATA_SET_ATTRIBUTES));

    dmdsa.Size = sizeof(DEVICE_MANAGE_DATA_SET_ATTRIBUTES);
    dmdsa.Action = DeviceDsmAction_Trim;
    dmdsa.Flags = DEVICE_DSM_FLAG_ENTIRE_DATA_SET_RANGE | DEVICE_DSM_FLAG_TRIM_NOT_FS_ALLOCATED;
    dmdsa.ParameterBlockOffset = 0;
    dmdsa.ParameterBlockLength = 0;
    dmdsa.DataSetRangesOffset = 0;
    dmdsa.DataSetRangesLength = 0;

    NtDeviceIoControlFile(h, NULL, NULL, NULL, &iosb, IOCTL_STORAGE_MANAGE_DATA_SET_ATTRIBUTES, &dmdsa, sizeof(DEVICE_MANAGE_DATA_SET_ATTRIBUTES), NULL, 0);
}