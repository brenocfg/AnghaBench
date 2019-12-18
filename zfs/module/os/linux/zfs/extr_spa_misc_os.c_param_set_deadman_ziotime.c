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
typedef  int /*<<< orphan*/  zfs_kernel_param_t ;
struct TYPE_4__ {int /*<<< orphan*/  spa_deadman_ziotime; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int param_set_ulong (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_mode_global ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_1__* spa_next (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_deadman_ziotime_ms ; 

int
param_set_deadman_ziotime(const char *val, zfs_kernel_param_t *kp)
{
	spa_t *spa = NULL;
	int error;

	error = param_set_ulong(val, kp);
	if (error < 0)
		return (SET_ERROR(error));

	if (spa_mode_global != 0) {
		mutex_enter(&spa_namespace_lock);
		while ((spa = spa_next(spa)) != NULL)
			spa->spa_deadman_ziotime =
			    MSEC2NSEC(zfs_deadman_ziotime_ms);
		mutex_exit(&spa_namespace_lock);
	}

	return (0);
}