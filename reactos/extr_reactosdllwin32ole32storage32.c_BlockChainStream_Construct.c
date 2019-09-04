#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {struct TYPE_8__* indexCache; scalar_t__ blockToEvict; TYPE_1__* cachedBlocks; scalar_t__ indexCacheSize; scalar_t__ indexCacheLen; int /*<<< orphan*/  ownerDirEntry; int /*<<< orphan*/ * headOfStreamPlaceHolder; int /*<<< orphan*/ * parentStorage; } ;
struct TYPE_7__ {int index; void* dirty; } ;
typedef  int /*<<< orphan*/  StorageImpl ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  TYPE_2__ BlockChainStream ;

/* Variables and functions */
 int /*<<< orphan*/  BlockChainStream_UpdateIndexCache (TYPE_2__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

BlockChainStream* BlockChainStream_Construct(
  StorageImpl* parentStorage,
  ULONG*         headOfStreamPlaceHolder,
  DirRef         dirEntry)
{
  BlockChainStream* newStream;

  newStream = HeapAlloc(GetProcessHeap(), 0, sizeof(BlockChainStream));
  if(!newStream)
    return NULL;

  newStream->parentStorage           = parentStorage;
  newStream->headOfStreamPlaceHolder = headOfStreamPlaceHolder;
  newStream->ownerDirEntry           = dirEntry;
  newStream->indexCache              = NULL;
  newStream->indexCacheLen           = 0;
  newStream->indexCacheSize          = 0;
  newStream->cachedBlocks[0].index = 0xffffffff;
  newStream->cachedBlocks[0].dirty = FALSE;
  newStream->cachedBlocks[1].index = 0xffffffff;
  newStream->cachedBlocks[1].dirty = FALSE;
  newStream->blockToEvict          = 0;

  if (FAILED(BlockChainStream_UpdateIndexCache(newStream)))
  {
    HeapFree(GetProcessHeap(), 0, newStream->indexCache);
    HeapFree(GetProcessHeap(), 0, newStream);
    return NULL;
  }

  return newStream;
}