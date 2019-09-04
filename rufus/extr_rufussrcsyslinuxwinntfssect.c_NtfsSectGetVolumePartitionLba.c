#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int NumberOfDiskExtents; TYPE_3__* Extents; } ;
typedef  TYPE_4__ VOLUME_DISK_EXTENTS ;
struct TYPE_8__ {int QuadPart; } ;
struct TYPE_12__ {int BytesPerSector; TYPE_1__ PartitionLba; int /*<<< orphan*/  Handle; } ;
struct TYPE_9__ {int QuadPart; } ;
struct TYPE_10__ {TYPE_2__ StartingOffset; } ;
typedef  TYPE_5__ S_NTFSSECT_VOLINFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeviceIoControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS ; 
 int /*<<< orphan*/  M_ERR (char*) ; 

__attribute__((used)) static DWORD NtfsSectGetVolumePartitionLba(S_NTFSSECT_VOLINFO * VolumeInfo) {
    BOOL ok;
    VOLUME_DISK_EXTENTS vol_disk_extents;
    DWORD output_size, rc;

    ok = DeviceIoControl(
        VolumeInfo->Handle,
        IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS,
        NULL,
        0,
        &vol_disk_extents,
        sizeof vol_disk_extents,
        &output_size,
        NULL
      );
    rc = GetLastError();
    if (!ok) {
        M_ERR("Couldn't fetch volume disk extent(s)!");
        goto err_vol_disk_extents;
      }

    if (vol_disk_extents.NumberOfDiskExtents != 1) {
        M_ERR("Unsupported number of volume disk extents!");
        goto err_num_of_extents;
      }

    VolumeInfo->PartitionLba.QuadPart = (
        vol_disk_extents.Extents[0].StartingOffset.QuadPart /
        VolumeInfo->BytesPerSector
      );

    return ERROR_SUCCESS;

    err_num_of_extents:

    err_vol_disk_extents:

    return rc;
  }