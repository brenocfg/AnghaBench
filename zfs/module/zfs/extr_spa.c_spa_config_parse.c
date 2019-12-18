#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_8__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 int vdev_alloc (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  vdev_free (TYPE_2__*) ; 

int
spa_config_parse(spa_t *spa, vdev_t **vdp, nvlist_t *nv, vdev_t *parent,
    uint_t id, int atype)
{
	nvlist_t **child;
	uint_t children;
	int error;

	if ((error = vdev_alloc(spa, vdp, nv, parent, id, atype)) != 0)
		return (error);

	if ((*vdp)->vdev_ops->vdev_op_leaf)
		return (0);

	error = nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
	    &child, &children);

	if (error == ENOENT)
		return (0);

	if (error) {
		vdev_free(*vdp);
		*vdp = NULL;
		return (SET_ERROR(EINVAL));
	}

	for (int c = 0; c < children; c++) {
		vdev_t *vd;
		if ((error = spa_config_parse(spa, &vd, child[c], *vdp, c,
		    atype)) != 0) {
			vdev_free(*vdp);
			*vdp = NULL;
			return (error);
		}
	}

	ASSERT(*vdp != NULL);

	return (0);
}