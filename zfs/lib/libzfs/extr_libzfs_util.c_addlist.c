#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pl_prop; int /*<<< orphan*/  pl_fixed; int /*<<< orphan*/  pl_width; int /*<<< orphan*/ * pl_user_prop; } ;
typedef  TYPE_1__ zprop_list_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EZFS_BADPROP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int /*<<< orphan*/  ZFS_TYPE_POOL ; 
 int ZPROP_INVAL ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ *,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_prop_user (char*) ; 
 int /*<<< orphan*/  zfs_prop_userquota (char*) ; 
 int /*<<< orphan*/  zfs_prop_written (char*) ; 
 int /*<<< orphan*/ * zfs_strdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zpool_prop_feature (char*) ; 
 int /*<<< orphan*/  zpool_prop_unsupported (char*) ; 
 int zprop_name_to_prop (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprop_valid_for_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprop_width (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
addlist(libzfs_handle_t *hdl, char *propname, zprop_list_t **listp,
    zfs_type_t type)
{
	int prop;
	zprop_list_t *entry;

	prop = zprop_name_to_prop(propname, type);

	if (prop != ZPROP_INVAL && !zprop_valid_for_type(prop, type, B_FALSE))
		prop = ZPROP_INVAL;

	/*
	 * When no property table entry can be found, return failure if
	 * this is a pool property or if this isn't a user-defined
	 * dataset property,
	 */
	if (prop == ZPROP_INVAL && ((type == ZFS_TYPE_POOL &&
	    !zpool_prop_feature(propname) &&
	    !zpool_prop_unsupported(propname)) ||
	    (type == ZFS_TYPE_DATASET && !zfs_prop_user(propname) &&
	    !zfs_prop_userquota(propname) && !zfs_prop_written(propname)))) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "invalid property '%s'"), propname);
		return (zfs_error(hdl, EZFS_BADPROP,
		    dgettext(TEXT_DOMAIN, "bad property list")));
	}

	if ((entry = zfs_alloc(hdl, sizeof (zprop_list_t))) == NULL)
		return (-1);

	entry->pl_prop = prop;
	if (prop == ZPROP_INVAL) {
		if ((entry->pl_user_prop = zfs_strdup(hdl, propname)) ==
		    NULL) {
			free(entry);
			return (-1);
		}
		entry->pl_width = strlen(propname);
	} else {
		entry->pl_width = zprop_width(prop, &entry->pl_fixed,
		    type);
	}

	*listp = entry;

	return (0);
}