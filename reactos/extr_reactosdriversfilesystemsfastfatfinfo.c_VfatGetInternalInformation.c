#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int BytesPerCluster; } ;
struct TYPE_14__ {TYPE_2__ FatInfo; } ;
struct TYPE_11__ {int QuadPart; } ;
struct TYPE_13__ {int /*<<< orphan*/  entry; TYPE_1__ IndexNumber; } ;
typedef  TYPE_3__* PVFATFCB ;
typedef  int* PULONG ;
typedef  TYPE_3__* PFILE_INTERNAL_INFORMATION ;
typedef  TYPE_5__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  FILE_INTERNAL_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ vfatDirEntryGetFirstCluster (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
NTSTATUS
VfatGetInternalInformation(
    PVFATFCB Fcb,
    PDEVICE_EXTENSION DeviceExt,
    PFILE_INTERNAL_INFORMATION InternalInfo,
    PULONG BufferLength)
{
    ASSERT(InternalInfo);
    ASSERT(Fcb);

    if (*BufferLength < sizeof(FILE_INTERNAL_INFORMATION))
        return STATUS_BUFFER_OVERFLOW;

    InternalInfo->IndexNumber.QuadPart = (LONGLONG)vfatDirEntryGetFirstCluster(DeviceExt, &Fcb->entry) * DeviceExt->FatInfo.BytesPerCluster;

    *BufferLength -= sizeof(FILE_INTERNAL_INFORMATION);
    return STATUS_SUCCESS;
}