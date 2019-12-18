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
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_IOC_SNAPSHOT ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_snapshot(const char *pool, const char *snapshot)
{
	nvlist_t *required = fnvlist_alloc();
	nvlist_t *optional = fnvlist_alloc();
	nvlist_t *snaps = fnvlist_alloc();
	nvlist_t *props = fnvlist_alloc();

	fnvlist_add_boolean(snaps, snapshot);
	fnvlist_add_nvlist(required, "snaps", snaps);

	fnvlist_add_string(props, "org.openzfs:launch", "September 17th, 2013");
	fnvlist_add_nvlist(optional, "props", props);

	IOC_INPUT_TEST(ZFS_IOC_SNAPSHOT, pool, required, optional, 0);

	nvlist_free(props);
	nvlist_free(snaps);
	nvlist_free(optional);
	nvlist_free(required);
}