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
struct TYPE_3__ {int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  enum lzc_send_flags { ____Placeholder_lzc_send_flags } lzc_send_flags ;

/* Variables and functions */
#define  EDQUOT 141 
#define  EFAULT 140 
#define  EFBIG 139 
#define  EINVAL 138 
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
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int lzc_send_space (char const*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int
zfs_send_space(zfs_handle_t *zhp, const char *snapname, const char *from,
    enum lzc_send_flags flags, uint64_t *spacep)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	int error;

	assert(snapname != NULL);
	error = lzc_send_space(snapname, from, flags, spacep);

	if (error != 0) {
		char errbuf[1024];
		(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
		    "warning: cannot estimate space for '%s'"), snapname);

		switch (error) {
		case EXDEV:
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "not an earlier snapshot from the same fs"));
			return (zfs_error(hdl, EZFS_CROSSTARGET, errbuf));

		case ENOENT:
			if (zfs_dataset_exists(hdl, snapname,
			    ZFS_TYPE_SNAPSHOT)) {
				zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
				    "incremental source (%s) does not exist"),
				    snapname);
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
		case EINVAL:
			zfs_error_aux(hdl, strerror(error));
			return (zfs_error(hdl, EZFS_BADBACKUP, errbuf));

		default:
			return (zfs_standard_error(hdl, error, errbuf));
		}
	}

	return (0);
}