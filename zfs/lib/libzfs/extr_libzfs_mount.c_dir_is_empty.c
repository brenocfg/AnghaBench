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
struct statfs64 {scalar_t__ f_type; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ ZFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  dir_is_empty_readdir (char const*) ; 
 int /*<<< orphan*/  dir_is_empty_stat (char const*) ; 
 scalar_t__ statfs64 (char const*,struct statfs64*) ; 

__attribute__((used)) static boolean_t
dir_is_empty(const char *dirname)
{
	struct statfs64 st;

	/*
	 * If the statvfs call fails or the filesystem is not a ZFS
	 * filesystem, fall back to the slow path which uses readdir.
	 */
	if ((statfs64(dirname, &st) != 0) ||
	    (st.f_type != ZFS_SUPER_MAGIC)) {
		return (dir_is_empty_readdir(dirname));
	}

	/*
	 * At this point, we know the provided path is on a ZFS
	 * filesystem, so we can use stat instead of readdir to
	 * determine if the directory is empty or not. We try to avoid
	 * using readdir because that requires opening "dirname"; this
	 * open file descriptor can potentially end up in a child
	 * process if there's a concurrent fork, thus preventing the
	 * zfs_mount() from otherwise succeeding (the open file
	 * descriptor inherited by the child process will cause the
	 * parent's mount to fail with EBUSY). The performance
	 * implications of replacing the open, read, and close with a
	 * single stat is nice; but is not the main motivation for the
	 * added complexity.
	 */
	return (dir_is_empty_stat(dirname));
}