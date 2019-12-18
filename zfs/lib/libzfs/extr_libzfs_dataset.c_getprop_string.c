#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zfs_prop_t ;
struct TYPE_3__ {scalar_t__* zfs_props_table; int /*<<< orphan*/  zfs_props; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  verify (int) ; 
 char* zfs_prop_default_string (size_t) ; 
 int /*<<< orphan*/  zfs_prop_to_name (size_t) ; 

__attribute__((used)) static const char *
getprop_string(zfs_handle_t *zhp, zfs_prop_t prop, char **source)
{
	nvlist_t *nv;
	const char *value;

	*source = NULL;
	if (nvlist_lookup_nvlist(zhp->zfs_props,
	    zfs_prop_to_name(prop), &nv) == 0) {
		value = fnvlist_lookup_string(nv, ZPROP_VALUE);
		(void) nvlist_lookup_string(nv, ZPROP_SOURCE, source);
	} else {
		verify(!zhp->zfs_props_table ||
		    zhp->zfs_props_table[prop] == B_TRUE);
		value = zfs_prop_default_string(prop);
		*source = "";
	}

	return (value);
}