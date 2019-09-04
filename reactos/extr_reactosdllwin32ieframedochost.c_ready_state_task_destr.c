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
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_3__ {int /*<<< orphan*/  doc; } ;
typedef  TYPE_1__ ready_state_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void ready_state_task_destr(task_header_t *_task)
{
    ready_state_task_t *task = (ready_state_task_t*)_task;

    IUnknown_Release(task->doc);
    heap_free(task);
}