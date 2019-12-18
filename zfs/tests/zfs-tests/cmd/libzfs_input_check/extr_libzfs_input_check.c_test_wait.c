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
 int /*<<< orphan*/  ZFS_IOC_WAIT ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_wait(const char *pool)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();

	fnvlist_add_int32(required, "wait_activity", 2);
	fnvlist_add_uint64(optional, "wait_tag", 0xdeadbeefdeadbeef);

	IOC_INPUT_TEST(ZFS_IOC_WAIT, pool, required, optional, EINVAL);

	nvlist_free(required);
	nvlist_free(optional);
}