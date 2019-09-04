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
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_8__ {TYPE_1__* parentStorage; } ;
struct TYPE_6__ {int /*<<< orphan*/  smallBlockDepotChain; } ;
typedef  TYPE_3__ SmallBlockChainStream ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  BlockChainStream_WriteAt (int /*<<< orphan*/ ,TYPE_2__,int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  StorageUtl_WriteDWord (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void SmallBlockChainStream_SetNextBlockInChain(
  SmallBlockChainStream* This,
  ULONG                  blockIndex,
  ULONG                  nextBlock)
{
  ULARGE_INTEGER offsetOfBlockInDepot;
  DWORD  buffer;
  ULONG  bytesWritten;

  offsetOfBlockInDepot.QuadPart  = (ULONGLONG)blockIndex * sizeof(ULONG);

  StorageUtl_WriteDWord((BYTE *)&buffer, 0, nextBlock);

  /*
   * Read those bytes in the buffer from the small block file.
   */
  BlockChainStream_WriteAt(
    This->parentStorage->smallBlockDepotChain,
    offsetOfBlockInDepot,
    sizeof(DWORD),
    &buffer,
    &bytesWritten);
}