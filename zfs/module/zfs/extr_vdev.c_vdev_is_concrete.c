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
struct TYPE_3__ {int /*<<< orphan*/ * vdev_ops; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_ops_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  vdev_hole_ops ; 
 int /*<<< orphan*/  vdev_indirect_ops ; 
 int /*<<< orphan*/  vdev_missing_ops ; 
 int /*<<< orphan*/  vdev_root_ops ; 

boolean_t
vdev_is_concrete(vdev_t *vd)
{
	vdev_ops_t *ops = vd->vdev_ops;
	if (ops == &vdev_indirect_ops || ops == &vdev_hole_ops ||
	    ops == &vdev_missing_ops || ops == &vdev_root_ops) {
		return (B_FALSE);
	} else {
		return (B_TRUE);
	}
}