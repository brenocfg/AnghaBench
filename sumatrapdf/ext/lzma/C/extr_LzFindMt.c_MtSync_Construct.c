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
struct TYPE_3__ {int /*<<< orphan*/  filledSemaphore; int /*<<< orphan*/  freeSemaphore; int /*<<< orphan*/  wasStopped; int /*<<< orphan*/  wasStarted; int /*<<< orphan*/  canStart; int /*<<< orphan*/  thread; void* csWasEntered; void* csWasInitialized; void* wasCreated; } ;
typedef  TYPE_1__ CMtSync ;

/* Variables and functions */
 int /*<<< orphan*/  Event_Construct (int /*<<< orphan*/ *) ; 
 void* False ; 
 int /*<<< orphan*/  Semaphore_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Thread_Construct (int /*<<< orphan*/ *) ; 

void MtSync_Construct(CMtSync *p)
{
  p->wasCreated = False;
  p->csWasInitialized = False;
  p->csWasEntered = False;
  Thread_Construct(&p->thread);
  Event_Construct(&p->canStart);
  Event_Construct(&p->wasStarted);
  Event_Construct(&p->wasStopped);
  Semaphore_Construct(&p->freeSemaphore);
  Semaphore_Construct(&p->filledSemaphore);
}