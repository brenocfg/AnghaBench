#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ QuadPart; } ;
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_13__ {int NumberOfLinks; int /*<<< orphan*/  DeletePending; int /*<<< orphan*/  Directory; TYPE_2__ EndOfFile; TYPE_1__ AllocationSize; } ;
struct TYPE_11__ {TYPE_2__ FileSize; TYPE_1__ AllocationSize; } ;
struct TYPE_12__ {int /*<<< orphan*/  Flags; TYPE_3__ RFCB; } ;
typedef  TYPE_4__* PVFATFCB ;
typedef  int* PULONG ;
typedef  TYPE_5__* PFILE_STANDARD_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_STANDARD_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FCB_DELETE_PENDING ; 
 int /*<<< orphan*/  STATUS_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ vfatFCBIsDirectory (TYPE_4__*) ; 

NTSTATUS
VfatGetStandardInformation(
    PVFATFCB FCB,
    PFILE_STANDARD_INFORMATION StandardInfo,
    PULONG BufferLength)
{
    if (*BufferLength < sizeof(FILE_STANDARD_INFORMATION))
        return STATUS_BUFFER_OVERFLOW;

    /* PRECONDITION */
    ASSERT(StandardInfo != NULL);
    ASSERT(FCB != NULL);

    if (vfatFCBIsDirectory(FCB))
    {
        StandardInfo->AllocationSize.QuadPart = 0;
        StandardInfo->EndOfFile.QuadPart = 0;
        StandardInfo->Directory = TRUE;
    }
    else
    {
        StandardInfo->AllocationSize = FCB->RFCB.AllocationSize;
        StandardInfo->EndOfFile = FCB->RFCB.FileSize;
        StandardInfo->Directory = FALSE;
    }
    StandardInfo->NumberOfLinks = 1;
    StandardInfo->DeletePending = BooleanFlagOn(FCB->Flags, FCB_DELETE_PENDING);

    *BufferLength -= sizeof(FILE_STANDARD_INFORMATION);
    return STATUS_SUCCESS;
}