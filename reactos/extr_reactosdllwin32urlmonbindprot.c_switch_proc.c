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
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ switch_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  protocol_handler; } ;
typedef  TYPE_2__ BindProtocol ;

/* Variables and functions */
 int /*<<< orphan*/  IInternetProtocol_Continue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void switch_proc(BindProtocol *bind, task_header_t *t)
{
    switch_task_t *task = (switch_task_t*)t;

    IInternetProtocol_Continue(bind->protocol_handler, task->data);

    heap_free(task);
}