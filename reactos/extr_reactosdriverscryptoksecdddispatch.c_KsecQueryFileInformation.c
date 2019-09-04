#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ QuadPart; } ;
struct TYPE_4__ {scalar_t__ QuadPart; } ;
struct TYPE_6__ {int NumberOfLinks; void* Directory; void* DeletePending; TYPE_2__ EndOfFile; TYPE_1__ AllocationSize; } ;
typedef  scalar_t__ PVOID ;
typedef  int* PSIZE_T ;
typedef  TYPE_3__* PFILE_STANDARD_INFORMATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  FILE_STANDARD_INFORMATION ;
typedef  scalar_t__ FILE_INFORMATION_CLASS ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ FileStandardInformation ; 
 int /*<<< orphan*/  STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  STATUS_INVALID_INFO_CLASS ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
KsecQueryFileInformation(
    PVOID InfoBuffer,
    FILE_INFORMATION_CLASS FileInformationClass,
    PSIZE_T BufferLength)
{
    PFILE_STANDARD_INFORMATION StandardInformation;

    /* Only FileStandardInformation is supported */
    if (FileInformationClass != FileStandardInformation)
    {
        return STATUS_INVALID_INFO_CLASS;
    }

    /* Validate buffer size */
    if (*BufferLength < sizeof(FILE_STANDARD_INFORMATION))
    {
        *BufferLength = sizeof(FILE_STANDARD_INFORMATION);
        return STATUS_INFO_LENGTH_MISMATCH;
    }

    /* Fill the structure */
    StandardInformation = (PFILE_STANDARD_INFORMATION)InfoBuffer;
    StandardInformation->AllocationSize.QuadPart = 0;
    StandardInformation->EndOfFile.QuadPart = 0;
    StandardInformation->NumberOfLinks = 1;
    StandardInformation->DeletePending = FALSE;
    StandardInformation->Directory = FALSE;
    *BufferLength = sizeof(FILE_STANDARD_INFORMATION);

    return STATUS_SUCCESS;
}