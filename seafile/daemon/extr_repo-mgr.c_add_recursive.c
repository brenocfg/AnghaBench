#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_11__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_10__ {char const* repo_id; int version; char const* modifier; char const* worktree; int /*<<< orphan*/ * options; int /*<<< orphan*/ ** remain_files; int /*<<< orphan*/ * total_size; int /*<<< orphan*/ * ignore_list; int /*<<< orphan*/  ignore_empty_dir; int /*<<< orphan*/ * crypt; struct index_state* istate; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafStat ;
typedef  int /*<<< orphan*/  GQueue ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_2__ AddParams ;
typedef  int /*<<< orphan*/  AddOptions ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PATH_SEPERATOR ; 
 int /*<<< orphan*/  SYNC_STATUS_ERROR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_dir_recursive (char const*,char*,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_file (char const*,int,char const*,struct index_state*,char const*,char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* g_build_path (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ lstat (char*,TYPE_1__*) ; 
 TYPE_4__* seaf ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*) ; 

__attribute__((used)) static int
add_recursive (const char *repo_id,
               int version,
               const char *modifier,
               struct index_state *istate, 
               const char *worktree,
               const char *path,
               SeafileCrypt *crypt,
               gboolean ignore_empty_dir,
               GList *ignore_list,
               gint64 *total_size,
               GQueue **remain_files,
               AddOptions *options)
{
    char *full_path;
    SeafStat st;

    full_path = g_build_path (PATH_SEPERATOR, worktree, path, NULL);
    if (seaf_stat (full_path, &st) < 0) {
        /* Ignore broken symlinks on Linux and Mac OS X */
        if (lstat (full_path, &st) == 0 && S_ISLNK(st.st_mode)) {
            g_free (full_path);
            return 0;
        }
        seaf_warning ("Failed to stat %s.\n", full_path);
        g_free (full_path);
        /* Ignore error. */

        seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                              repo_id,
                                              path,
                                              0,
                                              SYNC_STATUS_ERROR);

        return 0;
    }

    if (S_ISREG(st.st_mode)) {
        add_file (repo_id,
                  version,
                  modifier,
                  istate,
                  path,
                  full_path,
                  &st,
                  crypt,
                  total_size,
                  remain_files,
                  options);
    } else if (S_ISDIR(st.st_mode)) {
        AddParams params = {
            .repo_id = repo_id,
            .version = version,
            .modifier = modifier,
            .istate = istate,
            .worktree = worktree,
            .crypt = crypt,
            .ignore_empty_dir = ignore_empty_dir,
            .ignore_list = ignore_list,
            .total_size = total_size,
            .remain_files = remain_files,
            .options = options,
        };

        add_dir_recursive (path, full_path, &st, &params, FALSE);
    }

    g_free (full_path);
    return 0;
}