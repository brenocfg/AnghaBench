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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  struct dirent DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ DT_BLK ; 
 scalar_t__ DT_CHR ; 
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_FIFO ; 
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_REG ; 
 scalar_t__ DT_SOCK ; 
 scalar_t__ DT_UNKNOWN ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct dirent*) ; 
 int /*<<< orphan*/  dirfd (struct dirent*) ; 
 int errno ; 
 scalar_t__ fstatat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ ) ; 

int dirent_ensure_type(DIR *d, struct dirent *de) {
        struct stat st;

        assert(d);
        assert(de);

        if (de->d_type != DT_UNKNOWN)
                return 0;

        if (fstatat(dirfd(d), de->d_name, &st, AT_SYMLINK_NOFOLLOW) < 0)
                return -errno;

        de->d_type =
                S_ISREG(st.st_mode)  ? DT_REG  :
                S_ISDIR(st.st_mode)  ? DT_DIR  :
                S_ISLNK(st.st_mode)  ? DT_LNK  :
                S_ISFIFO(st.st_mode) ? DT_FIFO :
                S_ISSOCK(st.st_mode) ? DT_SOCK :
                S_ISCHR(st.st_mode)  ? DT_CHR  :
                S_ISBLK(st.st_mode)  ? DT_BLK  :
                                       DT_UNKNOWN;

        return 0;
}