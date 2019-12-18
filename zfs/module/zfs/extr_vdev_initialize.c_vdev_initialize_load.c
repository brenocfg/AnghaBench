#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vdev_leaf_zap; scalar_t__ vdev_initialize_state; scalar_t__ vdev_initialize_last_offset; TYPE_4__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 scalar_t__ VDEV_INITIALIZE_ACTIVE ; 
 scalar_t__ VDEV_INITIALIZE_SUSPENDED ; 
 int /*<<< orphan*/  VDEV_LEAF_ZAP_INITIALIZE_LAST_OFFSET ; 
 scalar_t__ spa_config_held (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_initialize_calculate_progress (TYPE_1__*) ; 
 int zap_lookup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__*) ; 

__attribute__((used)) static int
vdev_initialize_load(vdev_t *vd)
{
	int err = 0;
	ASSERT(spa_config_held(vd->vdev_spa, SCL_CONFIG, RW_READER) ||
	    spa_config_held(vd->vdev_spa, SCL_CONFIG, RW_WRITER));
	ASSERT(vd->vdev_leaf_zap != 0);

	if (vd->vdev_initialize_state == VDEV_INITIALIZE_ACTIVE ||
	    vd->vdev_initialize_state == VDEV_INITIALIZE_SUSPENDED) {
		err = zap_lookup(vd->vdev_spa->spa_meta_objset,
		    vd->vdev_leaf_zap, VDEV_LEAF_ZAP_INITIALIZE_LAST_OFFSET,
		    sizeof (vd->vdev_initialize_last_offset), 1,
		    &vd->vdev_initialize_last_offset);
		if (err == ENOENT) {
			vd->vdev_initialize_last_offset = 0;
			err = 0;
		}
	}

	vdev_initialize_calculate_progress(vd);
	return (err);
}