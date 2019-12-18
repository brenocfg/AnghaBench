#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_userquota_prop_t ;
struct TYPE_6__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_7__ {char* member_0; int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_objset_type; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_ONE ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int userquota_propname_decode (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_prop_get_userquota_common(zfs_handle_t *zhp, const char *propname,
    uint64_t *propvalue, zfs_userquota_prop_t *typep)
{
	int err;
	zfs_cmd_t zc = {"\0"};

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	err = userquota_propname_decode(propname,
	    zfs_prop_get_int(zhp, ZFS_PROP_ZONED),
	    typep, zc.zc_value, sizeof (zc.zc_value), &zc.zc_guid);
	zc.zc_objset_type = *typep;
	if (err)
		return (err);

	err = zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_USERSPACE_ONE, &zc);
	if (err)
		return (err);

	*propvalue = zc.zc_cookie;
	return (0);
}