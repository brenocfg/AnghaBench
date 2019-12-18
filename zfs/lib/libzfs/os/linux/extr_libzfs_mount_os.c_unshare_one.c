#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t zfs_share_proto_t ;
typedef  int /*<<< orphan*/ * sa_share_t ;
struct TYPE_7__ {int /*<<< orphan*/  libzfs_sharehdl; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_unshare_err; int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_INIT_SHARE_API ; 
 int SA_OK ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_6__* proto_table ; 
 int sa_disable_share (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_errorstr (int) ; 
 int /*<<< orphan*/ * sa_find_share (int /*<<< orphan*/ ,char*) ; 
 int zfs_error_fmt (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
 int zfs_init_libshare (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* zfs_strdup (TYPE_1__*,char const*) ; 

int
unshare_one(libzfs_handle_t *hdl, const char *name, const char *mountpoint,
    zfs_share_proto_t proto)
{
	sa_share_t share;
	int err;
	char *mntpt;
	/*
	 * Mountpoint could get trashed if libshare calls getmntany
	 * which it does during API initialization, so strdup the
	 * value.
	 */
	mntpt = zfs_strdup(hdl, mountpoint);

	/* make sure libshare initialized */
	if ((err = zfs_init_libshare(hdl, SA_INIT_SHARE_API)) != SA_OK) {
		free(mntpt);	/* don't need the copy anymore */
		return (zfs_error_fmt(hdl, proto_table[proto].p_unshare_err,
		    dgettext(TEXT_DOMAIN, "cannot unshare '%s': %s"),
		    name, sa_errorstr(err)));
	}

	share = sa_find_share(hdl->libzfs_sharehdl, mntpt);
	free(mntpt);	/* don't need the copy anymore */

	if (share != NULL) {
		err = sa_disable_share(share, proto_table[proto].p_name);
		if (err != SA_OK) {
			return (zfs_error_fmt(hdl,
			    proto_table[proto].p_unshare_err,
			    dgettext(TEXT_DOMAIN, "cannot unshare '%s': %s"),
			    name, sa_errorstr(err)));
		}
	} else {
		return (zfs_error_fmt(hdl, proto_table[proto].p_unshare_err,
		    dgettext(TEXT_DOMAIN, "cannot unshare '%s': not found"),
		    name));
	}
	return (0);
}