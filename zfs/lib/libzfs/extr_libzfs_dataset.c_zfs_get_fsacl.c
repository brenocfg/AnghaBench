#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_6__ {char* member_0; int zc_nvlist_dst_size; uintptr_t zc_nvlist_dst; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
#define  EINVAL 131 
#define  ENOENT 130 
#define  ENOMEM 129 
#define  ENOTSUP 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_BADVERSION ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  EZFS_NOMEM ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_IOC_GET_FSACL ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int nvlist_unpack (void*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int zfs_standard_error_fmt (int /*<<< orphan*/ *,int,char*) ; 

int
zfs_get_fsacl(zfs_handle_t *zhp, nvlist_t **nvl)
{
	zfs_cmd_t zc = {"\0"};
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	int nvsz = 2048;
	void *nvbuf;
	int err = 0;
	char errbuf[1024];

	assert(zhp->zfs_type == ZFS_TYPE_VOLUME ||
	    zhp->zfs_type == ZFS_TYPE_FILESYSTEM);

tryagain:

	nvbuf = malloc(nvsz);
	if (nvbuf == NULL) {
		err = (zfs_error(hdl, EZFS_NOMEM, strerror(errno)));
		goto out;
	}

	zc.zc_nvlist_dst_size = nvsz;
	zc.zc_nvlist_dst = (uintptr_t)nvbuf;

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));

	if (zfs_ioctl(hdl, ZFS_IOC_GET_FSACL, &zc) != 0) {
		(void) snprintf(errbuf, sizeof (errbuf),
		    dgettext(TEXT_DOMAIN, "cannot get permissions on '%s'"),
		    zc.zc_name);
		switch (errno) {
		case ENOMEM:
			free(nvbuf);
			nvsz = zc.zc_nvlist_dst_size;
			goto tryagain;

		case ENOTSUP:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "pool must be upgraded"));
			err = zfs_error(hdl, EZFS_BADVERSION, errbuf);
			break;
		case EINVAL:
			err = zfs_error(hdl, EZFS_BADTYPE, errbuf);
			break;
		case ENOENT:
			err = zfs_error(hdl, EZFS_NOENT, errbuf);
			break;
		default:
			err = zfs_standard_error_fmt(hdl, errno, errbuf);
			break;
		}
	} else {
		/* success */
		int rc = nvlist_unpack(nvbuf, zc.zc_nvlist_dst_size, nvl, 0);
		if (rc) {
			(void) snprintf(errbuf, sizeof (errbuf), dgettext(
			    TEXT_DOMAIN, "cannot get permissions on '%s'"),
			    zc.zc_name);
			err = zfs_standard_error_fmt(hdl, rc, errbuf);
		}
	}

	free(nvbuf);
out:
	return (err);
}