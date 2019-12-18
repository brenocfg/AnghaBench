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
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  IOC_INPUT_TEST (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_IOC_ROLLBACK ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_rollback(const char *dataset, const char *snapshot)
{
	nvlist_t *optional = fnvlist_alloc();

	fnvlist_add_string(optional, "target", snapshot);

	IOC_INPUT_TEST(ZFS_IOC_ROLLBACK, dataset, NULL, optional, B_FALSE);

	nvlist_free(optional);
}