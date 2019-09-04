#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  int ULONG ;
struct TYPE_11__ {int /*<<< orphan*/ * NextKey; TYPE_3__* IndexEntry; } ;
struct TYPE_8__ {int /*<<< orphan*/  IndexedFile; } ;
struct TYPE_9__ {TYPE_1__ Directory; } ;
struct TYPE_10__ {int Length; int KeyLength; int /*<<< orphan*/  FileName; TYPE_2__ Data; } ;
typedef  TYPE_3__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  int /*<<< orphan*/  PFILENAME_ATTRIBUTE ;
typedef  TYPE_4__* PB_TREE_KEY ;
typedef  int /*<<< orphan*/  B_TREE_KEY ;

/* Variables and functions */
 int ALIGN_UP_BY (int,int) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileName ; 
 int GetFileNameAttributeLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX_ENTRY_ATTRIBUTE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  TAG_NTFS ; 

PB_TREE_KEY
CreateBTreeKeyFromFilename(ULONGLONG FileReference, PFILENAME_ATTRIBUTE FileNameAttribute)
{
    PB_TREE_KEY NewKey;
    ULONG AttributeSize = GetFileNameAttributeLength(FileNameAttribute);
    ULONG EntrySize = ALIGN_UP_BY(AttributeSize + FIELD_OFFSET(INDEX_ENTRY_ATTRIBUTE, FileName), 8);

    // Create a new Index Entry for the file
    PINDEX_ENTRY_ATTRIBUTE NewEntry = ExAllocatePoolWithTag(NonPagedPool, EntrySize, TAG_NTFS);
    if (!NewEntry)
    {
        DPRINT1("ERROR: Failed to allocate memory for Index Entry!\n");
        return NULL;
    }

    // Setup the Index Entry
    RtlZeroMemory(NewEntry, EntrySize);
    NewEntry->Data.Directory.IndexedFile = FileReference;
    NewEntry->Length = EntrySize;
    NewEntry->KeyLength = AttributeSize;

    // Copy the FileNameAttribute
    RtlCopyMemory(&NewEntry->FileName, FileNameAttribute, AttributeSize);

    // Setup the New Key
    NewKey = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_KEY), TAG_NTFS);
    if (!NewKey)
    {
        DPRINT1("ERROR: Failed to allocate memory for new key!\n");
        ExFreePoolWithTag(NewEntry, TAG_NTFS);
        return NULL;
    }
    NewKey->IndexEntry = NewEntry;
    NewKey->NextKey = NULL;

    return NewKey;
}