#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ FatType; } ;
struct TYPE_8__ {TYPE_1__ FatInfo; } ;
struct TYPE_7__ {scalar_t__ EaSize; } ;
typedef  int /*<<< orphan*/  PVFATFCB ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  TYPE_2__* PFILE_EA_INFORMATION ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FAT12 ; 
 scalar_t__ FAT16 ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
NTSTATUS
VfatGetEaInformation(
    PFILE_OBJECT FileObject,
    PVFATFCB Fcb,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_EA_INFORMATION Info,
    PULONG BufferLength)
{
    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(Fcb);

    /* FIXME - use SEH to access the buffer! */
    Info->EaSize = 0;
    *BufferLength -= sizeof(*Info);
    if (DeviceExt->FatInfo.FatType == FAT12 ||
        DeviceExt->FatInfo.FatType == FAT16)
    {
        /* FIXME */
        DPRINT1("VFAT: FileEaInformation not implemented!\n");
    }
    return STATUS_SUCCESS;
}