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
struct stat {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  copy_progress_path_t ;
typedef  int /*<<< orphan*/  copy_progress_bytes_t ;
typedef  int /*<<< orphan*/  CopyFlags ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  COPY_DEPTH_MAX ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  GID_INVALID ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_INVALID ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int fd_copy_directory (int /*<<< orphan*/ ,char const*,struct stat*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 

int copy_directory_full(
                const char *from,
                const char *to,
                CopyFlags copy_flags,
                copy_progress_path_t progress_path,
                copy_progress_bytes_t progress_bytes,
                void *userdata) {

        struct stat st;

        assert(from);
        assert(to);

        if (lstat(from, &st) < 0)
                return -errno;

        if (!S_ISDIR(st.st_mode))
                return -ENOTDIR;

        return fd_copy_directory(AT_FDCWD, from, &st, AT_FDCWD, to, st.st_dev, COPY_DEPTH_MAX, UID_INVALID, GID_INVALID, copy_flags, NULL, progress_path, progress_bytes, userdata);
}