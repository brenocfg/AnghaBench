#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_4__ {int BytesPerCluster; int BytesPerSector; } ;
struct TYPE_5__ {TYPE_1__ NtfsInfo; } ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;

/* Variables and functions */

ULONGLONG
GetAllocationOffsetFromVCN(PDEVICE_EXTENSION DeviceExt,
                           ULONG IndexBufferSize,
                           ULONGLONG Vcn)
{
    if (IndexBufferSize < DeviceExt->NtfsInfo.BytesPerCluster)
        return Vcn * DeviceExt->NtfsInfo.BytesPerSector;

    return Vcn * DeviceExt->NtfsInfo.BytesPerCluster;
}