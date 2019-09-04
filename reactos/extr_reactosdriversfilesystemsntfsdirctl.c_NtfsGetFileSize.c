#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long ULONGLONG ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  pRecord; } ;
typedef  unsigned long long* PULONGLONG ;
typedef  TYPE_1__* PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 unsigned long long AttributeAllocatedLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AttributeData ; 
 unsigned long long AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FindAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_1__*) ; 

ULONGLONG
NtfsGetFileSize(PDEVICE_EXTENSION DeviceExt,
                PFILE_RECORD_HEADER FileRecord,
                PCWSTR Stream,
                ULONG StreamLength,
                PULONGLONG AllocatedSize)
{
    ULONGLONG Size = 0ULL;
    ULONGLONG Allocated = 0ULL;
    NTSTATUS Status;
    PNTFS_ATTR_CONTEXT DataContext;

    Status = FindAttribute(DeviceExt, FileRecord, AttributeData, Stream, StreamLength, &DataContext, NULL);
    if (NT_SUCCESS(Status))
    {
        Size = AttributeDataLength(DataContext->pRecord);
        Allocated = AttributeAllocatedLength(DataContext->pRecord);
        ReleaseAttributeContext(DataContext);
    }

    if (AllocatedSize != NULL) *AllocatedSize = Allocated;

    return Size;
}