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
struct TYPE_4__ {size_t zc_objset_type; scalar_t__* zc_value; scalar_t__ zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 size_t ZFS_NUM_USERQUOTA_PROPS ; 
 size_t ZFS_PROP_GROUPOBJQUOTA ; 
 size_t ZFS_PROP_GROUPOBJUSED ; 
 size_t ZFS_PROP_GROUPQUOTA ; 
 size_t ZFS_PROP_GROUPUSED ; 
 size_t ZFS_PROP_USEROBJQUOTA ; 
 size_t ZFS_PROP_USEROBJUSED ; 
 size_t ZFS_PROP_USERQUOTA ; 
 size_t ZFS_PROP_USERUSED ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 scalar_t__ groupmember (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * userquota_perms ; 
 int zfs_secpolicy_read (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zfs_secpolicy_write_perms (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_secpolicy_userspace_one(zfs_cmd_t *zc, nvlist_t *innvl, cred_t *cr)
{
	int err = zfs_secpolicy_read(zc, innvl, cr);
	if (err)
		return (err);

	if (zc->zc_objset_type >= ZFS_NUM_USERQUOTA_PROPS)
		return (SET_ERROR(EINVAL));

	if (zc->zc_value[0] == 0) {
		/*
		 * They are asking about a posix uid/gid.  If it's
		 * themself, allow it.
		 */
		if (zc->zc_objset_type == ZFS_PROP_USERUSED ||
		    zc->zc_objset_type == ZFS_PROP_USERQUOTA ||
		    zc->zc_objset_type == ZFS_PROP_USEROBJUSED ||
		    zc->zc_objset_type == ZFS_PROP_USEROBJQUOTA) {
			if (zc->zc_guid == crgetuid(cr))
				return (0);
		} else if (zc->zc_objset_type == ZFS_PROP_GROUPUSED ||
		    zc->zc_objset_type == ZFS_PROP_GROUPQUOTA ||
		    zc->zc_objset_type == ZFS_PROP_GROUPOBJUSED ||
		    zc->zc_objset_type == ZFS_PROP_GROUPOBJQUOTA) {
			if (groupmember(zc->zc_guid, cr))
				return (0);
		}
		/* else is for project quota/used */
	}

	return (zfs_secpolicy_write_perms(zc->zc_name,
	    userquota_perms[zc->zc_objset_type], cr));
}