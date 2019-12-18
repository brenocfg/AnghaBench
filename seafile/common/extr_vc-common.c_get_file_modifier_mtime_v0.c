#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_7__ {int /*<<< orphan*/  fs_mgr; int /*<<< orphan*/  commit_mgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctime; int /*<<< orphan*/  creator_name; int /*<<< orphan*/  root_id; int /*<<< orphan*/  parent_id; } ;
typedef  TYPE_1__ SeafCommit ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int diff_parents_with_path (TYPE_1__*,char const*,char const*,int,char const*,char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_clear_error (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 TYPE_4__* seaf ; 
 TYPE_1__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,char const*,int,char*) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_1__*) ; 
 char* seaf_fs_manager_path_to_obj_id (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
get_file_modifier_mtime_v0 (const char *repo_id, const char *store_id, int version,
                            const char *head, const char *path,
                            char **modifier, gint64 *mtime)
{
    char commit_id[41];
    SeafCommit *commit = NULL;
    char *file_id = NULL;
    int changed;
    int ret = 0;
    GError *error = NULL;

    *modifier = NULL;
    *mtime = 0;

    memcpy (commit_id, head, 41);

    while (1) {
        commit = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                                 repo_id, version,
                                                 commit_id);
        if (!commit) {
            ret = -1;
            break;
        }

        /* We hit the initial commit. */
        if (!commit->parent_id)
            break;

        file_id = seaf_fs_manager_path_to_obj_id (seaf->fs_mgr,
                                                  store_id, version,
                                                  commit->root_id,
                                                  path,
                                                  NULL,
                                                  &error);
        if (error) {
            g_clear_error (&error);
            ret = -1;
            break;
        }
        /* We expect commit to have this file. */
        if (!file_id) {
            ret = -1;
            break;
        }

        changed = diff_parents_with_path (commit,
                                          repo_id, store_id, version,
                                          path, file_id,
                                          commit_id, &error);
        if (error) {
            g_clear_error (&error);
            ret = -1;
            break;
        }

        if (changed) {
            *modifier = g_strdup (commit->creator_name);
            *mtime = commit->ctime;
            break;
        } else {
            /* If this commit doesn't change the file, commit_id will be set
             * to the parent commit to traverse.
             */
            g_free (file_id);
            seaf_commit_unref (commit);
        }
    }

    g_free (file_id);
    if (commit)
        seaf_commit_unref (commit);
    return ret;
}