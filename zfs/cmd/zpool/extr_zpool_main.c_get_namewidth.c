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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int MAX (unsigned int,int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int max_width (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_namewidth(zpool_handle_t *zhp, int min_width, int flags, boolean_t verbose)
{
	nvlist_t *config, *nvroot;
	int width = min_width;

	if ((config = zpool_get_config(zhp, NULL)) != NULL) {
		verify(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
		    &nvroot) == 0);
		unsigned int poolname_len = strlen(zpool_get_name(zhp));
		if (verbose == B_FALSE) {
			width = MAX(poolname_len, min_width);
		} else {
			width = MAX(poolname_len,
			    max_width(zhp, nvroot, 0, min_width, flags));
		}
	}

	return (width);
}