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
 int SET_ERROR (int) ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int param_set_int (char const*,int /*<<< orphan*/ *) ; 

int
param_set_slop_shift(const char *buf, zfs_kernel_param_t *kp)
{
	unsigned long val;
	int error;

	error = kstrtoul(buf, 0, &val);
	if (error)
		return (SET_ERROR(error));

	if (val < 1 || val > 31)
		return (SET_ERROR(-EINVAL));

	error = param_set_int(buf, kp);
	if (error < 0)
		return (SET_ERROR(error));

	return (0);
}