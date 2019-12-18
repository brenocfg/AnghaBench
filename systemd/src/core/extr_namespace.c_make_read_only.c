#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ mode; scalar_t__ ignore; int /*<<< orphan*/  flags; scalar_t__ nosuid; } ;
typedef  TYPE_1__ MountEntry ;
typedef  TYPE_1__ const FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_DIR ; 
 int ENOENT ; 
 int /*<<< orphan*/  IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long MS_NOSUID ; 
 unsigned long MS_RDONLY ; 
 scalar_t__ PRIVATE_DEV ; 
 int /*<<< orphan*/  TMPFS ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int bind_remount_one (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int bind_remount_recursive_with_mountinfo (int /*<<< orphan*/ ,unsigned long,unsigned long,char**,TYPE_1__ const*) ; 
 int log_debug_errno (int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mount_entry_path (TYPE_1__ const*) ; 
 scalar_t__ mount_entry_read_only (TYPE_1__ const*) ; 

__attribute__((used)) static int make_read_only(const MountEntry *m, char **blacklist, FILE *proc_self_mountinfo) {
        unsigned long new_flags = 0, flags_mask = 0;
        bool submounts = false;
        int r = 0;

        assert(m);
        assert(proc_self_mountinfo);

        if (mount_entry_read_only(m) || m->mode == PRIVATE_DEV) {
                new_flags |= MS_RDONLY;
                flags_mask |= MS_RDONLY;
        }

        if (m->nosuid) {
                new_flags |= MS_NOSUID;
                flags_mask |= MS_NOSUID;
        }

        if (flags_mask == 0) /* No Change? */
                return 0;

        /* We generally apply these changes recursively, except for /dev, and the cases we know there's
         * nothing further down.  Set /dev readonly, but not submounts like /dev/shm. Also, we only set the
         * per-mount read-only flag.  We can't set it on the superblock, if we are inside a user namespace
         * and running Linux <= 4.17. */
        submounts =
                mount_entry_read_only(m) &&
                !IN_SET(m->mode, EMPTY_DIR, TMPFS);
        if (submounts)
                r = bind_remount_recursive_with_mountinfo(mount_entry_path(m), new_flags, flags_mask, blacklist, proc_self_mountinfo);
        else
                r = bind_remount_one(mount_entry_path(m), m->flags, new_flags, flags_mask);

        /* Not that we only turn on the MS_RDONLY flag here, we never turn it off. Something that was marked
         * read-only already stays this way. This improves compatibility with container managers, where we
         * won't attempt to undo read-only mounts already applied. */

        if (r == -ENOENT && m->ignore)
                return 0;
        if (r < 0)
                return log_debug_errno(r, "Failed to re-mount '%s'%s: %m", mount_entry_path(m),
                                       submounts ? " and its submounts" : "");
        return 0;
}