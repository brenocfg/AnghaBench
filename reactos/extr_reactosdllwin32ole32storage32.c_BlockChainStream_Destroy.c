#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* indexCache; } ;
typedef  TYPE_1__ BlockChainStream ;

/* Variables and functions */
 int /*<<< orphan*/  BlockChainStream_Flush (TYPE_1__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void BlockChainStream_Destroy(BlockChainStream* This)
{
  if (This)
  {
    BlockChainStream_Flush(This);
    HeapFree(GetProcessHeap(), 0, This->indexCache);
  }
  HeapFree(GetProcessHeap(), 0, This);
}