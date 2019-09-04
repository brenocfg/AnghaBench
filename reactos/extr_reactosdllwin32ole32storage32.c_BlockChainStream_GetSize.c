#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
struct TYPE_9__ {int QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_12__ {int bigBlockSize; } ;
struct TYPE_11__ {TYPE_4__* parentStorage; int /*<<< orphan*/  ownerDirEntry; int /*<<< orphan*/ * headOfStreamPlaceHolder; } ;
struct TYPE_10__ {TYPE_1__ size; } ;
typedef  TYPE_2__ DirEntry ;
typedef  TYPE_3__ BlockChainStream ;

/* Variables and functions */
 scalar_t__ BlockChainStream_GetCount (TYPE_3__*) ; 
 int /*<<< orphan*/  StorageImpl_ReadDirEntry (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static ULARGE_INTEGER BlockChainStream_GetSize(BlockChainStream* This)
{
  DirEntry chainEntry;

  if(This->headOfStreamPlaceHolder == NULL)
  {
    /*
     * This chain has a directory entry so use the size value from there.
     */
    StorageImpl_ReadDirEntry(
      This->parentStorage,
      This->ownerDirEntry,
      &chainEntry);

    return chainEntry.size;
  }
  else
  {
    /*
     * this chain is a chain that does not have a directory entry, figure out the
     * size by making the product number of used blocks times the
     * size of them
     */
    ULARGE_INTEGER result;
    result.QuadPart =
      (ULONGLONG)BlockChainStream_GetCount(This) *
      This->parentStorage->bigBlockSize;

    return result;
  }
}