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
struct statvfs {unsigned long f_flag; } ;
struct libmnt_table {int dummy; } ;
struct libmnt_fs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_ITER_FORWARD ; 
 int /*<<< orphan*/  MNT_LINUX_MAP ; 
 unsigned long MS_RELATIME ; 
 int errno ; 
 int /*<<< orphan*/  log_warning (char*,char const*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*) ; 
 char* mnt_fs_get_vfs_options (struct libmnt_fs*) ; 
 int /*<<< orphan*/  mnt_get_builtin_optmap (int /*<<< orphan*/ ) ; 
 int mnt_optstr_get_flags (char const*,unsigned long*,int /*<<< orphan*/ ) ; 
 struct libmnt_fs* mnt_table_find_target (struct libmnt_table*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ statvfs (char const*,struct statvfs*) ; 

__attribute__((used)) static int get_mount_flags(const char *path, unsigned long *flags, struct libmnt_table *table) {
        struct statvfs buf = {};
        struct libmnt_fs *fs = NULL;
        const char *opts = NULL;
        int r = 0;

        fs = mnt_table_find_target(table, path, MNT_ITER_FORWARD);
        if (!fs) {
                log_warning("Could not find '%s' in mount table", path);
                goto fallback;
        }

        opts = mnt_fs_get_vfs_options(fs);
        r = mnt_optstr_get_flags(opts, flags, mnt_get_builtin_optmap(MNT_LINUX_MAP));
        if (r != 0) {
                log_warning_errno(r, "Could not get flags for '%s': %m", path);
                goto fallback;
        }

        /* relatime is default and trying to set it in an unprivileged container causes EPERM */
        *flags &= ~MS_RELATIME;
        return 0;

fallback:
        if (statvfs(path, &buf) < 0)
                return -errno;

        *flags = buf.f_flag;
        return 0;
}