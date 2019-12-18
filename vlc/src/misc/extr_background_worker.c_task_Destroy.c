#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task {int /*<<< orphan*/  entity; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pf_release ) (int /*<<< orphan*/ ) ;} ;
struct background_worker {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct task*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_Destroy(struct background_worker *worker, struct task *task)
{
    worker->conf.pf_release(task->entity);
    free(task);
}