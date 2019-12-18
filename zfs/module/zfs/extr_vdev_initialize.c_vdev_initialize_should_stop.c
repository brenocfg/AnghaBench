#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* vdev_top; scalar_t__ vdev_detached; scalar_t__ vdev_initialize_exit_wanted; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int boolean_t ;
struct TYPE_5__ {scalar_t__ vdev_removing; } ;

/* Variables and functions */
 int /*<<< orphan*/  vdev_writeable (TYPE_2__*) ; 

__attribute__((used)) static boolean_t
vdev_initialize_should_stop(vdev_t *vd)
{
	return (vd->vdev_initialize_exit_wanted || !vdev_writeable(vd) ||
	    vd->vdev_detached || vd->vdev_top->vdev_removing);
}