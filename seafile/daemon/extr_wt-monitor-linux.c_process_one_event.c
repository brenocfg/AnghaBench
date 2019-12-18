#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct inotify_event {int mask; char* name; } ;
typedef  int /*<<< orphan*/  gint ;
typedef  scalar_t__ gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  last_changed; } ;
typedef  TYPE_1__ WTStatus ;
struct TYPE_8__ {TYPE_1__* status; } ;
typedef  TYPE_2__ RepoWatchInfo ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int IN_ATTRIB ; 
 int IN_CLOSE_WRITE ; 
 int IN_CREATE ; 
 int IN_DELETE ; 
 int IN_IGNORED ; 
 int IN_MODIFY ; 
 int IN_Q_OVERFLOW ; 
 int IN_UNMOUNT ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WT_EVENT_ATTRIB ; 
 int /*<<< orphan*/  WT_EVENT_CREATE_OR_UPDATE ; 
 int /*<<< orphan*/  WT_EVENT_DELETE ; 
 int /*<<< orphan*/  WT_EVENT_OVERFLOW ; 
 int /*<<< orphan*/  add_event_to_queue (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_watch_recursive (TYPE_2__*,int,char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  g_atomic_int_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  handle_rename (int,TYPE_2__*,struct inotify_event*,char const*,char*,scalar_t__) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_one_event (int in_fd,
                   RepoWatchInfo *info,
                   const char *worktree,
                   const char *parent,
                   struct inotify_event *event,
                   gboolean last_event)
{
    WTStatus *status = info->status;
    char *filename;
    gboolean update_last_changed = TRUE;
    gboolean add_to_queue = TRUE;

    /* An inotfy watch has been removed, we don't care about this for now. */
    if ((event->mask & IN_IGNORED) || (event->mask & IN_UNMOUNT))
        return;

    /* Kernel event queue was overflowed, some events may lost. */
    if (event->mask & IN_Q_OVERFLOW) {
        add_event_to_queue (status, WT_EVENT_OVERFLOW, NULL, NULL);
        return;
    }

    /* if (handle_consecutive_duplicate_event (info, event)) */
    /*     add_to_queue = FALSE; */

    filename = g_build_filename (parent, event->name, NULL);

    handle_rename (in_fd, info, event, worktree, filename, last_event);

    if (event->mask & IN_MODIFY) {
        seaf_debug ("Modified %s.\n", filename);
        if (add_to_queue)
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
    } else if (event->mask & IN_CREATE) {
        seaf_debug ("Created %s.\n", filename);

        /* Nautilus's file copy operation doesn't trigger write events.
         * If the user copy a large file into the repo, only a create
         * event and a close_write event will be received. If we process
         * the create event, we'll certainly try to index a file when it's
         * still being copied. So we'll ignore create event for files.
         * Since write and close_write events will always be triggered,
         * we don't need to worry about missing this file.
         */
        char *fullpath = g_build_filename (worktree, filename, NULL);
        struct stat st;
        if (lstat (fullpath, &st) < 0 ||
            (!S_ISDIR(st.st_mode) && !S_ISLNK(st.st_mode))) {
            g_free (fullpath);
            update_last_changed = FALSE;
            goto out;
        }
        g_free (fullpath);

        /* We now know it's a directory or a symlink. */

        /* Files or dirs could have been added under this dir before we
         * watch it. So it's safer to scan this dir. At most time we don't
         * have to scan recursively and very few new files will be found.
         */
        add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
        add_watch_recursive (info, in_fd, worktree, filename, FALSE);
    } else if (event->mask & IN_DELETE) {
        seaf_debug ("Deleted %s.\n", filename);
        add_event_to_queue (status, WT_EVENT_DELETE, filename, NULL);
    } else if (event->mask & IN_CLOSE_WRITE) {
        seaf_debug ("Close write %s.\n", filename);
        if (add_to_queue)
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
    } else if (event->mask & IN_ATTRIB) {
        seaf_debug ("Attribute changed %s.\n", filename);
        add_event_to_queue (status, WT_EVENT_ATTRIB, filename, NULL);
    }

out:
    g_free (filename);
    if (update_last_changed)
        g_atomic_int_set (&info->status->last_changed, (gint)time(NULL));
}