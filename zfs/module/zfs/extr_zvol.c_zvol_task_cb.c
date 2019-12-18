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
struct TYPE_3__ {int op; int /*<<< orphan*/  value; int /*<<< orphan*/  name1; int /*<<< orphan*/  name2; } ;
typedef  TYPE_1__ zvol_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
#define  ZVOL_ASYNC_CREATE_MINORS 132 
#define  ZVOL_ASYNC_REMOVE_MINORS 131 
#define  ZVOL_ASYNC_RENAME_MINORS 130 
#define  ZVOL_ASYNC_SET_SNAPDEV 129 
#define  ZVOL_ASYNC_SET_VOLMODE 128 
 int /*<<< orphan*/  zvol_create_minors_impl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_remove_minors_impl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_rename_minors_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_set_snapdev_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_set_volmode_impl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_task_free (TYPE_1__*) ; 

__attribute__((used)) static void
zvol_task_cb(void *param)
{
	zvol_task_t *task = (zvol_task_t *)param;

	switch (task->op) {
	case ZVOL_ASYNC_CREATE_MINORS:
		(void) zvol_create_minors_impl(task->name1);
		break;
	case ZVOL_ASYNC_REMOVE_MINORS:
		zvol_remove_minors_impl(task->name1);
		break;
	case ZVOL_ASYNC_RENAME_MINORS:
		zvol_rename_minors_impl(task->name1, task->name2);
		break;
	case ZVOL_ASYNC_SET_SNAPDEV:
		zvol_set_snapdev_impl(task->name1, task->value);
		break;
	case ZVOL_ASYNC_SET_VOLMODE:
		zvol_set_volmode_impl(task->name1, task->value);
		break;
	default:
		VERIFY(0);
		break;
	}

	zvol_task_free(task);
}