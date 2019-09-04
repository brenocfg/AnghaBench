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
struct BlockChainRun {scalar_t__ lastOffset; scalar_t__ firstSector; scalar_t__ firstOffset; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_4__ {int indexCacheLen; int indexCacheSize; scalar_t__ tailIndex; scalar_t__ numBlocks; int /*<<< orphan*/  parentStorage; struct BlockChainRun* indexCache; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BlockChainStream ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 scalar_t__ BlockChainStream_GetHeadOfChain (TYPE_1__*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct BlockChainRun*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageImpl_GetNextBlockInChain (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (struct BlockChainRun*,struct BlockChainRun*,int) ; 

__attribute__((used)) static HRESULT BlockChainStream_UpdateIndexCache(BlockChainStream* This)
{
  ULONG  next_sector, next_offset;
  HRESULT hr;
  struct BlockChainRun *last_run;

  if (This->indexCacheLen == 0)
  {
    last_run = NULL;
    next_offset = 0;
    next_sector = BlockChainStream_GetHeadOfChain(This);
  }
  else
  {
    last_run = &This->indexCache[This->indexCacheLen-1];
    next_offset = last_run->lastOffset+1;
    hr = StorageImpl_GetNextBlockInChain(This->parentStorage,
        last_run->firstSector + last_run->lastOffset - last_run->firstOffset,
        &next_sector);
    if (FAILED(hr)) return hr;
  }

  while (next_sector != BLOCK_END_OF_CHAIN)
  {
    if (!last_run || next_sector != last_run->firstSector + next_offset - last_run->firstOffset)
    {
      /* Add the current block to the cache. */
      if (This->indexCacheSize == 0)
      {
        This->indexCache = HeapAlloc(GetProcessHeap(), 0, sizeof(struct BlockChainRun)*16);
        if (!This->indexCache) return E_OUTOFMEMORY;
        This->indexCacheSize = 16;
      }
      else if (This->indexCacheSize == This->indexCacheLen)
      {
        struct BlockChainRun *new_cache;
        ULONG new_size;

        new_size = This->indexCacheSize * 2;
        new_cache = HeapAlloc(GetProcessHeap(), 0, sizeof(struct BlockChainRun)*new_size);
        if (!new_cache) return E_OUTOFMEMORY;
        memcpy(new_cache, This->indexCache, sizeof(struct BlockChainRun)*This->indexCacheLen);

        HeapFree(GetProcessHeap(), 0, This->indexCache);
        This->indexCache = new_cache;
        This->indexCacheSize = new_size;
      }

      This->indexCacheLen++;
      last_run = &This->indexCache[This->indexCacheLen-1];
      last_run->firstSector = next_sector;
      last_run->firstOffset = next_offset;
    }

    last_run->lastOffset = next_offset;

    /* Find the next block. */
    next_offset++;
    hr = StorageImpl_GetNextBlockInChain(This->parentStorage, next_sector, &next_sector);
    if (FAILED(hr)) return hr;
  }

  if (This->indexCacheLen)
  {
    This->tailIndex = last_run->firstSector + last_run->lastOffset - last_run->firstOffset;
    This->numBlocks = last_run->lastOffset+1;
  }
  else
  {
    This->tailIndex = BLOCK_END_OF_CHAIN;
    This->numBlocks = 0;
  }

  return S_OK;
}