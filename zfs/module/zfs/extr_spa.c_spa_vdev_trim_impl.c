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
struct TYPE_11__ {scalar_t__ vdev_trim_state; int /*<<< orphan*/  vdev_trim_lock; TYPE_2__* vdev_top; int /*<<< orphan*/ * vdev_trim_thread; int /*<<< orphan*/  vdev_has_securetrim; int /*<<< orphan*/  vdev_has_trim; TYPE_1__* vdev_ops; scalar_t__ vdev_detached; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_10__ {scalar_t__ vdev_removing; } ;
struct TYPE_9__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
#define  POOL_TRIM_CANCEL 130 
#define  POOL_TRIM_START 129 
#define  POOL_TRIM_SUSPEND 128 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDEV_TRIM_ACTIVE ; 
 scalar_t__ VDEV_TRIM_CANCELED ; 
 scalar_t__ VDEV_TRIM_SUSPENDED ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned long long) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* spa_lookup_by_guid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_trim (TYPE_3__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vdev_trim_stop (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_3__*) ; 

__attribute__((used)) static int
spa_vdev_trim_impl(spa_t *spa, uint64_t guid, uint64_t cmd_type,
    uint64_t rate, boolean_t partial, boolean_t secure, list_t *vd_list)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	spa_config_enter(spa, SCL_CONFIG | SCL_STATE, FTAG, RW_READER);

	/* Look up vdev and ensure it's a leaf. */
	vdev_t *vd = spa_lookup_by_guid(spa, guid, B_FALSE);
	if (vd == NULL || vd->vdev_detached) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		return (SET_ERROR(ENODEV));
	} else if (!vd->vdev_ops->vdev_op_leaf || !vdev_is_concrete(vd)) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		return (SET_ERROR(EINVAL));
	} else if (!vdev_writeable(vd)) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		return (SET_ERROR(EROFS));
	} else if (!vd->vdev_has_trim) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		return (SET_ERROR(EOPNOTSUPP));
	} else if (secure && !vd->vdev_has_securetrim) {
		spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);
		return (SET_ERROR(EOPNOTSUPP));
	}
	mutex_enter(&vd->vdev_trim_lock);
	spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);

	/*
	 * When we activate a TRIM action we check to see if the
	 * vdev_trim_thread is NULL. We do this instead of using the
	 * vdev_trim_state since there might be a previous TRIM process
	 * which has completed but the thread is not exited.
	 */
	if (cmd_type == POOL_TRIM_START &&
	    (vd->vdev_trim_thread != NULL || vd->vdev_top->vdev_removing)) {
		mutex_exit(&vd->vdev_trim_lock);
		return (SET_ERROR(EBUSY));
	} else if (cmd_type == POOL_TRIM_CANCEL &&
	    (vd->vdev_trim_state != VDEV_TRIM_ACTIVE &&
	    vd->vdev_trim_state != VDEV_TRIM_SUSPENDED)) {
		mutex_exit(&vd->vdev_trim_lock);
		return (SET_ERROR(ESRCH));
	} else if (cmd_type == POOL_TRIM_SUSPEND &&
	    vd->vdev_trim_state != VDEV_TRIM_ACTIVE) {
		mutex_exit(&vd->vdev_trim_lock);
		return (SET_ERROR(ESRCH));
	}

	switch (cmd_type) {
	case POOL_TRIM_START:
		vdev_trim(vd, rate, partial, secure);
		break;
	case POOL_TRIM_CANCEL:
		vdev_trim_stop(vd, VDEV_TRIM_CANCELED, vd_list);
		break;
	case POOL_TRIM_SUSPEND:
		vdev_trim_stop(vd, VDEV_TRIM_SUSPENDED, vd_list);
		break;
	default:
		panic("invalid cmd_type %llu", (unsigned long long)cmd_type);
	}
	mutex_exit(&vd->vdev_trim_lock);

	return (0);
}