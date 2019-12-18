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
struct TYPE_6__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_7__ {char* member_0; int zc_cookie; int zc_flags; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; scalar_t__ zc_fromobj; int /*<<< orphan*/  zc_sendobj; scalar_t__ zc_obj; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
#define  EACCES 141 
#define  EDQUOT 140 
#define  EFAULT 139 
#define  EFBIG 138 
#define  EIO 137 
#define  ENOENT 136 
#define  ENOLINK 135 
#define  ENOSPC 134 
#define  ENOSTR 133 
#define  ENXIO 132 
#define  EPIPE 131 
#define  ERANGE 130 
#define  EROFS 129 
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_BADBACKUP ; 
 int /*<<< orphan*/  EZFS_CROSSTARGET ; 
 int /*<<< orphan*/  EZFS_CRYPTOFAILED ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_IOC_SEND ; 
 int /*<<< orphan*/  ZFS_PROP_OBJSETID ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int
dump_ioctl(zfs_handle_t *zhp, const char *fromsnap, uint64_t fromsnap_obj,
    boolean_t fromorigin, int outfd, enum lzc_send_flags flags,
    nvlist_t *debugnv)
{
	zfs_cmd_t zc = {"\0"};
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	nvlist_t *thisdbg;

	assert(zhp->zfs_type == ZFS_TYPE_SNAPSHOT);
	assert(fromsnap_obj == 0 || !fromorigin);

	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
	zc.zc_cookie = outfd;
	zc.zc_obj = fromorigin;
	zc.zc_sendobj = zfs_prop_get_int(zhp, ZFS_PROP_OBJSETID);
	zc.zc_fromobj = fromsnap_obj;
	zc.zc_flags = flags;

	VERIFY(0 == nvlist_alloc(&thisdbg, NV_UNIQUE_NAME, 0));
	if (fromsnap && fromsnap[0] != '\0') {
		VERIFY(0 == nvlist_add_string(thisdbg,
		    "fromsnap", fromsnap));
	}

	if (zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_SEND, &zc) != 0) {
		char errbuf[1024];
		(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
		    "warning: cannot send '%s'"), zhp->zfs_name);

		VERIFY(0 == nvlist_add_uint64(thisdbg, "error", errno));
		if (debugnv) {
			VERIFY(0 == nvlist_add_nvlist(debugnv,
			    zhp->zfs_name, thisdbg));
		}
		nvlist_free(thisdbg);

		switch (errno) {
		case EXDEV:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "not an earlier snapshot from the same fs"));
			return (zfs_error(hdl, EZFS_CROSSTARGET, errbuf));

		case EACCES:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "source key must be loaded"));
			return (zfs_error(hdl, EZFS_CRYPTOFAILED, errbuf));

		case ENOENT:
			if (zfs_dataset_exists(hdl, zc.zc_name,
			    ZFS_TYPE_SNAPSHOT)) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "incremental source (@%s) does not exist"),
				    zc.zc_value);
			}
			return (zfs_error(hdl, EZFS_NOENT, errbuf));

		case EDQUOT:
		case EFBIG:
		case EIO:
		case ENOLINK:
		case ENOSPC:
		case ENOSTR:
		case ENXIO:
		case EPIPE:
		case ERANGE:
		case EFAULT:
		case EROFS:
			zfs_error_aux(hdl, strerror(errno));
			return (zfs_error(hdl, EZFS_BADBACKUP, errbuf));

		default:
			return (zfs_standard_error(hdl, errno, errbuf));
		}
	}

	if (debugnv)
		VERIFY(0 == nvlist_add_nvlist(debugnv, zhp->zfs_name, thisdbg));
	nvlist_free(thisdbg);

	return (0);
}