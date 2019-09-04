#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
struct TYPE_7__ {TYPE_2__* bsc; } ;
typedef  TYPE_3__ stop_request_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;
struct TYPE_6__ {TYPE_1__ bsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 

__attribute__((used)) static void stop_request_task_destr(task_t *_task)
{
    stop_request_task_t *task = (stop_request_task_t*)_task;

    IBindStatusCallback_Release(&task->bsc->bsc.IBindStatusCallback_iface);
    heap_free(task);
}