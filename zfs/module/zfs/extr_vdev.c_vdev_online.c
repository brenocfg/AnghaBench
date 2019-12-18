#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ vdev_state; int vdev_checkremove; int vdev_forcefault; int vdev_expanding; scalar_t__ vdev_initialize_state; scalar_t__ vdev_trim_state; int /*<<< orphan*/  vdev_trim_lock; int /*<<< orphan*/  vdev_trim_secure; int /*<<< orphan*/  vdev_trim_partial; int /*<<< orphan*/  vdev_trim_rate; int /*<<< orphan*/ * vdev_trim_thread; int /*<<< orphan*/  vdev_initialize_lock; int /*<<< orphan*/ * vdev_initialize_thread; scalar_t__ vdev_aux; int /*<<< orphan*/  vdev_unspare; struct TYPE_18__** vdev_child; struct TYPE_18__* vdev_parent; TYPE_5__* vdev_ops; int /*<<< orphan*/  vdev_expansion_time; void* vdev_tmpoffline; void* vdev_offline; struct TYPE_18__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ vdev_state_t ;
typedef  int uint64_t ;
struct TYPE_19__ {scalar_t__ spa_autoexpand; TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int boolean_t ;
struct TYPE_20__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 void* B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ESC_ZFS_VDEV_ONLINE ; 
 int /*<<< orphan*/  SCL_NONE ; 
 int /*<<< orphan*/  SPA_ASYNC_CONFIG_UPDATE ; 
 scalar_t__ VDEV_INITIALIZE_ACTIVE ; 
 scalar_t__ VDEV_STATE_DEGRADED ; 
 scalar_t__ VDEV_TRIM_ACTIVE ; 
 int ZFS_ONLINE_CHECKREMOVE ; 
 int ZFS_ONLINE_EXPAND ; 
 int ZFS_ONLINE_FORCEFAULT ; 
 int ZFS_ONLINE_UNSPARE ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* spa_lookup_by_guid (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_vdev_state_enter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_vdev_state_exit (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_reopen (TYPE_1__*) ; 
 TYPE_5__ vdev_spare_ops ; 
 int /*<<< orphan*/  vdev_trim (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_writeable (TYPE_1__*) ; 

int
vdev_online(spa_t *spa, uint64_t guid, uint64_t flags, vdev_state_t *newstate)
{
	vdev_t *vd, *tvd, *pvd, *rvd = spa->spa_root_vdev;
	boolean_t wasoffline;
	vdev_state_t oldstate;

	spa_vdev_state_enter(spa, SCL_NONE);

	if ((vd = spa_lookup_by_guid(spa, guid, B_TRUE)) == NULL)
		return (spa_vdev_state_exit(spa, NULL, ENODEV));

	if (!vd->vdev_ops->vdev_op_leaf)
		return (spa_vdev_state_exit(spa, NULL, ENOTSUP));

	wasoffline = (vd->vdev_offline || vd->vdev_tmpoffline);
	oldstate = vd->vdev_state;

	tvd = vd->vdev_top;
	vd->vdev_offline = B_FALSE;
	vd->vdev_tmpoffline = B_FALSE;
	vd->vdev_checkremove = !!(flags & ZFS_ONLINE_CHECKREMOVE);
	vd->vdev_forcefault = !!(flags & ZFS_ONLINE_FORCEFAULT);

	/* XXX - L2ARC 1.0 does not support expansion */
	if (!vd->vdev_aux) {
		for (pvd = vd; pvd != rvd; pvd = pvd->vdev_parent)
			pvd->vdev_expanding = !!((flags & ZFS_ONLINE_EXPAND) ||
			    spa->spa_autoexpand);
		vd->vdev_expansion_time = gethrestime_sec();
	}

	vdev_reopen(tvd);
	vd->vdev_checkremove = vd->vdev_forcefault = B_FALSE;

	if (!vd->vdev_aux) {
		for (pvd = vd; pvd != rvd; pvd = pvd->vdev_parent)
			pvd->vdev_expanding = B_FALSE;
	}

	if (newstate)
		*newstate = vd->vdev_state;
	if ((flags & ZFS_ONLINE_UNSPARE) &&
	    !vdev_is_dead(vd) && vd->vdev_parent &&
	    vd->vdev_parent->vdev_ops == &vdev_spare_ops &&
	    vd->vdev_parent->vdev_child[0] == vd)
		vd->vdev_unspare = B_TRUE;

	if ((flags & ZFS_ONLINE_EXPAND) || spa->spa_autoexpand) {

		/* XXX - L2ARC 1.0 does not support expansion */
		if (vd->vdev_aux)
			return (spa_vdev_state_exit(spa, vd, ENOTSUP));
		spa_async_request(spa, SPA_ASYNC_CONFIG_UPDATE);
	}

	/* Restart initializing if necessary */
	mutex_enter(&vd->vdev_initialize_lock);
	if (vdev_writeable(vd) &&
	    vd->vdev_initialize_thread == NULL &&
	    vd->vdev_initialize_state == VDEV_INITIALIZE_ACTIVE) {
		(void) vdev_initialize(vd);
	}
	mutex_exit(&vd->vdev_initialize_lock);

	/* Restart trimming if necessary */
	mutex_enter(&vd->vdev_trim_lock);
	if (vdev_writeable(vd) &&
	    vd->vdev_trim_thread == NULL &&
	    vd->vdev_trim_state == VDEV_TRIM_ACTIVE) {
		(void) vdev_trim(vd, vd->vdev_trim_rate, vd->vdev_trim_partial,
		    vd->vdev_trim_secure);
	}
	mutex_exit(&vd->vdev_trim_lock);

	if (wasoffline ||
	    (oldstate < VDEV_STATE_DEGRADED &&
	    vd->vdev_state >= VDEV_STATE_DEGRADED))
		spa_event_notify(spa, vd, NULL, ESC_ZFS_VDEV_ONLINE);

	return (spa_vdev_state_exit(spa, vd, 0));
}