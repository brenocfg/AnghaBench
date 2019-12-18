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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  spa_vdev_top_lock; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_vdev_config_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_autotrim_stop_all (TYPE_1__*) ; 

uint64_t
spa_vdev_enter(spa_t *spa)
{
	mutex_enter(&spa->spa_vdev_top_lock);
	mutex_enter(&spa_namespace_lock);

	vdev_autotrim_stop_all(spa);

	return (spa_vdev_config_enter(spa));
}