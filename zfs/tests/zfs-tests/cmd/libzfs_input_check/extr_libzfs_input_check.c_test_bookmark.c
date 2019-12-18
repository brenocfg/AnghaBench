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
 int /*<<< orphan*/  IOC_INPUT_TEST_WILD (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_IOC_BOOKMARK ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_bookmark(const char *pool, const char *snapshot, const char *bookmark)
{
	nvlist_t *required = fnvlist_alloc();

	fnvlist_add_string(required, bookmark, snapshot);

	IOC_INPUT_TEST_WILD(ZFS_IOC_BOOKMARK, pool, required, NULL, 0);

	nvlist_free(required);
}