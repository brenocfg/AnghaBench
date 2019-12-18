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
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_4__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_props; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ PROP_TYPE_STRING ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZFS_PROP_QUOTA ; 
 scalar_t__ ZFS_PROP_REFQUOTA ; 
 scalar_t__ ZFS_PROP_REFRESERVATION ; 
 scalar_t__ ZFS_PROP_RESERVATION ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_SOURCE ; 
 int /*<<< orphan*/  ZPROP_SOURCE_VAL_RECVD ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zfs_get_recvd_props (TYPE_1__*) ; 
 scalar_t__ zfs_name_to_prop (char*) ; 
 scalar_t__ zfs_prop_get_type (scalar_t__) ; 
 scalar_t__ zfs_prop_readonly (scalar_t__) ; 
 scalar_t__ zfs_prop_user (char*) ; 

__attribute__((used)) static void
send_iterate_prop(zfs_handle_t *zhp, boolean_t received_only, nvlist_t *nv)
{
	nvlist_t *props = NULL;
	nvpair_t *elem = NULL;

	if (received_only)
		props = zfs_get_recvd_props(zhp);
	else
		props = zhp->zfs_props;

	while ((elem = nvlist_next_nvpair(props, elem)) != NULL) {
		char *propname = nvpair_name(elem);
		zfs_prop_t prop = zfs_name_to_prop(propname);
		nvlist_t *propnv;

		if (!zfs_prop_user(propname)) {
			/*
			 * Realistically, this should never happen.  However,
			 * we want the ability to add DSL properties without
			 * needing to make incompatible version changes.  We
			 * need to ignore unknown properties to allow older
			 * software to still send datasets containing these
			 * properties, with the unknown properties elided.
			 */
			if (prop == ZPROP_INVAL)
				continue;

			if (zfs_prop_readonly(prop))
				continue;
		}

		verify(nvpair_value_nvlist(elem, &propnv) == 0);
		if (prop == ZFS_PROP_QUOTA || prop == ZFS_PROP_RESERVATION ||
		    prop == ZFS_PROP_REFQUOTA ||
		    prop == ZFS_PROP_REFRESERVATION) {
			char *source;
			uint64_t value;
			verify(nvlist_lookup_uint64(propnv,
			    ZPROP_VALUE, &value) == 0);
			if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT)
				continue;
			/*
			 * May have no source before SPA_VERSION_RECVD_PROPS,
			 * but is still modifiable.
			 */
			if (nvlist_lookup_string(propnv,
			    ZPROP_SOURCE, &source) == 0) {
				if ((strcmp(source, zhp->zfs_name) != 0) &&
				    (strcmp(source,
				    ZPROP_SOURCE_VAL_RECVD) != 0))
					continue;
			}
		} else {
			char *source;
			if (nvlist_lookup_string(propnv,
			    ZPROP_SOURCE, &source) != 0)
				continue;
			if ((strcmp(source, zhp->zfs_name) != 0) &&
			    (strcmp(source, ZPROP_SOURCE_VAL_RECVD) != 0))
				continue;
		}

		if (zfs_prop_user(propname) ||
		    zfs_prop_get_type(prop) == PROP_TYPE_STRING) {
			char *value;
			verify(nvlist_lookup_string(propnv,
			    ZPROP_VALUE, &value) == 0);
			VERIFY(0 == nvlist_add_string(nv, propname, value));
		} else {
			uint64_t value;
			verify(nvlist_lookup_uint64(propnv,
			    ZPROP_VALUE, &value) == 0);
			VERIFY(0 == nvlist_add_uint64(nv, propname, value));
		}
	}
}