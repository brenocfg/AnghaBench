#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_12__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ ULARGE_INTEGER ;
struct TYPE_15__ {scalar_t__ bigBlockSize; } ;
struct TYPE_14__ {scalar_t__ data; void* dirty; void* read; int /*<<< orphan*/  sector; } ;
struct TYPE_13__ {TYPE_4__* parentStorage; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_2__ BlockChainStream ;
typedef  TYPE_3__ BlockChainBlock ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BlockChainStream_GetBlockAtOffset (TYPE_2__*,scalar_t__,TYPE_3__**,scalar_t__*,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STG_E_READFAULT ; 
 int /*<<< orphan*/  STG_E_WRITEFAULT ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ StorageImpl_GetBigBlockOffset (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  StorageImpl_ReadBigBlock (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  StorageImpl_WriteAt (TYPE_4__*,TYPE_1__,int /*<<< orphan*/  const*,scalar_t__,scalar_t__*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

HRESULT BlockChainStream_WriteAt(BlockChainStream* This,
  ULARGE_INTEGER    offset,
  ULONG             size,
  const void*       buffer,
  ULONG*            bytesWritten)
{
  ULONG blockNoInSequence = offset.QuadPart / This->parentStorage->bigBlockSize;
  ULONG offsetInBlock     = offset.QuadPart % This->parentStorage->bigBlockSize;
  ULONG bytesToWrite;
  ULONG blockIndex;
  const BYTE* bufferWalker;
  HRESULT hr;
  BlockChainBlock *cachedBlock;

  *bytesWritten   = 0;
  bufferWalker = buffer;

  while (size > 0)
  {
    ULARGE_INTEGER ulOffset;
    DWORD bytesWrittenAt;

    /*
     * Calculate how many bytes we can copy to this big block.
     */
    bytesToWrite =
      min(This->parentStorage->bigBlockSize - offsetInBlock, size);

    hr = BlockChainStream_GetBlockAtOffset(This, blockNoInSequence, &cachedBlock, &blockIndex, size == bytesToWrite);

    /* BlockChainStream_SetSize should have already been called to ensure we have
     * enough blocks in the chain to write into */
    if (FAILED(hr))
    {
      ERR("not enough blocks in chain to write data\n");
      return hr;
    }

    if (!cachedBlock)
    {
      /* Not in cache, and we're going to write past the end of the block. */
      ulOffset.QuadPart = StorageImpl_GetBigBlockOffset(This->parentStorage, blockIndex) +
                               offsetInBlock;

      StorageImpl_WriteAt(This->parentStorage,
           ulOffset,
           bufferWalker,
           bytesToWrite,
           &bytesWrittenAt);
    }
    else
    {
      if (!cachedBlock->read && bytesToWrite != This->parentStorage->bigBlockSize)
      {
        ULONG read;
        if (FAILED(StorageImpl_ReadBigBlock(This->parentStorage, cachedBlock->sector, cachedBlock->data, &read)) && !read)
          return STG_E_READFAULT;
      }

      memcpy(cachedBlock->data+offsetInBlock, bufferWalker, bytesToWrite);
      bytesWrittenAt = bytesToWrite;
      cachedBlock->read = TRUE;
      cachedBlock->dirty = TRUE;
    }

    blockNoInSequence++;
    bufferWalker  += bytesWrittenAt;
    size          -= bytesWrittenAt;
    *bytesWritten += bytesWrittenAt;
    offsetInBlock  = 0;      /* There is no offset on the next block */

    if (bytesWrittenAt != bytesToWrite)
      break;
  }

  return (size == 0) ? S_OK : STG_E_WRITEFAULT;
}