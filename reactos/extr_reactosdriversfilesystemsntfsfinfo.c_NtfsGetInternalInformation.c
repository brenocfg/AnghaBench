#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  QuadPart; } ;
struct TYPE_10__ {int /*<<< orphan*/  MFTIndex; TYPE_1__ IndexNumber; } ;
typedef  int* PULONG ;
typedef  TYPE_2__* PNTFS_FCB ;
typedef  TYPE_2__* PFILE_INTERNAL_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_INTERNAL_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,TYPE_2__*,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
NtfsGetInternalInformation(PNTFS_FCB Fcb,
                           PFILE_INTERNAL_INFORMATION InternalInfo,
                           PULONG BufferLength)
{
    DPRINT1("NtfsGetInternalInformation(%p, %p, %p)\n", Fcb, InternalInfo, BufferLength);

    ASSERT(InternalInfo);
    ASSERT(Fcb);

    if (*BufferLength < sizeof(FILE_INTERNAL_INFORMATION))
        return STATUS_BUFFER_TOO_SMALL;

    InternalInfo->IndexNumber.QuadPart = Fcb->MFTIndex;

    *BufferLength -= sizeof(FILE_INTERNAL_INFORMATION);

    return STATUS_SUCCESS;
}