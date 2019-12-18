#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {TYPE_6__* os_dsl_dataset; int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  nice_used ;
typedef  int /*<<< orphan*/  nice_uncomp ;
typedef  int /*<<< orphan*/  nice_comp ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_9__ {int /*<<< orphan*/  dd_livelist; } ;
typedef  TYPE_2__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_11__ {TYPE_2__* ds_dir; } ;
struct TYPE_10__ {int /*<<< orphan*/  dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_is_snapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_space_written (int /*<<< orphan*/ *,TYPE_6__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_space (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_4__* dsl_dir_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_pool_config_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * spa_get_dsl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdb_nicenum (scalar_t__,char*,int) ; 

__attribute__((used)) static int
verify_dd_livelist(objset_t *os)
{
	uint64_t ll_used, used, ll_comp, comp, ll_uncomp, uncomp;
	dsl_pool_t *dp = spa_get_dsl(os->os_spa);
	dsl_dir_t  *dd = os->os_dsl_dataset->ds_dir;

	ASSERT(!dmu_objset_is_snapshot(os));
	if (!dsl_deadlist_is_open(&dd->dd_livelist))
		return (0);
	dsl_pool_config_enter(dp, FTAG);
	dsl_deadlist_space(&dd->dd_livelist, &ll_used,
	    &ll_comp, &ll_uncomp);

	dsl_dataset_t *origin_ds;
	ASSERT(dsl_pool_config_held(dp));
	VERIFY0(dsl_dataset_hold_obj(dp,
	    dsl_dir_phys(dd)->dd_origin_obj, FTAG, &origin_ds));
	VERIFY0(dsl_dataset_space_written(origin_ds, os->os_dsl_dataset,
	    &used, &comp, &uncomp));
	dsl_dataset_rele(origin_ds, FTAG);
	dsl_pool_config_exit(dp, FTAG);
	/*
	 *  It's possible that the dataset's uncomp space is larger than the
	 *  livelist's because livelists do not track embedded block pointers
	 */
	if (used != ll_used || comp != ll_comp || uncomp < ll_uncomp) {
		char nice_used[32], nice_comp[32], nice_uncomp[32];
		(void) printf("Discrepancy in space accounting:\n");
		zdb_nicenum(used, nice_used, sizeof (nice_used));
		zdb_nicenum(comp, nice_comp, sizeof (nice_comp));
		zdb_nicenum(uncomp, nice_uncomp, sizeof (nice_uncomp));
		(void) printf("dir: used %s, comp %s, uncomp %s\n",
		    nice_used, nice_comp, nice_uncomp);
		zdb_nicenum(ll_used, nice_used, sizeof (nice_used));
		zdb_nicenum(ll_comp, nice_comp, sizeof (nice_comp));
		zdb_nicenum(ll_uncomp, nice_uncomp, sizeof (nice_uncomp));
		(void) printf("livelist: used %s, comp %s, uncomp %s\n",
		    nice_used, nice_comp, nice_uncomp);
		return (1);
	}
	return (0);
}