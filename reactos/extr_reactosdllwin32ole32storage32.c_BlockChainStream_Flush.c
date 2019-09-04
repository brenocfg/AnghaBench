#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* cachedBlocks; int /*<<< orphan*/  parentStorage; } ;
struct TYPE_4__ {scalar_t__ dirty; int /*<<< orphan*/  data; int /*<<< orphan*/  sector; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ BlockChainStream ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STG_E_WRITEFAULT ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ StorageImpl_WriteBigBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HRESULT BlockChainStream_Flush(BlockChainStream* This)
{
  int i;
  if (!This) return S_OK;
  for (i=0; i<2; i++)
  {
    if (This->cachedBlocks[i].dirty)
    {
      if (StorageImpl_WriteBigBlock(This->parentStorage, This->cachedBlocks[i].sector, This->cachedBlocks[i].data))
        This->cachedBlocks[i].dirty = FALSE;
      else
        return STG_E_WRITEFAULT;
    }
  }
  return S_OK;
}