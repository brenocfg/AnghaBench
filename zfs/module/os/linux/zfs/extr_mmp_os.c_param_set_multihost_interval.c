#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_kernel_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  mmp_signal_all_threads () ; 
 int param_set_ulong (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ spa_mode_global ; 

__attribute__((used)) static int
param_set_multihost_interval(const char *val, zfs_kernel_param_t *kp)
{
	int ret;

	ret = param_set_ulong(val, kp);
	if (ret < 0)
		return (ret);

	if (spa_mode_global != 0)
		mmp_signal_all_threads();

	return (ret);
}