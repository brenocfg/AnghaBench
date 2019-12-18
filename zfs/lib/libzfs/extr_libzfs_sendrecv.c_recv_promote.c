#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_11__ {char* member_0; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_value; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_12__ {scalar_t__ verbose; } ;
typedef  TYPE_3__ recvflags_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCP_CMD_FORCE_NEW_KEY ; 
 int EACCES ; 
 int /*<<< orphan*/  ZFS_IOC_PROMOTE ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 int lzc_change_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 TYPE_1__* recv_open_grand_origin (TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
recv_promote(libzfs_handle_t *hdl, const char *fsname,
    const char *origin_fsname, recvflags_t *flags)
{
	int err;
	zfs_cmd_t zc = {"\0"};
	zfs_handle_t *zhp = NULL, *ozhp = NULL;

	if (flags->verbose)
		(void) printf("promoting %s\n", fsname);

	(void) strlcpy(zc.zc_value, origin_fsname, sizeof (zc.zc_value));
	(void) strlcpy(zc.zc_name, fsname, sizeof (zc.zc_name));

	/*
	 * Attempt to promote the dataset. If it fails with EACCES the
	 * promotion would cause this dataset to leave its encryption root.
	 * Force the origin to become an encryption root and try again.
	 */
	err = zfs_ioctl(hdl, ZFS_IOC_PROMOTE, &zc);
	if (err == EACCES) {
		zhp = zfs_open(hdl, fsname, ZFS_TYPE_DATASET);
		if (zhp == NULL) {
			err = -1;
			goto out;
		}

		ozhp = recv_open_grand_origin(zhp);
		if (ozhp == NULL) {
			err = -1;
			goto out;
		}

		err = lzc_change_key(ozhp->zfs_name, DCP_CMD_FORCE_NEW_KEY,
		    NULL, NULL, 0);
		if (err != 0)
			goto out;

		err = zfs_ioctl(hdl, ZFS_IOC_PROMOTE, &zc);
	}

out:
	if (zhp != NULL)
		zfs_close(zhp);
	if (ozhp != NULL)
		zfs_close(ozhp);

	return (err);
}