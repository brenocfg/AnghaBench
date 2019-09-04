#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_11__ {int /*<<< orphan*/  filelock_mgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; int /*<<< orphan*/  worktree; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ check_full_path_ignore (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_7__* seaf ; 
 int /*<<< orphan*/  seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  update_active_file (TYPE_2__*,char const*,TYPE_1__*,struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_active_path_recursive (TYPE_2__*,char const*,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_active_path (SeafRepo *repo, const char *path,
                     struct index_state *istate, GList *ignore_list)
{
    SeafStat st;
    gboolean ignored = FALSE;

    char *fullpath = g_build_filename (repo->worktree, path, NULL);
    if (seaf_stat (fullpath, &st) < 0) {
        g_free (fullpath);
        return;
    }

    if (check_full_path_ignore (repo->worktree, path, ignore_list))
        ignored = TRUE;

    if (S_ISREG(st.st_mode)) {
        if (!seaf_filelock_manager_is_file_locked(seaf->filelock_mgr,
                                                  repo->id, path)) {
            update_active_file (repo, path, &st, istate, ignored);
        }
    } else {
        update_active_path_recursive (repo, path, istate, ignore_list, ignored);
    }

    g_free (fullpath);
}