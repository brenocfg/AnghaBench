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
struct TYPE_11__ {scalar_t__ vdev_initialize_state; int /*<<< orphan*/  vdev_initialize_lock; TYPE_2__* vdev_top; int /*<<< orphan*/ * vdev_initialize_thread; TYPE_1__* vdev_ops; scalar_t__ vdev_detached; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_10__ {scalar_t__ vdev_removing; } ;
struct TYPE_9__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
#define  POOL_INITIALIZE_CANCEL 130 
#define  POOL_INITIALIZE_START 129 
#define  POOL_INITIALIZE_SUSPEND 128 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ VDEV_INITIALIZE_ACTIVE ; 
 scalar_t__ VDEV_INITIALIZE_CANCELED ; 
 scalar_t__ VDEV_INITIALIZE_SUSPENDED ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned long long) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* spa_lookup_by_guid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  vdev_initialize (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_initialize_stop (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_3__*) ; 

__attribute__((used)) static int
spa_vdev_initialize_impl(spa_t *spa, uint64_t guid, uint64_t cmd_type,
    list_t *vd_list)
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
	}
	mutex_enter(&vd->vdev_initialize_lock);
	spa_config_exit(spa, SCL_CONFIG | SCL_STATE, FTAG);

	/*
	 * When we activate an initialize action we check to see
	 * if the vdev_initialize_thread is NULL. We do this instead
	 * of using the vdev_initialize_state since there might be
	 * a previous initialization process which has completed but
	 * the thread is not exited.
	 */
	if (cmd_type == POOL_INITIALIZE_START &&
	    (vd->vdev_initialize_thread != NULL ||
	    vd->vdev_top->vdev_removing)) {
		mutex_exit(&vd->vdev_initialize_lock);
		return (SET_ERROR(EBUSY));
	} else if (cmd_type == POOL_INITIALIZE_CANCEL &&
	    (vd->vdev_initialize_state != VDEV_INITIALIZE_ACTIVE &&
	    vd->vdev_initialize_state != VDEV_INITIALIZE_SUSPENDED)) {
		mutex_exit(&vd->vdev_initialize_lock);
		return (SET_ERROR(ESRCH));
	} else if (cmd_type == POOL_INITIALIZE_SUSPEND &&
	    vd->vdev_initialize_state != VDEV_INITIALIZE_ACTIVE) {
		mutex_exit(&vd->vdev_initialize_lock);
		return (SET_ERROR(ESRCH));
	}

	switch (cmd_type) {
	case POOL_INITIALIZE_START:
		vdev_initialize(vd);
		break;
	case POOL_INITIALIZE_CANCEL:
		vdev_initialize_stop(vd, VDEV_INITIALIZE_CANCELED, vd_list);
		break;
	case POOL_INITIALIZE_SUSPEND:
		vdev_initialize_stop(vd, VDEV_INITIALIZE_SUSPENDED, vd_list);
		break;
	default:
		panic("invalid cmd_type %llu", (unsigned long long)cmd_type);
	}
	mutex_exit(&vd->vdev_initialize_lock);

	return (0);
}