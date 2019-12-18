#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* zc_obj; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  vdev_state_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 void* VDEV_AUX_ERR_EXCEEDED ; 
 void* VDEV_AUX_EXTERNAL ; 
 void* VDEV_AUX_EXTERNAL_PERSIST ; 
#define  VDEV_STATE_DEGRADED 131 
#define  VDEV_STATE_FAULTED 130 
#define  VDEV_STATE_OFFLINE 129 
#define  VDEV_STATE_ONLINE 128 
 int /*<<< orphan*/  VDEV_STATE_UNKNOWN ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int vdev_degrade (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int vdev_fault (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int vdev_offline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int vdev_online (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_vdev_set_state(zfs_cmd_t *zc)
{
	spa_t *spa;
	int error;
	vdev_state_t newstate = VDEV_STATE_UNKNOWN;

	if ((error = spa_open(zc->zc_name, &spa, FTAG)) != 0)
		return (error);
	switch (zc->zc_cookie) {
	case VDEV_STATE_ONLINE:
		error = vdev_online(spa, zc->zc_guid, zc->zc_obj, &newstate);
		break;

	case VDEV_STATE_OFFLINE:
		error = vdev_offline(spa, zc->zc_guid, zc->zc_obj);
		break;

	case VDEV_STATE_FAULTED:
		if (zc->zc_obj != VDEV_AUX_ERR_EXCEEDED &&
		    zc->zc_obj != VDEV_AUX_EXTERNAL &&
		    zc->zc_obj != VDEV_AUX_EXTERNAL_PERSIST)
			zc->zc_obj = VDEV_AUX_ERR_EXCEEDED;

		error = vdev_fault(spa, zc->zc_guid, zc->zc_obj);
		break;

	case VDEV_STATE_DEGRADED:
		if (zc->zc_obj != VDEV_AUX_ERR_EXCEEDED &&
		    zc->zc_obj != VDEV_AUX_EXTERNAL)
			zc->zc_obj = VDEV_AUX_ERR_EXCEEDED;

		error = vdev_degrade(spa, zc->zc_guid, zc->zc_obj);
		break;

	default:
		error = SET_ERROR(EINVAL);
	}
	zc->zc_cookie = newstate;
	spa_close(spa, FTAG);
	return (error);
}