#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ zv_open_count; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_suspend_ref; int /*<<< orphan*/  zv_name; } ;
typedef  TYPE_1__ zvol_state_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* zv_free ) (TYPE_1__*) ;int /*<<< orphan*/  (* zv_clear_private ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_5__* ops ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 scalar_t__ zvol_inhibit_dev ; 
 int /*<<< orphan*/  zvol_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_state_list ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static void
zvol_remove_minor_impl(const char *name)
{
	zvol_state_t *zv = NULL, *zv_next;

	if (zvol_inhibit_dev)
		return;

	rw_enter(&zvol_state_lock, RW_WRITER);

	for (zv = list_head(&zvol_state_list); zv != NULL; zv = zv_next) {
		zv_next = list_next(&zvol_state_list, zv);

		mutex_enter(&zv->zv_state_lock);
		if (strcmp(zv->zv_name, name) == 0) {
			/*
			 * By holding zv_state_lock here, we guarantee that no
			 * one is currently using this zv
			 */

			/* If in use, leave alone */
			if (zv->zv_open_count > 0 ||
			    atomic_read(&zv->zv_suspend_ref)) {
				mutex_exit(&zv->zv_state_lock);
				continue;
			}
			zvol_remove(zv);

			ops->zv_clear_private(zv);
			mutex_exit(&zv->zv_state_lock);
			break;
		} else {
			mutex_exit(&zv->zv_state_lock);
		}
	}

	/* Drop zvol_state_lock before calling zvol_free() */
	rw_exit(&zvol_state_lock);

	if (zv != NULL)
		ops->zv_free(zv);
}