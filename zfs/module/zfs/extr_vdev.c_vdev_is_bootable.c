#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_children; struct TYPE_5__** vdev_child; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {char* vdev_op_type; int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VDEV_TYPE_INDIRECT ; 
 int /*<<< orphan*/  VDEV_TYPE_MISSING ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

boolean_t
vdev_is_bootable(vdev_t *vd)
{
	if (!vd->vdev_ops->vdev_op_leaf) {
		const char *vdev_type = vd->vdev_ops->vdev_op_type;

		if (strcmp(vdev_type, VDEV_TYPE_MISSING) == 0 ||
		    strcmp(vdev_type, VDEV_TYPE_INDIRECT) == 0) {
			return (B_FALSE);
		}
	}

	for (int c = 0; c < vd->vdev_children; c++) {
		if (!vdev_is_bootable(vd->vdev_child[c]))
			return (B_FALSE);
	}
	return (B_TRUE);
}