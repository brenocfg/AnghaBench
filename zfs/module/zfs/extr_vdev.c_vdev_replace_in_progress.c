#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vdev_children; struct TYPE_4__** vdev_child; int /*<<< orphan*/ * vdev_ops; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DTL_MISSING ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_dtl_empty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_replacing_ops ; 
 int /*<<< orphan*/  vdev_spare_ops ; 

boolean_t
vdev_replace_in_progress(vdev_t *vdev)
{
	ASSERT(spa_config_held(vdev->vdev_spa, SCL_ALL, RW_READER) != 0);

	if (vdev->vdev_ops == &vdev_replacing_ops)
		return (B_TRUE);

	/*
	 * A 'spare' vdev indicates that we have a replace in progress, unless
	 * it has exactly two children, and the second, the hot spare, has
	 * finished being resilvered.
	 */
	if (vdev->vdev_ops == &vdev_spare_ops && (vdev->vdev_children > 2 ||
	    !vdev_dtl_empty(vdev->vdev_child[1], DTL_MISSING)))
		return (B_TRUE);

	for (int i = 0; i < vdev->vdev_children; i++) {
		if (vdev_replace_in_progress(vdev->vdev_child[i]))
			return (B_TRUE);
	}

	return (B_FALSE);
}