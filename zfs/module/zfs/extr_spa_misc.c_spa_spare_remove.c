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
struct TYPE_4__ {int /*<<< orphan*/  vdev_isspare; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_aux_remove (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_spare_avl ; 
 int /*<<< orphan*/  spa_spare_lock ; 

void
spa_spare_remove(vdev_t *vd)
{
	mutex_enter(&spa_spare_lock);
	ASSERT(vd->vdev_isspare);
	spa_aux_remove(vd, &spa_spare_avl);
	vd->vdev_isspare = B_FALSE;
	mutex_exit(&spa_spare_lock);
}