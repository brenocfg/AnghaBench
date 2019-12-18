#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {TYPE_5__* cbr_ds; int /*<<< orphan*/  cbr_arg; int /*<<< orphan*/  (* cbr_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* cbr_pr; int /*<<< orphan*/  pr_cbs; } ;
typedef  TYPE_2__ dsl_prop_record_t ;
typedef  TYPE_2__ dsl_prop_cb_record_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/  dd_props; } ;
typedef  TYPE_4__ dsl_dir_t ;
struct TYPE_16__ {TYPE_4__* ds_dir; } ;
typedef  TYPE_5__ dsl_dataset_t ;
struct TYPE_13__ {int /*<<< orphan*/  pr_propname; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_try_add_ref (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_prop_get_ds (TYPE_5__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_prop_notify_all_cb(dsl_pool_t *dp, dsl_dataset_t *ds, void *arg)
{
	dsl_dir_t *dd = ds->ds_dir;
	dsl_prop_record_t *pr;
	dsl_prop_cb_record_t *cbr;

	mutex_enter(&dd->dd_lock);
	for (pr = list_head(&dd->dd_props);
	    pr; pr = list_next(&dd->dd_props, pr)) {
		for (cbr = list_head(&pr->pr_cbs); cbr;
		    cbr = list_next(&pr->pr_cbs, cbr)) {
			uint64_t value;

			/*
			 * Callback entries do not have holds on their
			 * datasets so that datasets with registered
			 * callbacks are still eligible for eviction.
			 * Unlike operations to update properties on a
			 * single dataset, we are performing a recursive
			 * descent of related head datasets.  The caller
			 * of this function only has a dataset hold on
			 * the passed in head dataset, not the snapshots
			 * associated with this dataset.  Without a hold,
			 * the dataset pointer within callback records
			 * for snapshots can be invalidated by eviction
			 * at any time.
			 *
			 * Use dsl_dataset_try_add_ref() to verify
			 * that the dataset for a snapshot has not
			 * begun eviction processing and to prevent
			 * eviction from occurring for the duration of
			 * the callback.  If the hold attempt fails,
			 * this object is already being evicted and the
			 * callback can be safely ignored.
			 */
			if (ds != cbr->cbr_ds &&
			    !dsl_dataset_try_add_ref(dp, cbr->cbr_ds, FTAG))
				continue;

			if (dsl_prop_get_ds(cbr->cbr_ds,
			    cbr->cbr_pr->pr_propname, sizeof (value), 1,
			    &value, NULL) == 0)
				cbr->cbr_func(cbr->cbr_arg, value);

			if (ds != cbr->cbr_ds)
				dsl_dataset_rele(cbr->cbr_ds, FTAG);
		}
	}
	mutex_exit(&dd->dd_lock);

	return (0);
}