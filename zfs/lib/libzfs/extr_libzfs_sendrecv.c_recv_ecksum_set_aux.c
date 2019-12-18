#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  token_buf ;
typedef  int /*<<< orphan*/  target_fs ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAXPROPLEN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_RECEIVE_RESUME_TOKEN ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int) ; 
 int zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recv_ecksum_set_aux(libzfs_handle_t *hdl, const char *target_snap,
    boolean_t resumable)
{
	char target_fs[ZFS_MAX_DATASET_NAME_LEN];

	zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
	    "checksum mismatch or incomplete stream"));

	if (!resumable)
		return;
	(void) strlcpy(target_fs, target_snap, sizeof (target_fs));
	*strchr(target_fs, '@') = '\0';
	zfs_handle_t *zhp = zfs_open(hdl, target_fs,
	    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
	if (zhp == NULL)
		return;

	char token_buf[ZFS_MAXPROPLEN];
	int error = zfs_prop_get(zhp, ZFS_PROP_RECEIVE_RESUME_TOKEN,
	    token_buf, sizeof (token_buf),
	    NULL, NULL, 0, B_TRUE);
	if (error == 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "checksum mismatch or incomplete stream.\n"
		    "Partially received snapshot is saved.\n"
		    "A resuming stream can be generated on the sending "
		    "system by running:\n"
		    "    zfs send -t %s"),
		    token_buf);
	}
	zfs_close(zhp);
}