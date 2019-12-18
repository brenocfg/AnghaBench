#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UInt32 ;
struct TYPE_5__ {int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  wasStopped; scalar_t__ numProcessedBlocks; scalar_t__ stopWriting; scalar_t__ exit; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; } ;
struct TYPE_6__ {int /*<<< orphan*/  hashSync; TYPE_1__ btSync; } ;
typedef  TYPE_1__ CMtSync ;
typedef  TYPE_2__ CMatchFinderMt ;

/* Variables and functions */
 int /*<<< orphan*/  BtFillBlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MtSync_StopWriting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Release1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Wait (int /*<<< orphan*/ *) ; 

void BtThreadFunc(CMatchFinderMt *mt)
{
  CMtSync *p = &mt->btSync;
  for (;;)
  {
    UInt32 blockIndex = 0;
    Event_Wait(&p->canStart);
    Event_Set(&p->wasStarted);
    for (;;)
    {
      if (p->exit)
        return;
      if (p->stopWriting)
      {
        p->numProcessedBlocks = blockIndex;
        MtSync_StopWriting(&mt->hashSync);
        Event_Set(&p->wasStopped);
        break;
      }
      Semaphore_Wait(&p->freeSemaphore);
      BtFillBlock(mt, blockIndex++);
      Semaphore_Release1(&p->filledSemaphore);
    }
  }
}