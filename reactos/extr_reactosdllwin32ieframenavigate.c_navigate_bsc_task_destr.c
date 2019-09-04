#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* bsc; } ;
typedef  TYPE_2__ task_navigate_bsc_t ;
typedef  int /*<<< orphan*/  task_header_t ;
struct TYPE_4__ {int /*<<< orphan*/  IBindStatusCallback_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 

__attribute__((used)) static void navigate_bsc_task_destr(task_header_t *t)
{
    task_navigate_bsc_t *task = (task_navigate_bsc_t*)t;

    IBindStatusCallback_Release(&task->bsc->IBindStatusCallback_iface);
    heap_free(task);
}