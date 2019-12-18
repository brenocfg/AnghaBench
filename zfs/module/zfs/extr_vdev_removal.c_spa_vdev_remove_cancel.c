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
struct TYPE_5__ {int /*<<< orphan*/ * spa_vdev_removal; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int ENOTACTIVE ; 
 int spa_vdev_remove_cancel_impl (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_vdev_remove_suspend (TYPE_1__*) ; 

int
spa_vdev_remove_cancel(spa_t *spa)
{
	spa_vdev_remove_suspend(spa);

	if (spa->spa_vdev_removal == NULL)
		return (ENOTACTIVE);

	return (spa_vdev_remove_cancel_impl(spa));
}