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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {scalar_t__ dirRootEntry; scalar_t__ leftChild; scalar_t__ rightChild; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DirRef ;
typedef  TYPE_1__ DirEntry ;

/* Variables and functions */
 scalar_t__ DIRENTRY_NULL ; 
 int /*<<< orphan*/  DIRENTRY_RELATION_DIR ; 
 int /*<<< orphan*/  DIRENTRY_RELATION_NEXT ; 
 int /*<<< orphan*/  DIRENTRY_RELATION_PREVIOUS ; 
 int /*<<< orphan*/  STG_E_FILENOTFOUND ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageBaseImpl_ReadDirEntry (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 scalar_t__ entryNameCmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT findTreeParent(StorageBaseImpl *storage, DirRef storageEntry,
    const OLECHAR *childName, DirEntry *parentData, DirRef *parentEntry,
    ULONG *relation)
{
  DirRef childEntry;
  DirEntry childData;

  /* Read the storage entry to find the root of the tree. */
  StorageBaseImpl_ReadDirEntry(storage, storageEntry, parentData);

  *parentEntry = storageEntry;
  *relation = DIRENTRY_RELATION_DIR;

  childEntry = parentData->dirRootEntry;

  while (childEntry != DIRENTRY_NULL)
  {
    LONG cmp;

    StorageBaseImpl_ReadDirEntry(storage, childEntry, &childData);

    cmp = entryNameCmp(childName, childData.name);

    if (cmp == 0)
      /* found it */
      break;

    else if (cmp < 0)
    {
      *parentData = childData;
      *parentEntry = childEntry;
      *relation = DIRENTRY_RELATION_PREVIOUS;

      childEntry = parentData->leftChild;
    }

    else if (cmp > 0)
    {
      *parentData = childData;
      *parentEntry = childEntry;
      *relation = DIRENTRY_RELATION_NEXT;

      childEntry = parentData->rightChild;
    }
  }

  if (childEntry == DIRENTRY_NULL)
    return STG_E_FILENOTFOUND;
  else
    return S_OK;
}