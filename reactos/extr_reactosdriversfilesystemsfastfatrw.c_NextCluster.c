#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {scalar_t__ SectorsPerCluster; } ;
struct TYPE_7__ {TYPE_1__ FatInfo; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GetNextCluster (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  GetNextClusterExtend (TYPE_2__*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
NextCluster(
    PDEVICE_EXTENSION DeviceExt,
    ULONG FirstCluster,
    PULONG CurrentCluster,
    BOOLEAN Extend)
{
    if (FirstCluster == 1)
    {
        (*CurrentCluster) += DeviceExt->FatInfo.SectorsPerCluster;
        return STATUS_SUCCESS;
    }
    else
    {
        if (Extend)
            return GetNextClusterExtend(DeviceExt, (*CurrentCluster), CurrentCluster);
        else
            return GetNextCluster(DeviceExt, (*CurrentCluster), CurrentCluster);
    }
}