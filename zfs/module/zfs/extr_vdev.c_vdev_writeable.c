#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  vdev_cant_write; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ vdev_is_concrete (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_is_dead (TYPE_1__*) ; 

boolean_t
vdev_writeable(vdev_t *vd)
{
	return (!vdev_is_dead(vd) && !vd->vdev_cant_write &&
	    vdev_is_concrete(vd));
}