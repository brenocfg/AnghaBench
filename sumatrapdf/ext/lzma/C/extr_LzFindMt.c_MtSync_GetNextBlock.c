#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numProcessedBlocks; void* csWasEntered; int /*<<< orphan*/  cs; int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; int /*<<< orphan*/  wasStopped; void* exit; void* stopWriting; void* needStart; } ;
typedef  TYPE_1__ CMtSync ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CriticalSection_Leave (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Wait (int /*<<< orphan*/ *) ; 
 void* False ; 
 int /*<<< orphan*/  Semaphore_Release1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Semaphore_Wait (int /*<<< orphan*/ *) ; 
 void* True ; 

void MtSync_GetNextBlock(CMtSync *p)
{
  if (p->needStart)
  {
    p->numProcessedBlocks = 1;
    p->needStart = False;
    p->stopWriting = False;
    p->exit = False;
    Event_Reset(&p->wasStarted);
    Event_Reset(&p->wasStopped);

    Event_Set(&p->canStart);
    Event_Wait(&p->wasStarted);
  }
  else
  {
    CriticalSection_Leave(&p->cs);
    p->csWasEntered = False;
    p->numProcessedBlocks++;
    Semaphore_Release1(&p->freeSemaphore);
  }
  Semaphore_Wait(&p->filledSemaphore);
  CriticalSection_Enter(&p->cs);
  p->csWasEntered = True;
}