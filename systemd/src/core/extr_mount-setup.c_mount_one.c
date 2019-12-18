#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; int /*<<< orphan*/  where; int /*<<< orphan*/  type; int /*<<< orphan*/  options; int /*<<< orphan*/  flags; int /*<<< orphan*/  what; int /*<<< orphan*/  (* condition_fn ) () ;} ;
typedef  TYPE_1__ MountPoint ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_FOLLOW ; 
 int ENOENT ; 
 int LABEL_IGNORE_ENOENT ; 
 int LABEL_IGNORE_EROFS ; 
 int LOG_DEBUG ; 
 int LOG_ERR ; 
 int MNT_CHECK_WRITABLE ; 
 int MNT_FATAL ; 
 int MNT_IN_CONTAINER ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ detect_container () ; 
 int errno ; 
 int /*<<< orphan*/  label_fix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_full_errno (int,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mkdir_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkdir_p_label (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int path_is_mount_point (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  umount (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_one(const MountPoint *p, bool relabel) {
        int r, priority;

        assert(p);

        priority = (p->mode & MNT_FATAL) ? LOG_ERR : LOG_DEBUG;

        if (p->condition_fn && !p->condition_fn())
                return 0;

        /* Relabel first, just in case */
        if (relabel)
                (void) label_fix(p->where, LABEL_IGNORE_ENOENT|LABEL_IGNORE_EROFS);

        r = path_is_mount_point(p->where, NULL, AT_SYMLINK_FOLLOW);
        if (r < 0 && r != -ENOENT) {
                log_full_errno(priority, r, "Failed to determine whether %s is a mount point: %m", p->where);
                return (p->mode & MNT_FATAL) ? r : 0;
        }
        if (r > 0)
                return 0;

        /* Skip securityfs in a container */
        if (!(p->mode & MNT_IN_CONTAINER) && detect_container() > 0)
                return 0;

        /* The access mode here doesn't really matter too much, since
         * the mounted file system will take precedence anyway. */
        if (relabel)
                (void) mkdir_p_label(p->where, 0755);
        else
                (void) mkdir_p(p->where, 0755);

        log_debug("Mounting %s to %s of type %s with options %s.",
                  p->what,
                  p->where,
                  p->type,
                  strna(p->options));

        if (mount(p->what,
                  p->where,
                  p->type,
                  p->flags,
                  p->options) < 0) {
                log_full_errno(priority, errno, "Failed to mount %s at %s: %m", p->type, p->where);
                return (p->mode & MNT_FATAL) ? -errno : 0;
        }

        /* Relabel again, since we now mounted something fresh here */
        if (relabel)
                (void) label_fix(p->where, 0);

        if (p->mode & MNT_CHECK_WRITABLE) {
                if (access(p->where, W_OK) < 0) {
                        r = -errno;

                        (void) umount(p->where);
                        (void) rmdir(p->where);

                        log_full_errno(priority, r, "Mount point %s not writable after mounting: %m", p->where);
                        return (p->mode & MNT_FATAL) ? r : 0;
                }
        }

        return 1;
}