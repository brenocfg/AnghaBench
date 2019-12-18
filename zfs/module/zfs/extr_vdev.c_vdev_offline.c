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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  spa_vdev_top_lock; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int vdev_offline_locked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
vdev_offline(spa_t *spa, uint64_t guid, uint64_t flags)
{
	int error;

	mutex_enter(&spa->spa_vdev_top_lock);
	error = vdev_offline_locked(spa, guid, flags);
	mutex_exit(&spa->spa_vdev_top_lock);

	return (error);
}