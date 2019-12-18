#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint ;
typedef  int gboolean ;
struct TYPE_13__ {int /*<<< orphan*/  last_changed; } ;
typedef  TYPE_1__ WTStatus ;
struct TYPE_16__ {scalar_t__ Action; int /*<<< orphan*/  FileNameLength; int /*<<< orphan*/  FileName; } ;
struct TYPE_15__ {TYPE_1__* status; } ;
struct TYPE_14__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_2__ SeafStat ;
typedef  TYPE_3__ RepoWatchInfo ;
typedef  TYPE_4__* PFILE_NOTIFY_INFORMATION ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ FILE_ACTION_ADDED ; 
 scalar_t__ FILE_ACTION_MODIFIED ; 
 scalar_t__ FILE_ACTION_REMOVED ; 
 scalar_t__ FILE_ACTION_RENAMED_OLD_NAME ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  WT_EVENT_CREATE_OR_UPDATE ; 
 int /*<<< orphan*/  WT_EVENT_DELETE ; 
 int /*<<< orphan*/  add_event_to_queue (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* convert_to_unix_path (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_atomic_int_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* g_build_filename (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ handle_consecutive_duplicate_event (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  handle_rename (TYPE_3__*,TYPE_4__*,char const*,char*,int) ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 int seaf_stat (char*,TYPE_2__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_one_event (RepoWatchInfo *info,
                   const char *worktree,
                   PFILE_NOTIFY_INFORMATION event,
                   gboolean last_event)
{
    WTStatus *status = info->status;
    char *filename;
    gboolean add_to_queue = TRUE;

#if 0
    if (handle_consecutive_duplicate_event (info, event))
        add_to_queue = FALSE;
#endif

    gboolean convert_long_path = !(event->Action == FILE_ACTION_RENAMED_OLD_NAME ||
                                   event->Action == FILE_ACTION_REMOVED);
    filename = convert_to_unix_path (worktree, event->FileName, event->FileNameLength,
                                     convert_long_path);
    if (!filename)
        goto out;

    handle_rename (info, event, worktree, filename, last_event);

    if (event->Action == FILE_ACTION_MODIFIED) {
        seaf_debug ("Modified %s.\n", filename);

        /* Ignore modified event for directories. */
        char *full_path = g_build_filename (worktree, filename, NULL);
        SeafStat st;
        int rc = seaf_stat (full_path, &st);
        if (rc < 0 || S_ISDIR(st.st_mode)) {
            g_free (full_path);
            goto out;
        }
        g_free (full_path);

        if (add_to_queue)
            add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
    } else if (event->Action == FILE_ACTION_ADDED) {
        seaf_debug ("Created %s.\n", filename);
        add_event_to_queue (status, WT_EVENT_CREATE_OR_UPDATE, filename, NULL);
    } else if (event->Action == FILE_ACTION_REMOVED) {
        seaf_debug ("Deleted %s.\n", filename);
        add_event_to_queue (status, WT_EVENT_DELETE, filename, NULL);
    }

out:
    g_free (filename);
    g_atomic_int_set (&info->status->last_changed, (gint)time(NULL));

}