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
struct TYPE_4__ {int /*<<< orphan*/  disp; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ task_timer_t ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_task_timer(HWND thread_hwnd, task_timer_t *timer)
{
    list_remove(&timer->entry);

    IDispatch_Release(timer->disp);

    heap_free(timer);
}