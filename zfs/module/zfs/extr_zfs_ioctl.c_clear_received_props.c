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
typedef  int zprop_source_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ZPROP_SRC_NONE ; 
 int ZPROP_SRC_RECEIVED ; 
 scalar_t__ dsl_prop_get_hasrecvd (char const*) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  props_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int zfs_set_prop_nvlist (char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
clear_received_props(const char *dsname, nvlist_t *props,
    nvlist_t *skipped)
{
	int err = 0;
	nvlist_t *cleared_props = NULL;
	props_skip(props, skipped, &cleared_props);
	if (!nvlist_empty(cleared_props)) {
		/*
		 * Acts on local properties until the dataset has received
		 * properties at least once on or after SPA_VERSION_RECVD_PROPS.
		 */
		zprop_source_t flags = (ZPROP_SRC_NONE |
		    (dsl_prop_get_hasrecvd(dsname) ? ZPROP_SRC_RECEIVED : 0));
		err = zfs_set_prop_nvlist(dsname, flags, cleared_props, NULL);
	}
	nvlist_free(cleared_props);
	return (err);
}