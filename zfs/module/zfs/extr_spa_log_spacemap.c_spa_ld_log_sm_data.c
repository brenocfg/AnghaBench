#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct spa_ld_log_sm_arg {int /*<<< orphan*/  slls_txg; TYPE_3__* slls_spa; } ;
typedef  int /*<<< orphan*/  space_map_t ;
struct TYPE_21__ {int sus_nblocks; int sus_memused; } ;
struct TYPE_22__ {TYPE_2__ spa_unflushed_stats; int /*<<< orphan*/  spa_metaslabs_by_flushed; int /*<<< orphan*/  spa_sm_logs_by_txg; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_23__ {int sls_nblocks; int ms_weight; int /*<<< orphan*/  ms_lock; int /*<<< orphan*/ * ms_sm; int /*<<< orphan*/  ms_unflushed_frees; TYPE_1__* ms_group; int /*<<< orphan*/  ms_unflushed_allocs; scalar_t__ ms_allocated_space; int /*<<< orphan*/  sls_mscount; int /*<<< orphan*/  sls_txg; scalar_t__ sls_sm_obj; } ;
typedef  TYPE_4__ spa_log_sm_t ;
typedef  TYPE_4__ metaslab_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  int hrtime_t ;
struct TYPE_20__ {int /*<<< orphan*/  mg_class; int /*<<< orphan*/ * mg_vd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int) ; 
 TYPE_4__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int METASLAB_ACTIVE_MASK ; 
 int /*<<< orphan*/  SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_4__* avl_first (int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int gethrtime () ; 
 scalar_t__ metaslab_debug_load ; 
 int /*<<< orphan*/  metaslab_load (TYPE_4__*) ; 
 int /*<<< orphan*/  metaslab_recalculate_weight_and_sort (TYPE_4__*) ; 
 int /*<<< orphan*/  metaslab_set_selected_txg (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_space_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ metaslab_unflushed_changes_memused (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_ld_log_sm_cb ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_log_sm_nblocks (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_meta_objset (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_3__*) ; 
 scalar_t__ space_map_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_close (int /*<<< orphan*/ *) ; 
 int space_map_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spa_ld_log_sm_arg*) ; 
 int /*<<< orphan*/  space_map_length (int /*<<< orphan*/ *) ; 
 int space_map_nblocks (int /*<<< orphan*/ *) ; 
 int space_map_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_add_data (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfs_log_sm_blksz ; 

__attribute__((used)) static int
spa_ld_log_sm_data(spa_t *spa)
{
	int error = 0;

	/*
	 * If we are not going to do any writes there is no need
	 * to read the log space maps.
	 */
	if (!spa_writeable(spa))
		return (0);

	ASSERT0(spa->spa_unflushed_stats.sus_nblocks);
	ASSERT0(spa->spa_unflushed_stats.sus_memused);

	hrtime_t read_logs_starttime = gethrtime();
	/* this is a no-op when we don't have space map logs */
	for (spa_log_sm_t *sls = avl_first(&spa->spa_sm_logs_by_txg);
	    sls; sls = AVL_NEXT(&spa->spa_sm_logs_by_txg, sls)) {
		space_map_t *sm = NULL;
		error = space_map_open(&sm, spa_meta_objset(spa),
		    sls->sls_sm_obj, 0, UINT64_MAX, SPA_MINBLOCKSHIFT);
		if (error != 0) {
			spa_load_failed(spa, "spa_ld_log_sm_data(): failed at "
			    "space_map_open(obj=%llu) [error %d]",
			    (u_longlong_t)sls->sls_sm_obj, error);
			goto out;
		}

		struct spa_ld_log_sm_arg vla = {
			.slls_spa = spa,
			.slls_txg = sls->sls_txg
		};
		error = space_map_iterate(sm, space_map_length(sm),
		    spa_ld_log_sm_cb, &vla);
		if (error != 0) {
			space_map_close(sm);
			spa_load_failed(spa, "spa_ld_log_sm_data(): failed "
			    "at space_map_iterate(obj=%llu) [error %d]",
			    (u_longlong_t)sls->sls_sm_obj, error);
			goto out;
		}

		ASSERT0(sls->sls_nblocks);
		sls->sls_nblocks = space_map_nblocks(sm);
		spa->spa_unflushed_stats.sus_nblocks += sls->sls_nblocks;
		summary_add_data(spa, sls->sls_txg,
		    sls->sls_mscount, sls->sls_nblocks);

		space_map_close(sm);
	}
	hrtime_t read_logs_endtime = gethrtime();
	spa_load_note(spa,
	    "read %llu log space maps (%llu total blocks - blksz = %llu bytes) "
	    "in %lld ms", (u_longlong_t)avl_numnodes(&spa->spa_sm_logs_by_txg),
	    (u_longlong_t)spa_log_sm_nblocks(spa),
	    (u_longlong_t)zfs_log_sm_blksz,
	    (longlong_t)((read_logs_endtime - read_logs_starttime) / 1000000));

out:
	/*
	 * Now that the metaslabs contain their unflushed changes:
	 * [1] recalculate their actual allocated space
	 * [2] recalculate their weights
	 * [3] sum up the memory usage of their unflushed range trees
	 * [4] optionally load them, if debug_load is set
	 *
	 * Note that even in the case where we get here because of an
	 * error (e.g. error != 0), we still want to update the fields
	 * below in order to have a proper teardown in spa_unload().
	 */
	for (metaslab_t *m = avl_first(&spa->spa_metaslabs_by_flushed);
	    m != NULL; m = AVL_NEXT(&spa->spa_metaslabs_by_flushed, m)) {
		mutex_enter(&m->ms_lock);
		m->ms_allocated_space = space_map_allocated(m->ms_sm) +
		    range_tree_space(m->ms_unflushed_allocs) -
		    range_tree_space(m->ms_unflushed_frees);

		vdev_t *vd = m->ms_group->mg_vd;
		metaslab_space_update(vd, m->ms_group->mg_class,
		    range_tree_space(m->ms_unflushed_allocs), 0, 0);
		metaslab_space_update(vd, m->ms_group->mg_class,
		    -range_tree_space(m->ms_unflushed_frees), 0, 0);

		ASSERT0(m->ms_weight & METASLAB_ACTIVE_MASK);
		metaslab_recalculate_weight_and_sort(m);

		spa->spa_unflushed_stats.sus_memused +=
		    metaslab_unflushed_changes_memused(m);

		if (metaslab_debug_load && m->ms_sm != NULL) {
			VERIFY0(metaslab_load(m));
			metaslab_set_selected_txg(m, 0);
		}
		mutex_exit(&m->ms_lock);
	}

	return (error);
}