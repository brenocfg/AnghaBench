#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dsl_prop_changed_cb_t ;
struct TYPE_12__ {void* cbr_arg; TYPE_1__* cbr_pr; int /*<<< orphan*/ * cbr_func; TYPE_4__* cbr_ds; } ;
typedef  TYPE_2__ dsl_prop_cb_record_t ;
struct TYPE_13__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_3__ dsl_dir_t ;
struct TYPE_14__ {int /*<<< orphan*/  ds_prop_cbs; TYPE_3__* ds_dir; } ;
typedef  TYPE_4__ dsl_dataset_t ;
struct TYPE_11__ {int /*<<< orphan*/  pr_cbs; int /*<<< orphan*/  pr_propname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMSG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
dsl_prop_unregister(dsl_dataset_t *ds, const char *propname,
    dsl_prop_changed_cb_t *callback, void *cbarg)
{
	dsl_dir_t *dd = ds->ds_dir;
	dsl_prop_cb_record_t *cbr;

	mutex_enter(&dd->dd_lock);
	for (cbr = list_head(&ds->ds_prop_cbs);
	    cbr; cbr = list_next(&ds->ds_prop_cbs, cbr)) {
		if (cbr->cbr_ds == ds &&
		    cbr->cbr_func == callback &&
		    cbr->cbr_arg == cbarg &&
		    strcmp(cbr->cbr_pr->pr_propname, propname) == 0)
			break;
	}

	if (cbr == NULL) {
		mutex_exit(&dd->dd_lock);
		return (SET_ERROR(ENOMSG));
	}

	list_remove(&ds->ds_prop_cbs, cbr);
	list_remove(&cbr->cbr_pr->pr_cbs, cbr);
	mutex_exit(&dd->dd_lock);
	kmem_free(cbr, sizeof (dsl_prop_cb_record_t));

	return (0);
}