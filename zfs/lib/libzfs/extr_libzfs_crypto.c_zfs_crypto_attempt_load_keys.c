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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_3__ {scalar_t__ cb_numattempted; scalar_t__ cb_numfailed; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ loadkey_cbdata_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int ENOENT ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 char* gettext (char*) ; 
 int load_keys_cb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_handle_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int) ; 

int
zfs_crypto_attempt_load_keys(libzfs_handle_t *hdl, char *fsname)
{
	int ret;
	zfs_handle_t *zhp = NULL;
	loadkey_cbdata_t cb = { 0 };

	zhp = zfs_open(hdl, fsname, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
	if (zhp == NULL) {
		ret = ENOENT;
		goto error;
	}

	ret = load_keys_cb(zfs_handle_dup(zhp), &cb);
	if (ret)
		goto error;

	(void) printf(gettext("%llu / %llu keys successfully loaded\n"),
	    (u_longlong_t)(cb.cb_numattempted - cb.cb_numfailed),
	    (u_longlong_t)cb.cb_numattempted);

	if (cb.cb_numfailed != 0) {
		ret = -1;
		goto error;
	}

	zfs_close(zhp);
	return (0);

error:
	if (zhp != NULL)
		zfs_close(zhp);
	return (ret);
}