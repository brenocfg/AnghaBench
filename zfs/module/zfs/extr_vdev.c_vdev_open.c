#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ vs_aux; } ;
struct TYPE_24__ {scalar_t__ vdev_open_thread; scalar_t__ vdev_state; scalar_t__ vdev_min_asize; scalar_t__ vdev_children; scalar_t__ vdev_label_aux; scalar_t__ vdev_psize; scalar_t__ vdev_asize; scalar_t__ vdev_ashift; scalar_t__ vdev_alloc_bias; scalar_t__ vdev_islog; TYPE_15__* vdev_ops; int /*<<< orphan*/ * vdev_aux; struct TYPE_24__* vdev_top; scalar_t__ vdev_expanding; scalar_t__ vdev_max_asize; int /*<<< orphan*/  vdev_copy_uberblocks; int /*<<< orphan*/ * vdev_parent; TYPE_1__** vdev_child; scalar_t__ vdev_ishole; scalar_t__ vdev_degraded; scalar_t__ vdev_faulted; void* vdev_removed; TYPE_2__ vdev_stat; void* vdev_reopening; scalar_t__ vdev_offline; void* vdev_cant_write; void* vdev_cant_read; TYPE_4__* vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_label_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_25__ {scalar_t__ spa_max_ashift; scalar_t__ spa_min_ashift; int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_scrub_reopen; scalar_t__ spa_autoexpand; } ;
typedef  TYPE_4__ spa_t ;
struct TYPE_22__ {scalar_t__ vdev_state; } ;
struct TYPE_21__ {int (* vdev_op_open ) (TYPE_3__*,scalar_t__*,scalar_t__*,scalar_t__*) ;scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 scalar_t__ ASHIFT_MAX ; 
 scalar_t__ ASHIFT_MIN ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EDOM ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_DEVICE_BAD_ASHIFT ; 
 scalar_t__ P2ALIGN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_STATE_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_ASYNC_RESILVER ; 
 int /*<<< orphan*/  SPA_FEATURE_RESILVER_DEFER ; 
 scalar_t__ SPA_MINDEVSIZE ; 
 scalar_t__ VDEV_AUX_BAD_ASHIFT ; 
 scalar_t__ VDEV_AUX_BAD_LABEL ; 
 scalar_t__ VDEV_AUX_CHILDREN_OFFLINE ; 
 scalar_t__ VDEV_AUX_ERR_EXCEEDED ; 
 scalar_t__ VDEV_AUX_EXTERNAL ; 
 scalar_t__ VDEV_AUX_NONE ; 
 scalar_t__ VDEV_AUX_OPEN_FAILED ; 
 scalar_t__ VDEV_AUX_TOO_SMALL ; 
 scalar_t__ VDEV_BIAS_NONE ; 
 scalar_t__ VDEV_LABEL_END_SIZE ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 scalar_t__ VDEV_STATE_CANT_OPEN ; 
 scalar_t__ VDEV_STATE_CLOSED ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 scalar_t__ VDEV_STATE_FAULTED ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 scalar_t__ VDEV_STATE_OFFLINE ; 
 scalar_t__ curthread ; 
 scalar_t__ dsl_scan_resilvering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_config_held (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_feature_is_enabled (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ vdev_get_min_asize (TYPE_3__*) ; 
 TYPE_15__ vdev_missing_ops ; 
 int /*<<< orphan*/  vdev_probe (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_resilver_needed (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_set_deferred_resilver (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_set_min_asize (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_set_state (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zfs_ereport_post (int /*<<< orphan*/ ,TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zio_handle_device_injection (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_injection_enabled ; 
 int zio_wait (int /*<<< orphan*/ ) ; 

int
vdev_open(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;
	int error;
	uint64_t osize = 0;
	uint64_t max_osize = 0;
	uint64_t asize, max_asize, psize;
	uint64_t ashift = 0;

	ASSERT(vd->vdev_open_thread == curthread ||
	    spa_config_held(spa, SCL_STATE_ALL, RW_WRITER) == SCL_STATE_ALL);
	ASSERT(vd->vdev_state == VDEV_STATE_CLOSED ||
	    vd->vdev_state == VDEV_STATE_CANT_OPEN ||
	    vd->vdev_state == VDEV_STATE_OFFLINE);

	vd->vdev_stat.vs_aux = VDEV_AUX_NONE;
	vd->vdev_cant_read = B_FALSE;
	vd->vdev_cant_write = B_FALSE;
	vd->vdev_min_asize = vdev_get_min_asize(vd);

	/*
	 * If this vdev is not removed, check its fault status.  If it's
	 * faulted, bail out of the open.
	 */
	if (!vd->vdev_removed && vd->vdev_faulted) {
		ASSERT(vd->vdev_children == 0);
		ASSERT(vd->vdev_label_aux == VDEV_AUX_ERR_EXCEEDED ||
		    vd->vdev_label_aux == VDEV_AUX_EXTERNAL);
		vdev_set_state(vd, B_TRUE, VDEV_STATE_FAULTED,
		    vd->vdev_label_aux);
		return (SET_ERROR(ENXIO));
	} else if (vd->vdev_offline) {
		ASSERT(vd->vdev_children == 0);
		vdev_set_state(vd, B_TRUE, VDEV_STATE_OFFLINE, VDEV_AUX_NONE);
		return (SET_ERROR(ENXIO));
	}

	error = vd->vdev_ops->vdev_op_open(vd, &osize, &max_osize, &ashift);

	/*
	 * Physical volume size should never be larger than its max size, unless
	 * the disk has shrunk while we were reading it or the device is buggy
	 * or damaged: either way it's not safe for use, bail out of the open.
	 */
	if (osize > max_osize) {
		vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
		    VDEV_AUX_OPEN_FAILED);
		return (SET_ERROR(ENXIO));
	}

	/*
	 * Reset the vdev_reopening flag so that we actually close
	 * the vdev on error.
	 */
	vd->vdev_reopening = B_FALSE;
	if (zio_injection_enabled && error == 0)
		error = zio_handle_device_injection(vd, NULL, ENXIO);

	if (error) {
		if (vd->vdev_removed &&
		    vd->vdev_stat.vs_aux != VDEV_AUX_OPEN_FAILED)
			vd->vdev_removed = B_FALSE;

		if (vd->vdev_stat.vs_aux == VDEV_AUX_CHILDREN_OFFLINE) {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_OFFLINE,
			    vd->vdev_stat.vs_aux);
		} else {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
			    vd->vdev_stat.vs_aux);
		}
		return (error);
	}

	vd->vdev_removed = B_FALSE;

	/*
	 * Recheck the faulted flag now that we have confirmed that
	 * the vdev is accessible.  If we're faulted, bail.
	 */
	if (vd->vdev_faulted) {
		ASSERT(vd->vdev_children == 0);
		ASSERT(vd->vdev_label_aux == VDEV_AUX_ERR_EXCEEDED ||
		    vd->vdev_label_aux == VDEV_AUX_EXTERNAL);
		vdev_set_state(vd, B_TRUE, VDEV_STATE_FAULTED,
		    vd->vdev_label_aux);
		return (SET_ERROR(ENXIO));
	}

	if (vd->vdev_degraded) {
		ASSERT(vd->vdev_children == 0);
		vdev_set_state(vd, B_TRUE, VDEV_STATE_DEGRADED,
		    VDEV_AUX_ERR_EXCEEDED);
	} else {
		vdev_set_state(vd, B_TRUE, VDEV_STATE_HEALTHY, 0);
	}

	/*
	 * For hole or missing vdevs we just return success.
	 */
	if (vd->vdev_ishole || vd->vdev_ops == &vdev_missing_ops)
		return (0);

	for (int c = 0; c < vd->vdev_children; c++) {
		if (vd->vdev_child[c]->vdev_state != VDEV_STATE_HEALTHY) {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_DEGRADED,
			    VDEV_AUX_NONE);
			break;
		}
	}

	osize = P2ALIGN(osize, (uint64_t)sizeof (vdev_label_t));
	max_osize = P2ALIGN(max_osize, (uint64_t)sizeof (vdev_label_t));

	if (vd->vdev_children == 0) {
		if (osize < SPA_MINDEVSIZE) {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
			    VDEV_AUX_TOO_SMALL);
			return (SET_ERROR(EOVERFLOW));
		}
		psize = osize;
		asize = osize - (VDEV_LABEL_START_SIZE + VDEV_LABEL_END_SIZE);
		max_asize = max_osize - (VDEV_LABEL_START_SIZE +
		    VDEV_LABEL_END_SIZE);
	} else {
		if (vd->vdev_parent != NULL && osize < SPA_MINDEVSIZE -
		    (VDEV_LABEL_START_SIZE + VDEV_LABEL_END_SIZE)) {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
			    VDEV_AUX_TOO_SMALL);
			return (SET_ERROR(EOVERFLOW));
		}
		psize = 0;
		asize = osize;
		max_asize = max_osize;
	}

	/*
	 * If the vdev was expanded, record this so that we can re-create the
	 * uberblock rings in labels {2,3}, during the next sync.
	 */
	if ((psize > vd->vdev_psize) && (vd->vdev_psize != 0))
		vd->vdev_copy_uberblocks = B_TRUE;

	vd->vdev_psize = psize;

	/*
	 * Make sure the allocatable size hasn't shrunk too much.
	 */
	if (asize < vd->vdev_min_asize) {
		vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
		    VDEV_AUX_BAD_LABEL);
		return (SET_ERROR(EINVAL));
	}

	if (vd->vdev_asize == 0) {
		/*
		 * This is the first-ever open, so use the computed values.
		 * For compatibility, a different ashift can be requested.
		 */
		vd->vdev_asize = asize;
		vd->vdev_max_asize = max_asize;
		if (vd->vdev_ashift == 0) {
			vd->vdev_ashift = ashift; /* use detected value */
		}
		if (vd->vdev_ashift != 0 && (vd->vdev_ashift < ASHIFT_MIN ||
		    vd->vdev_ashift > ASHIFT_MAX)) {
			vdev_set_state(vd, B_TRUE, VDEV_STATE_CANT_OPEN,
			    VDEV_AUX_BAD_ASHIFT);
			return (SET_ERROR(EDOM));
		}
	} else {
		/*
		 * Detect if the alignment requirement has increased.
		 * We don't want to make the pool unavailable, just
		 * post an event instead.
		 */
		if (ashift > vd->vdev_top->vdev_ashift &&
		    vd->vdev_ops->vdev_op_leaf) {
			zfs_ereport_post(FM_EREPORT_ZFS_DEVICE_BAD_ASHIFT,
			    spa, vd, NULL, NULL, 0, 0);
		}

		vd->vdev_max_asize = max_asize;
	}

	/*
	 * If all children are healthy we update asize if either:
	 * The asize has increased, due to a device expansion caused by dynamic
	 * LUN growth or vdev replacement, and automatic expansion is enabled;
	 * making the additional space available.
	 *
	 * The asize has decreased, due to a device shrink usually caused by a
	 * vdev replace with a smaller device. This ensures that calculations
	 * based of max_asize and asize e.g. esize are always valid. It's safe
	 * to do this as we've already validated that asize is greater than
	 * vdev_min_asize.
	 */
	if (vd->vdev_state == VDEV_STATE_HEALTHY &&
	    ((asize > vd->vdev_asize &&
	    (vd->vdev_expanding || spa->spa_autoexpand)) ||
	    (asize < vd->vdev_asize)))
		vd->vdev_asize = asize;

	vdev_set_min_asize(vd);

	/*
	 * Ensure we can issue some IO before declaring the
	 * vdev open for business.
	 */
	if (vd->vdev_ops->vdev_op_leaf &&
	    (error = zio_wait(vdev_probe(vd, NULL))) != 0) {
		vdev_set_state(vd, B_TRUE, VDEV_STATE_FAULTED,
		    VDEV_AUX_ERR_EXCEEDED);
		return (error);
	}

	/*
	 * Track the min and max ashift values for normal data devices.
	 */
	if (vd->vdev_top == vd && vd->vdev_ashift != 0 &&
	    vd->vdev_alloc_bias == VDEV_BIAS_NONE &&
	    vd->vdev_islog == 0 && vd->vdev_aux == NULL) {
		if (vd->vdev_ashift > spa->spa_max_ashift)
			spa->spa_max_ashift = vd->vdev_ashift;
		if (vd->vdev_ashift < spa->spa_min_ashift)
			spa->spa_min_ashift = vd->vdev_ashift;
	}

	/*
	 * If a leaf vdev has a DTL, and seems healthy, then kick off a
	 * resilver.  But don't do this if we are doing a reopen for a scrub,
	 * since this would just restart the scrub we are already doing.
	 */
	if (vd->vdev_ops->vdev_op_leaf && !spa->spa_scrub_reopen &&
	    vdev_resilver_needed(vd, NULL, NULL)) {
		if (dsl_scan_resilvering(spa->spa_dsl_pool) &&
		    spa_feature_is_enabled(spa, SPA_FEATURE_RESILVER_DEFER))
			vdev_set_deferred_resilver(spa, vd);
		else
			spa_async_request(spa, SPA_ASYNC_RESILVER);
	}

	return (0);
}