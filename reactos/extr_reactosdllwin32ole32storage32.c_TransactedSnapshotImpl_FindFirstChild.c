#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* entries; } ;
typedef  TYPE_2__ TransactedSnapshotImpl ;
struct TYPE_5__ {size_t leftChild; size_t rightChild; size_t dirRootEntry; } ;
struct TYPE_7__ {size_t parent; TYPE_1__ data; scalar_t__ read; } ;
typedef  TYPE_3__ TransactedDirEntry ;
typedef  size_t DirRef ;

/* Variables and functions */
 size_t DIRENTRY_NULL ; 

__attribute__((used)) static DirRef TransactedSnapshotImpl_FindFirstChild(
  TransactedSnapshotImpl* This, DirRef parent)
{
  DirRef cursor, prev;
  TransactedDirEntry *entry;

  cursor = parent;
  entry = &This->entries[cursor];
  while (entry->read)
  {
    if (entry->data.leftChild != DIRENTRY_NULL)
    {
      prev = cursor;
      cursor = entry->data.leftChild;
      entry = &This->entries[cursor];
      entry->parent = prev;
    }
    else if (entry->data.rightChild != DIRENTRY_NULL)
    {
      prev = cursor;
      cursor = entry->data.rightChild;
      entry = &This->entries[cursor];
      entry->parent = prev;
    }
    else if (entry->data.dirRootEntry != DIRENTRY_NULL)
    {
      prev = cursor;
      cursor = entry->data.dirRootEntry;
      entry = &This->entries[cursor];
      entry->parent = prev;
    }
    else
      break;
  }

  return cursor;
}