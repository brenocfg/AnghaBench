#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {scalar_t__ index; scalar_t__ sector; void* read; void* dirty; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int blockToEvict; int /*<<< orphan*/  parentStorage; TYPE_2__* cachedBlocks; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BlockChainStream ;
typedef  TYPE_2__ BlockChainBlock ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ BLOCK_END_OF_CHAIN ; 
 scalar_t__ BlockChainStream_GetSectorOfOffset (TYPE_1__*,scalar_t__) ; 
 void* FALSE ; 
 int /*<<< orphan*/  STG_E_DOCFILECORRUPT ; 
 int /*<<< orphan*/  STG_E_WRITEFAULT ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageImpl_WriteBigBlock (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT BlockChainStream_GetBlockAtOffset(BlockChainStream *This,
    ULONG index, BlockChainBlock **block, ULONG *sector, BOOL create)
{
  BlockChainBlock *result=NULL;
  int i;

  for (i=0; i<2; i++)
    if (This->cachedBlocks[i].index == index)
    {
      *sector = This->cachedBlocks[i].sector;
      *block = &This->cachedBlocks[i];
      return S_OK;
    }

  *sector = BlockChainStream_GetSectorOfOffset(This, index);
  if (*sector == BLOCK_END_OF_CHAIN)
    return STG_E_DOCFILECORRUPT;

  if (create)
  {
    if (This->cachedBlocks[0].index == 0xffffffff)
      result = &This->cachedBlocks[0];
    else if (This->cachedBlocks[1].index == 0xffffffff)
      result = &This->cachedBlocks[1];
    else
    {
      result = &This->cachedBlocks[This->blockToEvict++];
      if (This->blockToEvict == 2)
        This->blockToEvict = 0;
    }

    if (result->dirty)
    {
      if (!StorageImpl_WriteBigBlock(This->parentStorage, result->sector, result->data))
        return STG_E_WRITEFAULT;
      result->dirty = FALSE;
    }

    result->read = FALSE;
    result->index = index;
    result->sector = *sector;
  }

  *block = result;
  return S_OK;
}