#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  commit_mgr; } ;
struct TYPE_11__ {char const* parent_id; scalar_t__ second_parent_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  version; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafCommit ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GDestroyNotify ;

/* Variables and functions */
 int diff_commits (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ diff_entry_free ; 
 int diff_merge (TYPE_2__*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* g_strdup (char*) ; 
 TYPE_6__* seaf ; 
 TYPE_2__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_2__*) ; 

GList *
seaf_repo_diff (SeafRepo *repo, const char *old, const char *new, int fold_dir_diff, char **error)
{
    SeafCommit *c1 = NULL, *c2 = NULL;
    int ret = 0;
    GList *diff_entries = NULL;

    c2 = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                         repo->id, repo->version,
                                         new);
    if (!c2) {
        *error = g_strdup("Can't find new commit");
        return NULL;
    }

    if (old == NULL || old[0] == '\0') {
        if (c2->parent_id && c2->second_parent_id) {
            ret = diff_merge (c2, &diff_entries, fold_dir_diff);
            seaf_commit_unref (c2);
            if (ret < 0) {
                *error = g_strdup("Failed to do diff");
                g_list_free_full (diff_entries, (GDestroyNotify)diff_entry_free);
                return NULL;
            }
            return diff_entries;
        }

        if (!c2->parent_id) {
            seaf_commit_unref (c2);
            return NULL;
        }
        c1 = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                             repo->id, repo->version,
                                             c2->parent_id);
    } else {
        c1 = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                             repo->id, repo->version, old);
    }

    if (!c1) {
        *error = g_strdup("Can't find old commit");
        seaf_commit_unref (c2);
        return NULL;
    }

    /* do diff */
    ret = diff_commits (c1, c2, &diff_entries, fold_dir_diff);
    if (ret < 0) {
        g_list_free_full (diff_entries, (GDestroyNotify)diff_entry_free);
        diff_entries = NULL;
        *error = g_strdup("Failed to do diff");
    }

    seaf_commit_unref (c1);
    seaf_commit_unref (c2);

    return diff_entries;
}