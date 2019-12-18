#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_9__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
#define  ENOENT 130 
#define  ENOMEM 129 
#define  ESRCH 128 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zcmd_expand_dst_nvlist (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 int zfs_ioctl (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int zfs_standard_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_do_list_ioctl(zfs_handle_t *zhp, int arg, zfs_cmd_t *zc)
{
	int rc;
	uint64_t	orig_cookie;

	orig_cookie = zc->zc_cookie;
top:
	(void) strlcpy(zc->zc_name, zhp->zfs_name, sizeof (zc->zc_name));
	rc = zfs_ioctl(zhp->zfs_hdl, arg, zc);

	if (rc == -1) {
		switch (errno) {
		case ENOMEM:
			/* expand nvlist memory and try again */
			if (zcmd_expand_dst_nvlist(zhp->zfs_hdl, zc) != 0) {
				zcmd_free_nvlists(zc);
				return (-1);
			}
			zc->zc_cookie = orig_cookie;
			goto top;
		/*
		 * An errno value of ESRCH indicates normal completion.
		 * If ENOENT is returned, then the underlying dataset
		 * has been removed since we obtained the handle.
		 */
		case ESRCH:
		case ENOENT:
			rc = 1;
			break;
		default:
			rc = zfs_standard_error(zhp->zfs_hdl, errno,
			    dgettext(TEXT_DOMAIN,
			    "cannot iterate filesystems"));
			break;
		}
	}
	return (rc);
}