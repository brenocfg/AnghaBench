#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zfs_userspace_cb_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  scalar_t__ zfs_userquota_prop_t ;
struct TYPE_6__ {int /*<<< orphan*/  zu_space; int /*<<< orphan*/  zu_rid; int /*<<< orphan*/  zu_domain; } ;
typedef  TYPE_1__ zfs_useracct_t ;
struct TYPE_7__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_2__ zfs_handle_t ;
struct TYPE_8__ {char* member_0; uintptr_t zc_nvlist_dst; int zc_nvlist_dst_size; int /*<<< orphan*/  zc_name; scalar_t__ zc_objset_type; } ;
typedef  TYPE_3__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ENOTSUP ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_USERSPACE_MANY ; 
 scalar_t__ ZFS_PROP_GROUPOBJQUOTA ; 
 scalar_t__ ZFS_PROP_GROUPOBJUSED ; 
 scalar_t__ ZFS_PROP_PROJECTOBJQUOTA ; 
 scalar_t__ ZFS_PROP_PROJECTOBJUSED ; 
 scalar_t__ ZFS_PROP_PROJECTQUOTA ; 
 scalar_t__ ZFS_PROP_PROJECTUSED ; 
 scalar_t__ ZFS_PROP_USEROBJQUOTA ; 
 scalar_t__ ZFS_PROP_USEROBJUSED ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int zfs_standard_error_fmt (int /*<<< orphan*/ *,scalar_t__,char*) ; 

int
zfs_userspace(zfs_handle_t *zhp, zfs_userquota_prop_t type,
    zfs_userspace_cb_t func, void *arg)
{
	zfs_cmd_t zc = {"\0"};
	zfs_useracct_t buf[100];
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	int ret;

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	zc.zc_objset_type = type;
	zc.zc_nvlist_dst = (uintptr_t)buf;

	for (;;) {
		zfs_useracct_t *zua = buf;

		zc.zc_nvlist_dst_size = sizeof (buf);
		if (zfs_ioctl(hdl, ZFS_IOC_USERSPACE_MANY, &zc) != 0) {
			char errbuf[1024];

			if ((errno == ENOTSUP &&
			    (type == ZFS_PROP_USEROBJUSED ||
			    type == ZFS_PROP_GROUPOBJUSED ||
			    type == ZFS_PROP_USEROBJQUOTA ||
			    type == ZFS_PROP_GROUPOBJQUOTA ||
			    type == ZFS_PROP_PROJECTOBJUSED ||
			    type == ZFS_PROP_PROJECTOBJQUOTA ||
			    type == ZFS_PROP_PROJECTUSED ||
			    type == ZFS_PROP_PROJECTQUOTA)))
				break;

			(void) snprintf(errbuf, sizeof (errbuf),
			    dgettext(TEXT_DOMAIN,
			    "cannot get used/quota for %s"), zc.zc_name);
			return (zfs_standard_error_fmt(hdl, errno, errbuf));
		}
		if (zc.zc_nvlist_dst_size == 0)
			break;

		while (zc.zc_nvlist_dst_size > 0) {
			if ((ret = func(arg, zua->zu_domain, zua->zu_rid,
			    zua->zu_space)) != 0)
				return (ret);
			zua++;
			zc.zc_nvlist_dst_size -= sizeof (zfs_useracct_t);
		}
	}

	return (0);
}