#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  scalar_t__ zpool_prop_t ;
struct TYPE_4__ {int /*<<< orphan*/ * zpool_props; int /*<<< orphan*/ * zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ ZPOOL_PROP_GUID ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_SRC_DEFAULT ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zpool_get_all_props (TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_prop_default_numeric (scalar_t__) ; 
 int /*<<< orphan*/  zpool_prop_to_name (scalar_t__) ; 

uint64_t
zpool_get_prop_int(zpool_handle_t *zhp, zpool_prop_t prop, zprop_source_t *src)
{
	nvlist_t *nv, *nvl;
	uint64_t value;
	zprop_source_t source;

	if (zhp->zpool_props == NULL && zpool_get_all_props(zhp)) {
		/*
		 * zpool_get_all_props() has most likely failed because
		 * the pool is faulted, but if all we need is the top level
		 * vdev's guid then get it from the zhp config nvlist.
		 */
		if ((prop == ZPOOL_PROP_GUID) &&
		    (nvlist_lookup_nvlist(zhp->zpool_config,
		    ZPOOL_CONFIG_VDEV_TREE, &nv) == 0) &&
		    (nvlist_lookup_uint64(nv, ZPOOL_CONFIG_GUID, &value)
		    == 0)) {
			return (value);
		}
		return (zpool_prop_default_numeric(prop));
	}

	nvl = zhp->zpool_props;
	if (nvlist_lookup_nvlist(nvl, zpool_prop_to_name(prop), &nv) == 0) {
		verify(nvlist_lookup_uint64(nv, ZPROP_SOURCE, &value) == 0);
		source = value;
		verify(nvlist_lookup_uint64(nv, ZPROP_VALUE, &value) == 0);
	} else {
		source = ZPROP_SRC_DEFAULT;
		value = zpool_prop_default_numeric(prop);
	}

	if (src)
		*src = source;

	return (value);
}