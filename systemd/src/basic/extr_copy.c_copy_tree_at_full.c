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
typedef  int /*<<< orphan*/  uid_t ;
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_dev; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  copy_progress_path_t ;
typedef  int /*<<< orphan*/  copy_progress_bytes_t ;
typedef  int /*<<< orphan*/  CopyFlags ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int /*<<< orphan*/  COPY_DEPTH_MAX ; 
 int EOPNOTSUPP ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int fd_copy_directory (int,char const*,struct stat*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int fd_copy_fifo (int,char const*,struct stat*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fd_copy_node (int,char const*,struct stat*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fd_copy_regular (int,char const*,struct stat*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int fd_copy_symlink (int,char const*,struct stat*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fstatat (int,char const*,struct stat*,int /*<<< orphan*/ ) ; 

int copy_tree_at_full(
                int fdf,
                const char *from,
                int fdt,
                const char *to,
                uid_t override_uid,
                gid_t override_gid,
                CopyFlags copy_flags,
                copy_progress_path_t progress_path,
                copy_progress_bytes_t progress_bytes,
                void *userdata) {

        struct stat st;

        assert(from);
        assert(to);

        if (fstatat(fdf, from, &st, AT_SYMLINK_NOFOLLOW) < 0)
                return -errno;

        if (S_ISREG(st.st_mode))
                return fd_copy_regular(fdf, from, &st, fdt, to, override_uid, override_gid, copy_flags, progress_bytes, userdata);
        else if (S_ISDIR(st.st_mode))
                return fd_copy_directory(fdf, from, &st, fdt, to, st.st_dev, COPY_DEPTH_MAX, override_uid, override_gid, copy_flags, NULL, progress_path, progress_bytes, userdata);
        else if (S_ISLNK(st.st_mode))
                return fd_copy_symlink(fdf, from, &st, fdt, to, override_uid, override_gid, copy_flags);
        else if (S_ISFIFO(st.st_mode))
                return fd_copy_fifo(fdf, from, &st, fdt, to, override_uid, override_gid, copy_flags);
        else if (S_ISBLK(st.st_mode) || S_ISCHR(st.st_mode) || S_ISSOCK(st.st_mode))
                return fd_copy_node(fdf, from, &st, fdt, to, override_uid, override_gid, copy_flags);
        else
                return -EOPNOTSUPP;
}