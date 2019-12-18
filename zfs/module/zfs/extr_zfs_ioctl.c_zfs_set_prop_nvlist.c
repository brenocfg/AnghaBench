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
typedef  scalar_t__ zprop_source_t ;
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_PANIC ; 
 int /*<<< orphan*/  CRED () ; 
 scalar_t__ DATA_TYPE_BOOLEAN ; 
 scalar_t__ DATA_TYPE_NVLIST ; 
 scalar_t__ DATA_TYPE_STRING ; 
 scalar_t__ DATA_TYPE_UINT64 ; 
 scalar_t__ DATA_TYPE_UINT64_ARRAY ; 
 int /*<<< orphan*/  EINVAL ; 
#define  PROP_TYPE_INDEX 130 
#define  PROP_TYPE_NUMBER 129 
#define  PROP_TYPE_STRING 128 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ZPROP_INVAL ; 
 scalar_t__ ZPROP_SRC_INHERITED ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*) ; 
 int dsl_prop_inherit (char const*,char const*,scalar_t__) ; 
 int dsl_prop_set_int (char const*,char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int dsl_prop_set_string (char const*,char const*,scalar_t__,char*) ; 
 scalar_t__ dsl_props_set (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_int32 (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int nvlist_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int zfs_check_settable (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int zfs_prop_get_type (scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_index_to_string (scalar_t__,int /*<<< orphan*/ ,char const**) ; 
 int zfs_prop_set_special (char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_user (char const*) ; 
 scalar_t__ zfs_prop_userquota (char const*) ; 

int
zfs_set_prop_nvlist(const char *dsname, zprop_source_t source, nvlist_t *nvl,
    nvlist_t *errlist)
{
	nvpair_t *pair;
	nvpair_t *propval;
	int rv = 0;
	uint64_t intval;
	char *strval;

	nvlist_t *genericnvl = fnvlist_alloc();
	nvlist_t *retrynvl = fnvlist_alloc();
retry:
	pair = NULL;
	while ((pair = nvlist_next_nvpair(nvl, pair)) != NULL) {
		const char *propname = nvpair_name(pair);
		zfs_prop_t prop = zfs_name_to_prop(propname);
		int err = 0;

		/* decode the property value */
		propval = pair;
		if (nvpair_type(pair) == DATA_TYPE_NVLIST) {
			nvlist_t *attrs;
			attrs = fnvpair_value_nvlist(pair);
			if (nvlist_lookup_nvpair(attrs, ZPROP_VALUE,
			    &propval) != 0)
				err = SET_ERROR(EINVAL);
		}

		/* Validate value type */
		if (err == 0 && source == ZPROP_SRC_INHERITED) {
			/* inherited properties are expected to be booleans */
			if (nvpair_type(propval) != DATA_TYPE_BOOLEAN)
				err = SET_ERROR(EINVAL);
		} else if (err == 0 && prop == ZPROP_INVAL) {
			if (zfs_prop_user(propname)) {
				if (nvpair_type(propval) != DATA_TYPE_STRING)
					err = SET_ERROR(EINVAL);
			} else if (zfs_prop_userquota(propname)) {
				if (nvpair_type(propval) !=
				    DATA_TYPE_UINT64_ARRAY)
					err = SET_ERROR(EINVAL);
			} else {
				err = SET_ERROR(EINVAL);
			}
		} else if (err == 0) {
			if (nvpair_type(propval) == DATA_TYPE_STRING) {
				if (zfs_prop_get_type(prop) != PROP_TYPE_STRING)
					err = SET_ERROR(EINVAL);
			} else if (nvpair_type(propval) == DATA_TYPE_UINT64) {
				const char *unused;

				intval = fnvpair_value_uint64(propval);

				switch (zfs_prop_get_type(prop)) {
				case PROP_TYPE_NUMBER:
					break;
				case PROP_TYPE_STRING:
					err = SET_ERROR(EINVAL);
					break;
				case PROP_TYPE_INDEX:
					if (zfs_prop_index_to_string(prop,
					    intval, &unused) != 0)
						err = SET_ERROR(EINVAL);
					break;
				default:
					cmn_err(CE_PANIC,
					    "unknown property type");
				}
			} else {
				err = SET_ERROR(EINVAL);
			}
		}

		/* Validate permissions */
		if (err == 0)
			err = zfs_check_settable(dsname, pair, CRED());

		if (err == 0) {
			if (source == ZPROP_SRC_INHERITED)
				err = -1; /* does not need special handling */
			else
				err = zfs_prop_set_special(dsname, source,
				    pair);
			if (err == -1) {
				/*
				 * For better performance we build up a list of
				 * properties to set in a single transaction.
				 */
				err = nvlist_add_nvpair(genericnvl, pair);
			} else if (err != 0 && nvl != retrynvl) {
				/*
				 * This may be a spurious error caused by
				 * receiving quota and reservation out of order.
				 * Try again in a second pass.
				 */
				err = nvlist_add_nvpair(retrynvl, pair);
			}
		}

		if (err != 0) {
			if (errlist != NULL)
				fnvlist_add_int32(errlist, propname, err);
			rv = err;
		}
	}

	if (nvl != retrynvl && !nvlist_empty(retrynvl)) {
		nvl = retrynvl;
		goto retry;
	}

	if (!nvlist_empty(genericnvl) &&
	    dsl_props_set(dsname, source, genericnvl) != 0) {
		/*
		 * If this fails, we still want to set as many properties as we
		 * can, so try setting them individually.
		 */
		pair = NULL;
		while ((pair = nvlist_next_nvpair(genericnvl, pair)) != NULL) {
			const char *propname = nvpair_name(pair);
			int err = 0;

			propval = pair;
			if (nvpair_type(pair) == DATA_TYPE_NVLIST) {
				nvlist_t *attrs;
				attrs = fnvpair_value_nvlist(pair);
				propval = fnvlist_lookup_nvpair(attrs,
				    ZPROP_VALUE);
			}

			if (nvpair_type(propval) == DATA_TYPE_STRING) {
				strval = fnvpair_value_string(propval);
				err = dsl_prop_set_string(dsname, propname,
				    source, strval);
			} else if (nvpair_type(propval) == DATA_TYPE_BOOLEAN) {
				err = dsl_prop_inherit(dsname, propname,
				    source);
			} else {
				intval = fnvpair_value_uint64(propval);
				err = dsl_prop_set_int(dsname, propname, source,
				    intval);
			}

			if (err != 0) {
				if (errlist != NULL) {
					fnvlist_add_int32(errlist, propname,
					    err);
				}
				rv = err;
			}
		}
	}
	nvlist_free(genericnvl);
	nvlist_free(retrynvl);

	return (rv);
}