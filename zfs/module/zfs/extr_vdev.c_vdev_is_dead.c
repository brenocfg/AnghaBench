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
struct TYPE_3__ {scalar_t__ vdev_state; int /*<<< orphan*/ * vdev_ops; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ VDEV_STATE_DEGRADED ; 
 int /*<<< orphan*/  vdev_hole_ops ; 
 int /*<<< orphan*/  vdev_missing_ops ; 

boolean_t
vdev_is_dead(vdev_t *vd)
{
	/*
	 * Holes and missing devices are always considered "dead".
	 * This simplifies the code since we don't have to check for
	 * these types of devices in the various code paths.
	 * Instead we rely on the fact that we skip over dead devices
	 * before issuing I/O to them.
	 */
	return (vd->vdev_state < VDEV_STATE_DEGRADED ||
	    vd->vdev_ops == &vdev_hole_ops ||
	    vd->vdev_ops == &vdev_missing_ops);
}