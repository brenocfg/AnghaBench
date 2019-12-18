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
typedef  int /*<<< orphan*/  WRes ;
struct TYPE_3__ {int stop; int /*<<< orphan*/  thread; int /*<<< orphan*/  startEvent; } ;
typedef  TYPE_1__ CLoopThread ;

/* Variables and functions */
 scalar_t__ Event_Set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SZ_ERROR_THREAD ; 
 int /*<<< orphan*/  Thread_Wait (int /*<<< orphan*/ *) ; 

WRes LoopThread_StopAndWait(CLoopThread *p)
{
  p->stop = 1;
  if (Event_Set(&p->startEvent) != 0)
    return SZ_ERROR_THREAD;
  return Thread_Wait(&p->thread);
}