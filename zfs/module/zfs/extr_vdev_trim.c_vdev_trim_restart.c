#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ vdev_leaf_zap; size_t vdev_trim_state; size_t vdev_children; struct TYPE_9__** vdev_child; int /*<<< orphan*/  vdev_trim_lock; int /*<<< orphan*/  vdev_trim_secure; int /*<<< orphan*/  vdev_trim_partial; int /*<<< orphan*/  vdev_trim_rate; int /*<<< orphan*/ * vdev_trim_thread; TYPE_1__* vdev_top; scalar_t__ vdev_offline; scalar_t__ vdev_trim_action_time; TYPE_7__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  trim_state ;
typedef  int /*<<< orphan*/  timestamp ;
typedef  scalar_t__ time_t ;
struct TYPE_10__ {int /*<<< orphan*/  spa_meta_objset; } ;
struct TYPE_8__ {int /*<<< orphan*/  vdev_removing; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_LEAF_ZAP_TRIM_ACTION_TIME ; 
 int /*<<< orphan*/  VDEV_LEAF_ZAP_TRIM_STATE ; 
 size_t VDEV_TRIM_ACTIVE ; 
 size_t VDEV_TRIM_NONE ; 
 size_t VDEV_TRIM_SUSPENDED ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  vdev_trim (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_trim_load (TYPE_2__*) ; 
 scalar_t__ vdev_writeable (TYPE_2__*) ; 
 int zap_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,size_t*) ; 

void
vdev_trim_restart(vdev_t *vd)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(!spa_config_held(vd->vdev_spa, SCL_ALL, RW_WRITER));

	if (vd->vdev_leaf_zap != 0) {
		mutex_enter(&vd->vdev_trim_lock);
		uint64_t trim_state = VDEV_TRIM_NONE;
		int err = zap_lookup(vd->vdev_spa->spa_meta_objset,
		    vd->vdev_leaf_zap, VDEV_LEAF_ZAP_TRIM_STATE,
		    sizeof (trim_state), 1, &trim_state);
		ASSERT(err == 0 || err == ENOENT);
		vd->vdev_trim_state = trim_state;

		uint64_t timestamp = 0;
		err = zap_lookup(vd->vdev_spa->spa_meta_objset,
		    vd->vdev_leaf_zap, VDEV_LEAF_ZAP_TRIM_ACTION_TIME,
		    sizeof (timestamp), 1, &timestamp);
		ASSERT(err == 0 || err == ENOENT);
		vd->vdev_trim_action_time = (time_t)timestamp;

		if (vd->vdev_trim_state == VDEV_TRIM_SUSPENDED ||
		    vd->vdev_offline) {
			/* load progress for reporting, but don't resume */
			VERIFY0(vdev_trim_load(vd));
		} else if (vd->vdev_trim_state == VDEV_TRIM_ACTIVE &&
		    vdev_writeable(vd) && !vd->vdev_top->vdev_removing &&
		    vd->vdev_trim_thread == NULL) {
			VERIFY0(vdev_trim_load(vd));
			vdev_trim(vd, vd->vdev_trim_rate,
			    vd->vdev_trim_partial, vd->vdev_trim_secure);
		}

		mutex_exit(&vd->vdev_trim_lock);
	}

	for (uint64_t i = 0; i < vd->vdev_children; i++) {
		vdev_trim_restart(vd->vdev_child[i]);
	}
}