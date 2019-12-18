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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_POOL_REOPEN ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

int
lzc_reopen(const char *pool_name, boolean_t scrub_restart)
{
	nvlist_t *args = fnvlist_alloc();
	int error;

	fnvlist_add_boolean_value(args, "scrub_restart", scrub_restart);

	error = lzc_ioctl(ZFS_IOC_POOL_REOPEN, pool_name, args, NULL);
	nvlist_free(args);
	return (error);
}