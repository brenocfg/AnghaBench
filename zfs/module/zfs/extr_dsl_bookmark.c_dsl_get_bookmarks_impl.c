#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  ds_bookmarks; TYPE_1__* ds_dir; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_11__ {int /*<<< orphan*/  dbn_name; int /*<<< orphan*/  dbn_phys; } ;
typedef  TYPE_3__ dsl_bookmark_node_t ;
struct TYPE_9__ {int /*<<< orphan*/ * dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_bookmark_fetch_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_is_snapshot (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_pool_config_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 

int
dsl_get_bookmarks_impl(dsl_dataset_t *ds, nvlist_t *props, nvlist_t *outnvl)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;

	ASSERT(dsl_pool_config_held(dp));

	if (dsl_dataset_is_snapshot(ds))
		return (SET_ERROR(EINVAL));

	for (dsl_bookmark_node_t *dbn = avl_first(&ds->ds_bookmarks);
	    dbn != NULL; dbn = AVL_NEXT(&ds->ds_bookmarks, dbn)) {
		nvlist_t *out_props = fnvlist_alloc();

		dsl_bookmark_fetch_props(dp, &dbn->dbn_phys, props, out_props);

		fnvlist_add_nvlist(outnvl, dbn->dbn_name, out_props);
		fnvlist_free(out_props);
	}
	return (0);
}