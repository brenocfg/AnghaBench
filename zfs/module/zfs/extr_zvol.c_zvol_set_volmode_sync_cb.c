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
typedef  int /*<<< orphan*/  zvol_task_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_1__* dp_spa; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_4__ {int /*<<< orphan*/  spa_zvol_taskq; } ;

/* Variables and functions */
 int MAXNAMELEN ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  ZVOL_ASYNC_SET_VOLMODE ; 
 int /*<<< orphan*/  dsl_dataset_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dsl_prop_get_int_ds (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zvol_task_alloc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_task_cb ; 

__attribute__((used)) static int
zvol_set_volmode_sync_cb(dsl_pool_t *dp, dsl_dataset_t *ds, void *arg)
{
	char dsname[MAXNAMELEN];
	zvol_task_t *task;
	uint64_t volmode;

	dsl_dataset_name(ds, dsname);
	if (dsl_prop_get_int_ds(ds, "volmode", &volmode) != 0)
		return (0);
	task = zvol_task_alloc(ZVOL_ASYNC_SET_VOLMODE, dsname, NULL, volmode);
	if (task == NULL)
		return (0);

	(void) taskq_dispatch(dp->dp_spa->spa_zvol_taskq, zvol_task_cb,
	    task, TQ_SLEEP);
	return (0);
}