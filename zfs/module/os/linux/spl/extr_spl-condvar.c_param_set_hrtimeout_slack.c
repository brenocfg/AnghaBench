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
 int EINVAL ; 
 unsigned long MAX_HRTIMEOUT_SLACK_US ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int param_set_uint (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
param_set_hrtimeout_slack(const char *buf, zfs_kernel_param_t *kp)
{
	unsigned long val;
	int error;

	error = kstrtoul(buf, 0, &val);
	if (error)
		return (error);

	if (val > MAX_HRTIMEOUT_SLACK_US)
		return (-EINVAL);

	error = param_set_uint(buf, kp);
	if (error < 0)
		return (error);

	return (0);
}