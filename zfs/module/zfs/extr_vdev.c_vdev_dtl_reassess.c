#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int vdev_children; scalar_t__ vdev_resilver_txg; int vdev_nparity; int /*<<< orphan*/  vdev_dtl_lock; int /*<<< orphan*/ * vdev_dtl; struct TYPE_16__** vdev_child; int /*<<< orphan*/  vdev_top; TYPE_1__* vdev_ops; scalar_t__ vdev_aux; TYPE_5__* vdev_spa; } ;
typedef  TYPE_4__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_17__ {scalar_t__ spa_scrub_started; TYPE_2__* spa_dsl_pool; TYPE_4__* spa_root_vdev; } ;
typedef  TYPE_5__ spa_t ;
struct TYPE_15__ {scalar_t__ scn_errors; } ;
struct TYPE_18__ {TYPE_3__ scn_phys; } ;
typedef  TYPE_6__ dsl_scan_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
struct TYPE_14__ {TYPE_6__* dp_scan; } ;
struct TYPE_13__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t DTL_MISSING ; 
 size_t DTL_OUTAGE ; 
 size_t DTL_PARTIAL ; 
 size_t DTL_SCRUB ; 
 int DTL_TYPES ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDD_DTL ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 scalar_t__ range_tree_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_walk (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long),int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  space_reftree_add_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  space_reftree_add_seg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  space_reftree_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_reftree_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_reftree_generate_map (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_config_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 scalar_t__ vdev_dtl_should_excise (TYPE_4__*) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_4__*) ; 
 int /*<<< orphan*/  vdev_readable (TYPE_4__*) ; 
 scalar_t__ zfs_scan_ignore_errors ; 

void
vdev_dtl_reassess(vdev_t *vd, uint64_t txg, uint64_t scrub_txg, int scrub_done)
{
	spa_t *spa = vd->vdev_spa;
	avl_tree_t reftree;
	int minref;

	ASSERT(spa_config_held(spa, SCL_ALL, RW_READER) != 0);

	for (int c = 0; c < vd->vdev_children; c++)
		vdev_dtl_reassess(vd->vdev_child[c], txg,
		    scrub_txg, scrub_done);

	if (vd == spa->spa_root_vdev || !vdev_is_concrete(vd) || vd->vdev_aux)
		return;

	if (vd->vdev_ops->vdev_op_leaf) {
		dsl_scan_t *scn = spa->spa_dsl_pool->dp_scan;

		mutex_enter(&vd->vdev_dtl_lock);

		/*
		 * If requested, pretend the scan completed cleanly.
		 */
		if (zfs_scan_ignore_errors && scn)
			scn->scn_phys.scn_errors = 0;

		/*
		 * If we've completed a scan cleanly then determine
		 * if this vdev should remove any DTLs. We only want to
		 * excise regions on vdevs that were available during
		 * the entire duration of this scan.
		 */
		if (scrub_txg != 0 &&
		    (spa->spa_scrub_started ||
		    (scn != NULL && scn->scn_phys.scn_errors == 0)) &&
		    vdev_dtl_should_excise(vd)) {
			/*
			 * We completed a scrub up to scrub_txg.  If we
			 * did it without rebooting, then the scrub dtl
			 * will be valid, so excise the old region and
			 * fold in the scrub dtl.  Otherwise, leave the
			 * dtl as-is if there was an error.
			 *
			 * There's little trick here: to excise the beginning
			 * of the DTL_MISSING map, we put it into a reference
			 * tree and then add a segment with refcnt -1 that
			 * covers the range [0, scrub_txg).  This means
			 * that each txg in that range has refcnt -1 or 0.
			 * We then add DTL_SCRUB with a refcnt of 2, so that
			 * entries in the range [0, scrub_txg) will have a
			 * positive refcnt -- either 1 or 2.  We then convert
			 * the reference tree into the new DTL_MISSING map.
			 */
			space_reftree_create(&reftree);
			space_reftree_add_map(&reftree,
			    vd->vdev_dtl[DTL_MISSING], 1);
			space_reftree_add_seg(&reftree, 0, scrub_txg, -1);
			space_reftree_add_map(&reftree,
			    vd->vdev_dtl[DTL_SCRUB], 2);
			space_reftree_generate_map(&reftree,
			    vd->vdev_dtl[DTL_MISSING], 1);
			space_reftree_destroy(&reftree);
		}
		range_tree_vacate(vd->vdev_dtl[DTL_PARTIAL], NULL, NULL);
		range_tree_walk(vd->vdev_dtl[DTL_MISSING],
		    range_tree_add, vd->vdev_dtl[DTL_PARTIAL]);
		if (scrub_done)
			range_tree_vacate(vd->vdev_dtl[DTL_SCRUB], NULL, NULL);
		range_tree_vacate(vd->vdev_dtl[DTL_OUTAGE], NULL, NULL);
		if (!vdev_readable(vd))
			range_tree_add(vd->vdev_dtl[DTL_OUTAGE], 0, -1ULL);
		else
			range_tree_walk(vd->vdev_dtl[DTL_MISSING],
			    range_tree_add, vd->vdev_dtl[DTL_OUTAGE]);

		/*
		 * If the vdev was resilvering and no longer has any
		 * DTLs then reset its resilvering flag and dirty
		 * the top level so that we persist the change.
		 */
		if (txg != 0 && vd->vdev_resilver_txg != 0 &&
		    range_tree_is_empty(vd->vdev_dtl[DTL_MISSING]) &&
		    range_tree_is_empty(vd->vdev_dtl[DTL_OUTAGE])) {
			vd->vdev_resilver_txg = 0;
			vdev_config_dirty(vd->vdev_top);
		}

		mutex_exit(&vd->vdev_dtl_lock);

		if (txg != 0)
			vdev_dirty(vd->vdev_top, VDD_DTL, vd, txg);
		return;
	}

	mutex_enter(&vd->vdev_dtl_lock);
	for (int t = 0; t < DTL_TYPES; t++) {
		/* account for child's outage in parent's missing map */
		int s = (t == DTL_MISSING) ? DTL_OUTAGE: t;
		if (t == DTL_SCRUB)
			continue;			/* leaf vdevs only */
		if (t == DTL_PARTIAL)
			minref = 1;			/* i.e. non-zero */
		else if (vd->vdev_nparity != 0)
			minref = vd->vdev_nparity + 1;	/* RAID-Z */
		else
			minref = vd->vdev_children;	/* any kind of mirror */
		space_reftree_create(&reftree);
		for (int c = 0; c < vd->vdev_children; c++) {
			vdev_t *cvd = vd->vdev_child[c];
			mutex_enter(&cvd->vdev_dtl_lock);
			space_reftree_add_map(&reftree, cvd->vdev_dtl[s], 1);
			mutex_exit(&cvd->vdev_dtl_lock);
		}
		space_reftree_generate_map(&reftree, vd->vdev_dtl[t], minref);
		space_reftree_destroy(&reftree);
	}
	mutex_exit(&vd->vdev_dtl_lock);
}