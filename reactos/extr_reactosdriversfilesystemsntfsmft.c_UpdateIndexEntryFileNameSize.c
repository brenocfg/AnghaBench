#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_28__ {int /*<<< orphan*/  Ntfs; } ;
struct TYPE_24__ {scalar_t__ AllocatedSize; scalar_t__ FirstEntryOffset; scalar_t__ TotalSizeOfEntries; } ;
struct TYPE_23__ {scalar_t__ Type; } ;
struct TYPE_27__ {TYPE_5__ Header; TYPE_4__ Ntfs; } ;
struct TYPE_22__ {scalar_t__ NameType; scalar_t__ AllocatedSize; scalar_t__ DataSize; } ;
struct TYPE_20__ {int IndexedFile; } ;
struct TYPE_21__ {TYPE_1__ Directory; } ;
struct TYPE_26__ {int Flags; int Length; TYPE_3__ FileName; TYPE_2__ Data; } ;
struct TYPE_25__ {int /*<<< orphan*/  pRecord; } ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  TYPE_6__* PNTFS_ATTR_CONTEXT ;
typedef  TYPE_7__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  TYPE_8__* PINDEX_BUFFER ;
typedef  TYPE_9__* PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/ * PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  INDEX_ENTRY_ATTRIBUTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ AddFixupArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ AttributeDataLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AttributeIndexAllocation ; 
 scalar_t__ CompareFileName (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FindAttribute (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ,char*,int,TYPE_6__**,int /*<<< orphan*/ *) ; 
 scalar_t__ FixupUpdateSequenceArray (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Header ; 
 int /*<<< orphan*/  INDEX_BUFFER ; 
 scalar_t__ NRH_INDX_TYPE ; 
 int NTFS_FILE_FIRST_USER_FILE ; 
 scalar_t__ NTFS_FILE_NAME_DOS ; 
 int NTFS_INDEX_ENTRY_END ; 
 int NTFS_INDEX_ENTRY_NODE ; 
 int NTFS_MFT_MASK ; 
 scalar_t__ NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  ReadAttribute (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseAttributeContext (TYPE_6__*) ; 
 scalar_t__ STATUS_OBJECT_PATH_NOT_FOUND ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ WriteAttribute (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__,int /*<<< orphan*/  const,scalar_t__,scalar_t__*,TYPE_9__*) ; 

NTSTATUS
UpdateIndexEntryFileNameSize(PDEVICE_EXTENSION Vcb,
                             PFILE_RECORD_HEADER MftRecord,
                             PCHAR IndexRecord,
                             ULONG IndexBlockSize,
                             PINDEX_ENTRY_ATTRIBUTE FirstEntry,
                             PINDEX_ENTRY_ATTRIBUTE LastEntry,
                             PUNICODE_STRING FileName,
                             PULONG StartEntry,
                             PULONG CurrentEntry,
                             BOOLEAN DirSearch,
                             ULONGLONG NewDataSize,
                             ULONGLONG NewAllocatedSize,
                             BOOLEAN CaseSensitive)
{
    NTSTATUS Status;
    ULONG RecordOffset;
    PINDEX_ENTRY_ATTRIBUTE IndexEntry;
    PNTFS_ATTR_CONTEXT IndexAllocationCtx;
    ULONGLONG IndexAllocationSize;
    PINDEX_BUFFER IndexBuffer;

    DPRINT("UpdateIndexEntrySize(%p, %p, %p, %lu, %p, %p, %wZ, %lu, %lu, %s, %I64u, %I64u, %s)\n",
           Vcb,
           MftRecord,
           IndexRecord,
           IndexBlockSize,
           FirstEntry,
           LastEntry,
           FileName,
           *StartEntry,
           *CurrentEntry,
           DirSearch ? "TRUE" : "FALSE",
           NewDataSize,
           NewAllocatedSize,
           CaseSensitive ? "TRUE" : "FALSE");

    // find the index entry responsible for the file we're trying to update
    IndexEntry = FirstEntry;
    while (IndexEntry < LastEntry &&
           !(IndexEntry->Flags & NTFS_INDEX_ENTRY_END))
    {
        if ((IndexEntry->Data.Directory.IndexedFile & NTFS_MFT_MASK) > NTFS_FILE_FIRST_USER_FILE &&
            *CurrentEntry >= *StartEntry &&
            IndexEntry->FileName.NameType != NTFS_FILE_NAME_DOS &&
            CompareFileName(FileName, IndexEntry, DirSearch, CaseSensitive))
        {
            *StartEntry = *CurrentEntry;
            IndexEntry->FileName.DataSize = NewDataSize;
            IndexEntry->FileName.AllocatedSize = NewAllocatedSize;
            // indicate that the caller will still need to write the structure to the disk
            return STATUS_PENDING;
        }

        (*CurrentEntry) += 1;
        ASSERT(IndexEntry->Length >= sizeof(INDEX_ENTRY_ATTRIBUTE));
        IndexEntry = (PINDEX_ENTRY_ATTRIBUTE)((PCHAR)IndexEntry + IndexEntry->Length);
    }

    /* If we're already browsing a subnode */
    if (IndexRecord == NULL)
    {
        return STATUS_OBJECT_PATH_NOT_FOUND;
    }

    /* If there's no subnode */
    if (!(IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE))
    {
        return STATUS_OBJECT_PATH_NOT_FOUND;
    }

    Status = FindAttribute(Vcb, MftRecord, AttributeIndexAllocation, L"$I30", 4, &IndexAllocationCtx, NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Corrupted filesystem!\n");
        return Status;
    }

    IndexAllocationSize = AttributeDataLength(IndexAllocationCtx->pRecord);
    Status = STATUS_OBJECT_PATH_NOT_FOUND;
    for (RecordOffset = 0; RecordOffset < IndexAllocationSize; RecordOffset += IndexBlockSize)
    {
        ReadAttribute(Vcb, IndexAllocationCtx, RecordOffset, IndexRecord, IndexBlockSize);
        Status = FixupUpdateSequenceArray(Vcb, &((PFILE_RECORD_HEADER)IndexRecord)->Ntfs);
        if (!NT_SUCCESS(Status))
        {
            break;
        }

        IndexBuffer = (PINDEX_BUFFER)IndexRecord;
        ASSERT(IndexBuffer->Ntfs.Type == NRH_INDX_TYPE);
        ASSERT(IndexBuffer->Header.AllocatedSize + FIELD_OFFSET(INDEX_BUFFER, Header) == IndexBlockSize);
        FirstEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)&IndexBuffer->Header + IndexBuffer->Header.FirstEntryOffset);
        LastEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)&IndexBuffer->Header + IndexBuffer->Header.TotalSizeOfEntries);
        ASSERT(LastEntry <= (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)IndexBuffer + IndexBlockSize));

        Status = UpdateIndexEntryFileNameSize(NULL,
                                              NULL,
                                              NULL,
                                              0,
                                              FirstEntry,
                                              LastEntry,
                                              FileName,
                                              StartEntry,
                                              CurrentEntry,
                                              DirSearch,
                                              NewDataSize,
                                              NewAllocatedSize,
                                              CaseSensitive);
        if (Status == STATUS_PENDING)
        {
            // write the index record back to disk
            ULONG Written;

            // first we need to update the fixup values for the index block
            Status = AddFixupArray(Vcb, &((PFILE_RECORD_HEADER)IndexRecord)->Ntfs);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("Error: Failed to update fixup sequence array!\n");
                break;
            }

            Status = WriteAttribute(Vcb, IndexAllocationCtx, RecordOffset, (const PUCHAR)IndexRecord, IndexBlockSize, &Written, MftRecord);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("ERROR Performing write!\n");
                break;
            }

            Status = STATUS_SUCCESS;
            break;
        }
        if (NT_SUCCESS(Status))
        {
            break;
        }
    }

    ReleaseAttributeContext(IndexAllocationCtx);
    return Status;
}