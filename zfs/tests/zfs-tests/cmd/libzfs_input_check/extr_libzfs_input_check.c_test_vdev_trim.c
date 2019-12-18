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

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long long POOL_TRIM_START ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_TRIM ; 
 char* ZPOOL_TRIM_COMMAND ; 
 char* ZPOOL_TRIM_RATE ; 
 int /*<<< orphan*/  ZPOOL_TRIM_SECURE ; 
 int /*<<< orphan*/  ZPOOL_TRIM_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_boolean_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_vdev_trim(const char *pool)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();
	nvlist_t *vdev_guids = fnvlist_alloc();

	fnvlist_add_uint64(vdev_guids, "path", 0xdeadbeefdeadbeef);
	fnvlist_add_uint64(required, ZPOOL_TRIM_COMMAND, POOL_TRIM_START);
	fnvlist_add_nvlist(required, ZPOOL_TRIM_VDEVS, vdev_guids);
	fnvlist_add_uint64(optional, ZPOOL_TRIM_RATE, 1ULL << 30);
	fnvlist_add_boolean_value(optional, ZPOOL_TRIM_SECURE, B_TRUE);

	IOC_INPUT_TEST(ZFS_IOC_POOL_TRIM, pool, required, optional, EINVAL);
	nvlist_free(vdev_guids);
	nvlist_free(optional);
	nvlist_free(required);
}