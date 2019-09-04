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
struct TYPE_6__ {int rootStart; int BytesPerCluster; int SectorsPerCluster; } ;
struct TYPE_7__ {TYPE_1__ FatInfo; } ;
typedef  int* PULONG ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetNextCluster (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  GetNextClusterExtend (TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
OffsetToCluster(
    PDEVICE_EXTENSION DeviceExt,
    ULONG FirstCluster,
    ULONG FileOffset,
    PULONG Cluster,
    BOOLEAN Extend)
{
    ULONG CurrentCluster;
    ULONG i;
    NTSTATUS Status;
/*
    DPRINT("OffsetToCluster(DeviceExt %x, Fcb %x, FirstCluster %x,"
           " FileOffset %x, Cluster %x, Extend %d)\n", DeviceExt,
           Fcb, FirstCluster, FileOffset, Cluster, Extend);
*/
    if (FirstCluster == 0)
    {
        DbgPrint("OffsetToCluster is called with FirstCluster = 0!\n");
        ASSERT(FALSE);
    }

    if (FirstCluster == 1)
    {
        /* root of FAT16 or FAT12 */
        *Cluster = DeviceExt->FatInfo.rootStart + FileOffset
            / (DeviceExt->FatInfo.BytesPerCluster) * DeviceExt->FatInfo.SectorsPerCluster;
        return STATUS_SUCCESS;
    }
    else
    {
        CurrentCluster = FirstCluster;
        if (Extend)
        {
            for (i = 0; i < FileOffset / DeviceExt->FatInfo.BytesPerCluster; i++)
            {
                Status = GetNextClusterExtend (DeviceExt, CurrentCluster, &CurrentCluster);
                if (!NT_SUCCESS(Status))
                    return Status;
            }
            *Cluster = CurrentCluster;
        }
        else
        {
            for (i = 0; i < FileOffset / DeviceExt->FatInfo.BytesPerCluster; i++)
            {
                Status = GetNextCluster (DeviceExt, CurrentCluster, &CurrentCluster);
                if (!NT_SUCCESS(Status))
                    return Status;
            }
            *Cluster = CurrentCluster;
       }
       return STATUS_SUCCESS;
   }
}