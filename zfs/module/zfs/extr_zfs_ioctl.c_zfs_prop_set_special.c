#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int zfs_prop_t ;
struct TYPE_6__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ DATA_TYPE_NVLIST ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ PROP_TYPE_STRING ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY (int) ; 
#define  ZFS_PROP_FILESYSTEM_LIMIT 138 
#define  ZFS_PROP_KEYLOCATION 137 
#define  ZFS_PROP_QUOTA 136 
#define  ZFS_PROP_REFQUOTA 135 
#define  ZFS_PROP_REFRESERVATION 134 
#define  ZFS_PROP_RESERVATION 133 
#define  ZFS_PROP_SNAPDEV 132 
#define  ZFS_PROP_SNAPSHOT_LIMIT 131 
#define  ZFS_PROP_VERSION 130 
#define  ZFS_PROP_VOLMODE 129 
#define  ZFS_PROP_VOLSIZE 128 
 int /*<<< orphan*/  ZPL_VERSION_USERSPACE ; 
 int ZPROP_INVAL ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int dsl_crypto_can_set_keylocation (char const*,char*) ; 
 int dsl_dataset_set_refquota (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_dataset_set_refreservation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_dir_activate_fs_ss_limit (char const*) ; 
 int dsl_dir_set_quota (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_dir_set_reservation (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* fnvpair_value_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvpair_value_uint64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zfs_ioc_id_quota_upgrade (TYPE_1__*) ; 
 int /*<<< orphan*/  zfs_ioc_userspace_upgrade (TYPE_1__*) ; 
 int zfs_name_to_prop (char const*) ; 
 scalar_t__ zfs_prop_get_type (int) ; 
 int zfs_prop_set_userquota (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_userquota (char const*) ; 
 int zfs_set_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfsvfs_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsvfs_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zvol_set_snapdev (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zvol_set_volmode (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zvol_set_volsize (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_prop_set_special(const char *dsname, zprop_source_t source,
    nvpair_t *pair)
{
	const char *propname = nvpair_name(pair);
	zfs_prop_t prop = zfs_name_to_prop(propname);
	uint64_t intval = 0;
	char *strval = NULL;
	int err = -1;

	if (prop == ZPROP_INVAL) {
		if (zfs_prop_userquota(propname))
			return (zfs_prop_set_userquota(dsname, pair));
		return (-1);
	}

	if (nvpair_type(pair) == DATA_TYPE_NVLIST) {
		nvlist_t *attrs;
		VERIFY(nvpair_value_nvlist(pair, &attrs) == 0);
		VERIFY(nvlist_lookup_nvpair(attrs, ZPROP_VALUE,
		    &pair) == 0);
	}

	/* all special properties are numeric except for keylocation */
	if (zfs_prop_get_type(prop) == PROP_TYPE_STRING) {
		strval = fnvpair_value_string(pair);
	} else {
		intval = fnvpair_value_uint64(pair);
	}

	switch (prop) {
	case ZFS_PROP_QUOTA:
		err = dsl_dir_set_quota(dsname, source, intval);
		break;
	case ZFS_PROP_REFQUOTA:
		err = dsl_dataset_set_refquota(dsname, source, intval);
		break;
	case ZFS_PROP_FILESYSTEM_LIMIT:
	case ZFS_PROP_SNAPSHOT_LIMIT:
		if (intval == UINT64_MAX) {
			/* clearing the limit, just do it */
			err = 0;
		} else {
			err = dsl_dir_activate_fs_ss_limit(dsname);
		}
		/*
		 * Set err to -1 to force the zfs_set_prop_nvlist code down the
		 * default path to set the value in the nvlist.
		 */
		if (err == 0)
			err = -1;
		break;
	case ZFS_PROP_KEYLOCATION:
		err = dsl_crypto_can_set_keylocation(dsname, strval);

		/*
		 * Set err to -1 to force the zfs_set_prop_nvlist code down the
		 * default path to set the value in the nvlist.
		 */
		if (err == 0)
			err = -1;
		break;
	case ZFS_PROP_RESERVATION:
		err = dsl_dir_set_reservation(dsname, source, intval);
		break;
	case ZFS_PROP_REFRESERVATION:
		err = dsl_dataset_set_refreservation(dsname, source, intval);
		break;
	case ZFS_PROP_VOLSIZE:
		err = zvol_set_volsize(dsname, intval);
		break;
	case ZFS_PROP_SNAPDEV:
		err = zvol_set_snapdev(dsname, source, intval);
		break;
	case ZFS_PROP_VOLMODE:
		err = zvol_set_volmode(dsname, source, intval);
		break;
	case ZFS_PROP_VERSION:
	{
		zfsvfs_t *zfsvfs;

		if ((err = zfsvfs_hold(dsname, FTAG, &zfsvfs, B_TRUE)) != 0)
			break;

		err = zfs_set_version(zfsvfs, intval);
		zfsvfs_rele(zfsvfs, FTAG);

		if (err == 0 && intval >= ZPL_VERSION_USERSPACE) {
			zfs_cmd_t *zc;

			zc = kmem_zalloc(sizeof (zfs_cmd_t), KM_SLEEP);
			(void) strcpy(zc->zc_name, dsname);
			(void) zfs_ioc_userspace_upgrade(zc);
			(void) zfs_ioc_id_quota_upgrade(zc);
			kmem_free(zc, sizeof (zfs_cmd_t));
		}
		break;
	}
	default:
		err = -1;
	}

	return (err);
}