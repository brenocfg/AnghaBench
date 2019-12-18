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
 int /*<<< orphan*/  ZFS_IOC_GET_BOOKMARKS ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_get_bookmarks(const char *dataset)
{
	nvlist_t *optional = fnvlist_alloc();

	fnvlist_add_boolean(optional, "guid");
	fnvlist_add_boolean(optional, "createtxg");
	fnvlist_add_boolean(optional, "creation");

	IOC_INPUT_TEST_WILD(ZFS_IOC_GET_BOOKMARKS, dataset, NULL, optional, 0);

	nvlist_free(optional);
}