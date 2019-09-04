#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_8__ {TYPE_1__* parentStorage; } ;
struct TYPE_6__ {int /*<<< orphan*/  smallBlockDepotChain; } ;
typedef  TYPE_3__ SmallBlockChainStream ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int BLOCK_END_OF_CHAIN ; 
 int /*<<< orphan*/  BlockChainStream_ReadAt (int /*<<< orphan*/ ,TYPE_2__,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  STG_E_READFAULT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageUtl_ReadDWord (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static HRESULT SmallBlockChainStream_GetNextBlockInChain(
  SmallBlockChainStream* This,
  ULONG                  blockIndex,
  ULONG*                 nextBlockInChain)
{
  ULARGE_INTEGER offsetOfBlockInDepot;
  DWORD  buffer;
  ULONG  bytesRead;
  HRESULT res;

  *nextBlockInChain = BLOCK_END_OF_CHAIN;

  offsetOfBlockInDepot.QuadPart  = (ULONGLONG)blockIndex * sizeof(ULONG);

  /*
   * Read those bytes in the buffer from the small block file.
   */
  res = BlockChainStream_ReadAt(
              This->parentStorage->smallBlockDepotChain,
              offsetOfBlockInDepot,
              sizeof(DWORD),
              &buffer,
              &bytesRead);

  if (SUCCEEDED(res) && bytesRead != sizeof(DWORD))
    res = STG_E_READFAULT;

  if (SUCCEEDED(res))
  {
    StorageUtl_ReadDWord((BYTE *)&buffer, 0, nextBlockInChain);
    return S_OK;
  }

  return res;
}