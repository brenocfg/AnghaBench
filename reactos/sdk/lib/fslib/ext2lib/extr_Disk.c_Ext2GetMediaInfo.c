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
struct TYPE_3__ {int /*<<< orphan*/  PartInfo; int /*<<< orphan*/  MediaHandle; int /*<<< orphan*/  DiskGeometry; } ;
typedef  TYPE_1__* PEXT2_FILESYS ;
typedef  int /*<<< orphan*/  PARTITION_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  DISK_GEOMETRY ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_DISK_GET_DRIVE_GEOMETRY ; 
 int /*<<< orphan*/  IOCTL_DISK_GET_PARTITION_INFO ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtDeviceIoControlFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

NTSTATUS
Ext2GetMediaInfo( PEXT2_FILESYS Ext2Sys )
{
    NTSTATUS Status;
    IO_STATUS_BLOCK IoSb;

    Status = NtDeviceIoControlFile( Ext2Sys->MediaHandle,
                                NULL, NULL, NULL, &IoSb,
                                IOCTL_DISK_GET_DRIVE_GEOMETRY,
                                &(Ext2Sys->DiskGeometry), sizeof(DISK_GEOMETRY),
                                &(Ext2Sys->DiskGeometry), sizeof(DISK_GEOMETRY));


    if (!NT_SUCCESS(Status))
    {
        goto errorout;
    }

    Status = NtDeviceIoControlFile( Ext2Sys->MediaHandle,
                                NULL, NULL, NULL, &IoSb,
                                IOCTL_DISK_GET_PARTITION_INFO,
                                &(Ext2Sys->PartInfo), sizeof(PARTITION_INFORMATION),
                                &(Ext2Sys->PartInfo), sizeof(PARTITION_INFORMATION));

    if (!NT_SUCCESS(Status))
    {
        goto errorout;
    }

errorout:

    return Status;
}