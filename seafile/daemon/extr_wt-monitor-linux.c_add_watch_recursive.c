#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dirent {char const* d_name; scalar_t__ d_type; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_6__ {int /*<<< orphan*/  status; int /*<<< orphan*/  mapping; } ;
struct TYPE_5__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ RepoWatchInfo ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ WATCH_MASK ; 
 int /*<<< orphan*/  WT_EVENT_CREATE_OR_UPDATE ; 
 int /*<<< orphan*/  add_event_to_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_mapping (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int inotify_add_watch (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_debug (char*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_watch_recursive (RepoWatchInfo *info,
                     int in_fd,
                     const char *worktree,
                     const char *path,
                     gboolean add_events)
{
    char *full_path;
    SeafStat st;
    DIR *dir;
    struct dirent *dent;
    int wd;

    full_path = g_build_filename (worktree, path, NULL);

    if (stat (full_path, &st) < 0) {
        seaf_warning ("[wt mon] fail to stat %s: %s\n", full_path, strerror(errno));
        goto out;
    }

    if (add_events && path[0] != 0)
        add_event_to_queue (info->status, WT_EVENT_CREATE_OR_UPDATE,
                            path, NULL);

    if (S_ISDIR (st.st_mode)) {
        seaf_debug ("Watching %s.\n", full_path);

        wd = inotify_add_watch (in_fd, full_path, (uint32_t)WATCH_MASK);
        if (wd < 0) {
            seaf_warning ("[wt mon] fail to add watch to %s: %s.\n",
                          full_path, strerror(errno));
            goto out;
        }

        add_mapping (info->mapping, path, wd);

        dir = opendir (full_path);
        if (!dir) {
            seaf_warning ("[wt mon] fail to open dir %s: %s.\n",
                          full_path, strerror(errno));
            goto out;
        }

        while (1) {
            dent = readdir (dir);
            if (!dent)
                break;
            if (strcmp (dent->d_name, ".") == 0 ||
                strcmp (dent->d_name, "..") == 0)
                continue;

            char *sub_path = g_build_filename (path, dent->d_name, NULL);

            /* Check d_type to avoid stating every files under this dir.
             * Note that d_type may not be supported in some file systems,
             * in this case DT_UNKNOWN is returned.
             */
            if (dent->d_type == DT_DIR || dent->d_type == DT_LNK ||
                dent->d_type == DT_UNKNOWN)
                add_watch_recursive (info, in_fd, worktree, sub_path, add_events);

            if (dent->d_type == DT_REG && add_events)
                add_event_to_queue (info->status, WT_EVENT_CREATE_OR_UPDATE,
                                    sub_path, NULL);
            g_free (sub_path);
        }

        closedir (dir);
    }

out:
    g_free (full_path);
    return 0;
}