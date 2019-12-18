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
struct TYPE_4__ {void* wasCreated; int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  wasStopped; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; void* csWasInitialized; int /*<<< orphan*/  cs; int /*<<< orphan*/  thread; scalar_t__ needStart; int /*<<< orphan*/  exit; } ;
typedef  TYPE_1__ CMtSync ;

/* Variables and functions */
 int /*<<< orphan*/  CriticalSection_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Event_Set (int /*<<< orphan*/ *) ; 
 void* False ; 
 int /*<<< orphan*/  MtSync_StopWriting (TYPE_1__*) ; 
 int /*<<< orphan*/  Semaphore_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Wait (int /*<<< orphan*/ *) ; 
 scalar_t__ Thread_WasCreated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  True ; 

void MtSync_Destruct(CMtSync *p)
{
  if (Thread_WasCreated(&p->thread))
  {
    MtSync_StopWriting(p);
    p->exit = True;
    if (p->needStart)
      Event_Set(&p->canStart);
    Thread_Wait(&p->thread);
    Thread_Close(&p->thread);
  }
  if (p->csWasInitialized)
  {
    CriticalSection_Delete(&p->cs);
    p->csWasInitialized = False;
  }

  Event_Close(&p->canStart);
  Event_Close(&p->wasStarted);
  Event_Close(&p->wasStopped);
  Semaphore_Close(&p->freeSemaphore);
  Semaphore_Close(&p->filledSemaphore);

  p->wasCreated = False;
}