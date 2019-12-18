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
struct TYPE_3__ {int /*<<< orphan*/ * vdev_open_thread; int /*<<< orphan*/  vdev_open_error; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/ * curthread ; 
 int /*<<< orphan*/  vdev_open (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_open_child(void *arg)
{
	vdev_t *vd = arg;

	vd->vdev_open_thread = curthread;
	vd->vdev_open_error = vdev_open(vd);
	vd->vdev_open_thread = NULL;
}