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
typedef  int /*<<< orphan*/  zvol_task_t ;
typedef  scalar_t__ taskqid_t ;
struct TYPE_3__ {int /*<<< orphan*/  spa_zvol_taskq; } ;
typedef  TYPE_1__ spa_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ TASKQID_INVALID ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  ZVOL_ASYNC_CREATE_MINORS ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_wait_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * zvol_task_alloc (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  zvol_task_cb ; 

void
zvol_create_minors(spa_t *spa, const char *name, boolean_t async)
{
	zvol_task_t *task;
	taskqid_t id;

	task = zvol_task_alloc(ZVOL_ASYNC_CREATE_MINORS, name, NULL, ~0ULL);
	if (task == NULL)
		return;

	id = taskq_dispatch(spa->spa_zvol_taskq, zvol_task_cb, task, TQ_SLEEP);
	if ((async == B_FALSE) && (id != TASKQID_INVALID))
		taskq_wait_id(spa->spa_zvol_taskq, id);
}