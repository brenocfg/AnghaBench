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
struct TYPE_8__ {int zfs_type; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_9__ {scalar_t__ domount; int /*<<< orphan*/  nomount; } ;
typedef  TYPE_2__ recvflags_t ;
typedef  int /*<<< orphan*/  prop_changelist_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_GATHER_MOUNT_ALWAYS ; 
 int ENOENT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  changelist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changelist_gather (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int changelist_postfix (int /*<<< orphan*/ *) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  libzfs_set_pipe_max (int) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ *,char*,int) ; 
 int zfs_receive_impl (int /*<<< orphan*/ *,char const*,char*,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
zfs_receive(libzfs_handle_t *hdl, const char *tosnap, nvlist_t *props,
    recvflags_t *flags, int infd, avl_tree_t *stream_avl)
{
	char *top_zfs = NULL;
	int err;
	int cleanup_fd;
	uint64_t action_handle = 0;
	struct stat sb;
	char *originsnap = NULL;

	/*
	 * The only way fstat can fail is if we do not have a valid file
	 * descriptor.
	 */
	if (fstat(infd, &sb) == -1) {
		perror("fstat");
		return (-2);
	}

	/*
	 * It is not uncommon for gigabytes to be processed in zfs receive.
	 * Speculatively increase the buffer size if supported by the platform.
	 */
	if (S_ISFIFO(sb.st_mode))
		libzfs_set_pipe_max(infd);

	if (props) {
		err = nvlist_lookup_string(props, "origin", &originsnap);
		if (err && err != ENOENT)
			return (err);
	}

	cleanup_fd = open(ZFS_DEV, O_RDWR|O_EXCL);
	VERIFY(cleanup_fd >= 0);

	err = zfs_receive_impl(hdl, tosnap, originsnap, flags, infd, NULL, NULL,
	    stream_avl, &top_zfs, cleanup_fd, &action_handle, NULL, props);

	VERIFY(0 == close(cleanup_fd));

	if (err == 0 && !flags->nomount && flags->domount && top_zfs) {
		zfs_handle_t *zhp = NULL;
		prop_changelist_t *clp = NULL;

		zhp = zfs_open(hdl, top_zfs,
		    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
		if (zhp == NULL) {
			err = -1;
			goto out;
		} else {
			if (zhp->zfs_type == ZFS_TYPE_VOLUME) {
				zfs_close(zhp);
				goto out;
			}

			clp = changelist_gather(zhp, ZFS_PROP_MOUNTPOINT,
			    CL_GATHER_MOUNT_ALWAYS, 0);
			zfs_close(zhp);
			if (clp == NULL) {
				err = -1;
				goto out;
			}

			/* mount and share received datasets */
			err = changelist_postfix(clp);
			changelist_free(clp);
			if (err != 0)
				err = -1;
		}
	}

out:
	if (top_zfs)
		free(top_zfs);

	return (err);
}