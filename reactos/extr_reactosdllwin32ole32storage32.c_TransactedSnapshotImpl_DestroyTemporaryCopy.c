#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ QuadPart; } ;
typedef  TYPE_3__ ULARGE_INTEGER ;
struct TYPE_12__ {size_t storageDirEntry; } ;
struct TYPE_14__ {int /*<<< orphan*/  transactedParent; TYPE_5__* entries; TYPE_2__ base; } ;
typedef  TYPE_4__ TransactedSnapshotImpl ;
struct TYPE_11__ {size_t dirRootEntry; } ;
struct TYPE_15__ {int /*<<< orphan*/  transactedParentEntry; int /*<<< orphan*/  newTransactedParentEntry; scalar_t__ stream_dirty; TYPE_1__ data; int /*<<< orphan*/  read; } ;
typedef  TYPE_5__ TransactedDirEntry ;
typedef  size_t DirRef ;

/* Variables and functions */
 size_t DIRENTRY_NULL ; 
 int /*<<< orphan*/  StorageBaseImpl_DestroyDirEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StorageBaseImpl_StreamSetSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__) ; 
 size_t TransactedSnapshotImpl_FindFirstChild (TYPE_4__*,size_t) ; 
 size_t TransactedSnapshotImpl_FindNextChild (TYPE_4__*,size_t) ; 
 scalar_t__ TransactedSnapshotImpl_MadeCopy (TYPE_4__*,size_t) ; 

__attribute__((used)) static void TransactedSnapshotImpl_DestroyTemporaryCopy(
  TransactedSnapshotImpl* This, DirRef stop)
{
  DirRef cursor;
  TransactedDirEntry *entry;
  ULARGE_INTEGER zero;

  zero.QuadPart = 0;

  if (!This->entries[This->base.storageDirEntry].read)
    return;

  cursor = This->entries[This->base.storageDirEntry].data.dirRootEntry;

  if (cursor == DIRENTRY_NULL)
    return;

  cursor = TransactedSnapshotImpl_FindFirstChild(This, cursor);

  while (cursor != DIRENTRY_NULL && cursor != stop)
  {
    if (TransactedSnapshotImpl_MadeCopy(This, cursor))
    {
      entry = &This->entries[cursor];

      if (entry->stream_dirty)
        StorageBaseImpl_StreamSetSize(This->transactedParent,
          entry->newTransactedParentEntry, zero);

      StorageBaseImpl_DestroyDirEntry(This->transactedParent,
        entry->newTransactedParentEntry);

      entry->newTransactedParentEntry = entry->transactedParentEntry;
    }

    cursor = TransactedSnapshotImpl_FindNextChild(This, cursor);
  }
}