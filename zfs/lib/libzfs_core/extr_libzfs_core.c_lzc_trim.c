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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ pool_trim_func_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_POOL_TRIM ; 
 int /*<<< orphan*/  ZPOOL_TRIM_COMMAND ; 
 int /*<<< orphan*/  ZPOOL_TRIM_RATE ; 
 int /*<<< orphan*/  ZPOOL_TRIM_SECURE ; 
 int /*<<< orphan*/  ZPOOL_TRIM_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int lzc_ioctl (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
lzc_trim(const char *poolname, pool_trim_func_t cmd_type, uint64_t rate,
    boolean_t secure, nvlist_t *vdevs, nvlist_t **errlist)
{
	int error;

	nvlist_t *args = fnvlist_alloc();
	fnvlist_add_uint64(args, ZPOOL_TRIM_COMMAND, (uint64_t)cmd_type);
	fnvlist_add_nvlist(args, ZPOOL_TRIM_VDEVS, vdevs);
	fnvlist_add_uint64(args, ZPOOL_TRIM_RATE, rate);
	fnvlist_add_boolean_value(args, ZPOOL_TRIM_SECURE, secure);

	error = lzc_ioctl(ZFS_IOC_POOL_TRIM, poolname, args, errlist);

	fnvlist_free(args);

	return (error);
}