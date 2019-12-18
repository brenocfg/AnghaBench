#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* member_0; int zc_cleanup_fd; unsigned int zc_guid; scalar_t__ zc_cookie; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
#define  ENOENT 130 
#define  ENOMEM 129 
#define  ESHUTDOWN 128 
 int /*<<< orphan*/  EZFS_NOMEM ; 
 int /*<<< orphan*/  EZFS_POOLUNAVAIL ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 unsigned int ZEVENT_NONBLOCK ; 
 int /*<<< orphan*/  ZEVENT_SIZE ; 
 int /*<<< orphan*/  ZFS_IOC_EVENTS_NEXT ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ zcmd_alloc_dst_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcmd_expand_dst_nvlist (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 int zcmd_read_dst_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int zfs_error_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int zpool_standard_error_fmt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

int
zpool_events_next(libzfs_handle_t *hdl, nvlist_t **nvp,
    int *dropped, unsigned flags, int zevent_fd)
{
	zfs_cmd_t zc = {"\0"};
	int error = 0;

	*nvp = NULL;
	*dropped = 0;
	zc.zc_cleanup_fd = zevent_fd;

	if (flags & ZEVENT_NONBLOCK)
		zc.zc_guid = ZEVENT_NONBLOCK;

	if (zcmd_alloc_dst_nvlist(hdl, &zc, ZEVENT_SIZE) != 0)
		return (-1);

retry:
	if (zfs_ioctl(hdl, ZFS_IOC_EVENTS_NEXT, &zc) != 0) {
		switch (errno) {
		case ESHUTDOWN:
			error = zfs_error_fmt(hdl, EZFS_POOLUNAVAIL,
			    dgettext(TEXT_DOMAIN, "zfs shutdown"));
			goto out;
		case ENOENT:
			/* Blocking error case should not occur */
			if (!(flags & ZEVENT_NONBLOCK))
				error = zpool_standard_error_fmt(hdl, errno,
				    dgettext(TEXT_DOMAIN, "cannot get event"));

			goto out;
		case ENOMEM:
			if (zcmd_expand_dst_nvlist(hdl, &zc) != 0) {
				error = zfs_error_fmt(hdl, EZFS_NOMEM,
				    dgettext(TEXT_DOMAIN, "cannot get event"));
				goto out;
			} else {
				goto retry;
			}
		default:
			error = zpool_standard_error_fmt(hdl, errno,
			    dgettext(TEXT_DOMAIN, "cannot get event"));
			goto out;
		}
	}

	error = zcmd_read_dst_nvlist(hdl, &zc, nvp);
	if (error != 0)
		goto out;

	*dropped = (int)zc.zc_cookie;
out:
	zcmd_free_nvlists(&zc);

	return (error);
}