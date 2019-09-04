#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ ULONG ;
struct TYPE_18__ {scalar_t__ Length; } ;
struct TYPE_17__ {int HasValidVCN; scalar_t__ KeyCount; TYPE_4__* FirstKey; int /*<<< orphan*/  VCN; } ;
struct TYPE_16__ {struct TYPE_16__* NextKey; TYPE_8__* IndexEntry; } ;
struct TYPE_12__ {int UsaOffset; int UsaCount; int /*<<< orphan*/  Type; } ;
struct TYPE_13__ {int FirstEntryOffset; int TotalSizeOfEntries; int /*<<< orphan*/  Flags; scalar_t__ AllocatedSize; } ;
struct TYPE_15__ {TYPE_11__ Ntfs; TYPE_1__ Header; int /*<<< orphan*/  VCN; } ;
struct TYPE_14__ {scalar_t__ Length; int /*<<< orphan*/  KeyLength; } ;
typedef  TYPE_2__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  TYPE_3__* PINDEX_BUFFER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  TYPE_4__* PB_TREE_KEY ;
typedef  TYPE_5__* PB_TREE_FILENAME_NODE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AddFixupArray (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Header ; 
 int /*<<< orphan*/  INDEX_BUFFER ; 
 int /*<<< orphan*/  INDEX_NODE_LARGE ; 
 int /*<<< orphan*/  NRH_INDX_TYPE ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_2__*,TYPE_8__*,scalar_t__) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  STATUS_NOT_IMPLEMENTED ; 

NTSTATUS
CreateIndexBufferFromBTreeNode(PDEVICE_EXTENSION DeviceExt,
                               PB_TREE_FILENAME_NODE Node,
                               ULONG BufferSize,
                               BOOLEAN HasChildren,
                               PINDEX_BUFFER IndexBuffer)
{
    ULONG i;
    PB_TREE_KEY CurrentKey;
    PINDEX_ENTRY_ATTRIBUTE CurrentNodeEntry;
    NTSTATUS Status;

    // TODO: Fix magic, do math
    RtlZeroMemory(IndexBuffer, BufferSize);
    IndexBuffer->Ntfs.Type = NRH_INDX_TYPE;
    IndexBuffer->Ntfs.UsaOffset = 0x28;
    IndexBuffer->Ntfs.UsaCount = 9;

    // TODO: Check bitmap for VCN
    ASSERT(Node->HasValidVCN);
    IndexBuffer->VCN = Node->VCN;

    // Windows seems to alternate between using 0x28 and 0x40 for the first entry offset of each index buffer.
    // Interestingly, neither Windows nor chkdsk seem to mind if we just use 0x28 for every index record.
    IndexBuffer->Header.FirstEntryOffset = 0x28; 
    IndexBuffer->Header.AllocatedSize = BufferSize - FIELD_OFFSET(INDEX_BUFFER, Header);

    // Start summing the total size of this node's entries
    IndexBuffer->Header.TotalSizeOfEntries = IndexBuffer->Header.FirstEntryOffset;

    CurrentKey = Node->FirstKey;
    CurrentNodeEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)&(IndexBuffer->Header)
                                                + IndexBuffer->Header.FirstEntryOffset);
    for (i = 0; i < Node->KeyCount; i++)
    {
        // Would adding the current entry to the index increase the node size beyond the allocation size?
        ULONG IndexSize = FIELD_OFFSET(INDEX_BUFFER, Header)
            + IndexBuffer->Header.TotalSizeOfEntries
            + CurrentNodeEntry->Length;
        if (IndexSize > BufferSize)
        {
            DPRINT1("TODO: Adding file would require creating a new node!\n");
            return STATUS_NOT_IMPLEMENTED;
        }

        ASSERT(CurrentKey->IndexEntry->Length != 0);

        // Copy the index entry
        RtlCopyMemory(CurrentNodeEntry, CurrentKey->IndexEntry, CurrentKey->IndexEntry->Length);

        DPRINT("Index Node Entry Stream Length: %u\nIndex Node Entry Length: %u\n",
               CurrentNodeEntry->KeyLength,
               CurrentNodeEntry->Length);

        // Add Length of Current Entry to Total Size of Entries
        IndexBuffer->Header.TotalSizeOfEntries += CurrentNodeEntry->Length;

        // Check for child nodes
        if (HasChildren)
            IndexBuffer->Header.Flags = INDEX_NODE_LARGE;

        // Go to the next node entry
        CurrentNodeEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)CurrentNodeEntry + CurrentNodeEntry->Length);
        CurrentKey = CurrentKey->NextKey;
    }

    Status = AddFixupArray(DeviceExt, &IndexBuffer->Ntfs);

    return Status;
}