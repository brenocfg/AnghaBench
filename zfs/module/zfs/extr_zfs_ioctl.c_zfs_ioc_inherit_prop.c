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
typedef  int zprop_type_t ;
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_3__ {char* zc_value; int /*<<< orphan*/  zc_name; scalar_t__ zc_cookie; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  PROP_TYPE_INDEX 130 
#define  PROP_TYPE_NUMBER 129 
#define  PROP_TYPE_STRING 128 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZFS_PROP_VERSION ; 
 scalar_t__ ZFS_PROP_VOLSIZE ; 
 scalar_t__ ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_SRC_INHERITED ; 
 int /*<<< orphan*/  ZPROP_SRC_NONE ; 
 int dsl_prop_inherit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int zfs_prop_get_type (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_inheritable (scalar_t__) ; 
 int zfs_prop_set_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 

__attribute__((used)) static int
zfs_ioc_inherit_prop(zfs_cmd_t *zc)
{
	const char *propname = zc->zc_value;
	zfs_prop_t prop = zfs_name_to_prop(propname);
	boolean_t received = zc->zc_cookie;
	zprop_source_t source = (received
	    ? ZPROP_SRC_NONE		/* revert to received value, if any */
	    : ZPROP_SRC_INHERITED);	/* explicitly inherit */
	nvlist_t *dummy;
	nvpair_t *pair;
	zprop_type_t type;
	int err;

	if (!received) {
		/*
		 * Only check this in the non-received case. We want to allow
		 * 'inherit -S' to revert non-inheritable properties like quota
		 * and reservation to the received or default values even though
		 * they are not considered inheritable.
		 */
		if (prop != ZPROP_INVAL && !zfs_prop_inheritable(prop))
			return (SET_ERROR(EINVAL));
	}

	if (prop == ZPROP_INVAL) {
		if (!zfs_prop_user(propname))
			return (SET_ERROR(EINVAL));

		type = PROP_TYPE_STRING;
	} else if (prop == ZFS_PROP_VOLSIZE || prop == ZFS_PROP_VERSION) {
		return (SET_ERROR(EINVAL));
	} else {
		type = zfs_prop_get_type(prop);
	}

	/*
	 * zfs_prop_set_special() expects properties in the form of an
	 * nvpair with type info.
	 */
	dummy = fnvlist_alloc();

	switch (type) {
	case PROP_TYPE_STRING:
		VERIFY(0 == nvlist_add_string(dummy, propname, ""));
		break;
	case PROP_TYPE_NUMBER:
	case PROP_TYPE_INDEX:
		VERIFY(0 == nvlist_add_uint64(dummy, propname, 0));
		break;
	default:
		err = SET_ERROR(EINVAL);
		goto errout;
	}

	pair = nvlist_next_nvpair(dummy, NULL);
	if (pair == NULL) {
		err = SET_ERROR(EINVAL);
	} else {
		err = zfs_prop_set_special(zc->zc_name, source, pair);
		if (err == -1) /* property is not "special", needs handling */
			err = dsl_prop_inherit(zc->zc_name, zc->zc_value,
			    source);
	}

errout:
	nvlist_free(dummy);
	return (err);
}