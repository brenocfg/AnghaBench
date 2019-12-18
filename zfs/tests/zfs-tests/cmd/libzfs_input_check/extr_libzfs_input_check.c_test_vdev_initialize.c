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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int POOL_INITIALIZE_START ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_INITIALIZE ; 
 char* ZPOOL_INITIALIZE_COMMAND ; 
 int /*<<< orphan*/  ZPOOL_INITIALIZE_VDEVS ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_vdev_initialize(const char *pool)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *vdev_guids = fnvlist_alloc();

	fnvlist_add_uint64(vdev_guids, "path", 0xdeadbeefdeadbeef);
	fnvlist_add_uint64(required, ZPOOL_INITIALIZE_COMMAND,
	    POOL_INITIALIZE_START);
	fnvlist_add_nvlist(required, ZPOOL_INITIALIZE_VDEVS, vdev_guids);

	IOC_INPUT_TEST(ZFS_IOC_POOL_INITIALIZE, pool, required, NULL, EINVAL);
	nvlist_free(vdev_guids);
	nvlist_free(required);
}