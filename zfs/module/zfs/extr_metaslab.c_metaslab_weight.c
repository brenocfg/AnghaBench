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
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_4__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  space_map_phys_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_16__ {TYPE_2__* ms_sm; int /*<<< orphan*/  ms_max_size; scalar_t__ ms_loaded; int /*<<< orphan*/  ms_lock; TYPE_3__* ms_group; } ;
typedef  TYPE_5__ metaslab_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {TYPE_4__* mg_vd; } ;
struct TYPE_13__ {TYPE_1__* sm_dbuf; } ;
struct TYPE_12__ {int db_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  metaslab_largest_allocatable (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_largest_unflushed_free (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_segment_weight (TYPE_5__*) ; 
 int /*<<< orphan*/  metaslab_set_fragmentation (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_space_weight (TYPE_5__*) ; 
 scalar_t__ spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_metaslab_segment_weight_enabled ; 

__attribute__((used)) static uint64_t
metaslab_weight(metaslab_t *msp, boolean_t nodirty)
{
	vdev_t *vd = msp->ms_group->mg_vd;
	spa_t *spa = vd->vdev_spa;
	uint64_t weight;

	ASSERT(MUTEX_HELD(&msp->ms_lock));

	metaslab_set_fragmentation(msp, nodirty);

	/*
	 * Update the maximum size. If the metaslab is loaded, this will
	 * ensure that we get an accurate maximum size if newly freed space
	 * has been added back into the free tree. If the metaslab is
	 * unloaded, we check if there's a larger free segment in the
	 * unflushed frees. This is a lower bound on the largest allocatable
	 * segment size. Coalescing of adjacent entries may reveal larger
	 * allocatable segments, but we aren't aware of those until loading
	 * the space map into a range tree.
	 */
	if (msp->ms_loaded) {
		msp->ms_max_size = metaslab_largest_allocatable(msp);
	} else {
		msp->ms_max_size = MAX(msp->ms_max_size,
		    metaslab_largest_unflushed_free(msp));
	}

	/*
	 * Segment-based weighting requires space map histogram support.
	 */
	if (zfs_metaslab_segment_weight_enabled &&
	    spa_feature_is_enabled(spa, SPA_FEATURE_SPACEMAP_HISTOGRAM) &&
	    (msp->ms_sm == NULL || msp->ms_sm->sm_dbuf->db_size ==
	    sizeof (space_map_phys_t))) {
		weight = metaslab_segment_weight(msp);
	} else {
		weight = metaslab_space_weight(msp);
	}
	return (weight);
}