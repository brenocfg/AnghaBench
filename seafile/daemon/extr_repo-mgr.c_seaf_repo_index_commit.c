#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct index_state {int /*<<< orphan*/  cache_nr; int /*<<< orphan*/  cache; int /*<<< orphan*/  cache_changed; } ;
struct cache_tree {int /*<<< orphan*/  sha1; } ;
typedef  int /*<<< orphan*/  istate ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_18__ {int /*<<< orphan*/  commit_mgr; } ;
struct TYPE_17__ {int /*<<< orphan*/  root_id; } ;
struct TYPE_16__ {char* id; int /*<<< orphan*/  version; TYPE_1__* head; int /*<<< orphan*/  worktree; int /*<<< orphan*/ * changeset; TYPE_2__* manager; } ;
struct TYPE_15__ {char* index_dir; } ;
struct TYPE_14__ {int /*<<< orphan*/  commit_id; } ;
typedef  TYPE_2__ SeafRepoManager ;
typedef  TYPE_3__ SeafRepo ;
typedef  TYPE_4__ SeafCommit ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GError ;
typedef  int /*<<< orphan*/  GDestroyNotify ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 int /*<<< orphan*/  SEAF_ERR_INTERNAL ; 
 int SEAF_PATH_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 struct cache_tree* cache_tree () ; 
 int /*<<< orphan*/  cache_tree_free (struct cache_tree**) ; 
 scalar_t__ cache_tree_update (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cache_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changeset_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * changeset_new (char*) ; 
 int /*<<< orphan*/  check_worktree_common (TYPE_3__*) ; 
 scalar_t__ commit_tree (TYPE_3__*,char*,char*,char*) ; 
 char* commit_tree_from_changeset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_trees_cb ; 
 int /*<<< orphan*/  compare_index_changeset (struct index_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diff_commit_roots (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ diff_entry_free ; 
 char* diff_results_to_description (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_index (struct index_state*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_signal_emit_by_name (TYPE_8__*,char*,TYPE_3__*) ; 
 char* g_strdup (char*) ; 
 scalar_t__ index_add (TYPE_3__*,struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct index_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ read_index_from (struct index_state*,char*,int /*<<< orphan*/ ) ; 
 TYPE_8__* seaf ; 
 TYPE_4__* seaf_commit_manager_get_commit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_commit_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  seaf_message (char*,char*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ update_index (struct index_state*,char*) ; 

char *
seaf_repo_index_commit (SeafRepo *repo,
                        gboolean is_force_commit,
                        gboolean is_initial_commit,
                        GError **error)
{
    SeafRepoManager *mgr = repo->manager;
    struct index_state istate;
    char index_path[SEAF_PATH_MAX];
    SeafCommit *head = NULL;
    char *new_root_id = NULL;
    char commit_id[41];
    ChangeSet *changeset = NULL;
    GList *diff_results = NULL;
    char *desc = NULL;
    char *ret = NULL;

    if (!check_worktree_common (repo))
        return NULL;

    memset (&istate, 0, sizeof(istate));
    snprintf (index_path, SEAF_PATH_MAX, "%s/%s", mgr->index_dir, repo->id);
    if (read_index_from (&istate, index_path, repo->version) < 0) {
        seaf_warning ("Failed to load index.\n");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL, "Internal data structure error");
        return NULL;
    }

    changeset = changeset_new (repo->id);
    if (!changeset) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL, "Internal data structure error");
        goto out;
    }

    repo->changeset = changeset;

    if (index_add (repo, &istate, is_force_commit) < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL, "Failed to add");
        goto out;
    }

    if (!istate.cache_changed)
        goto out;

    if (!is_initial_commit && !is_force_commit) {
        new_root_id = commit_tree_from_changeset (changeset);
        if (!new_root_id) {
            seaf_warning ("Create commit tree failed for repo %s\n", repo->id);
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                         "Failed to generate commit");
            goto out;
        }
    } else {
        char hex[41];
        struct cache_tree *it = cache_tree ();
        if (cache_tree_update (repo->id, repo->version,
                               repo->worktree,
                               it, istate.cache,
                               istate.cache_nr, 0, 0, commit_trees_cb) < 0) {
            seaf_warning ("Failed to build cache tree");
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL,
                         "Internal data structure error");
            cache_tree_free (&it);
            goto out;
        }
        rawdata_to_hex (it->sha1, hex, 20);
        new_root_id = g_strdup(hex);
        cache_tree_free (&it);
    }

    head = seaf_commit_manager_get_commit (seaf->commit_mgr,
                                           repo->id, repo->version,
                                           repo->head->commit_id);
    if (!head) {
        seaf_warning ("Head commit %s for repo %s not found\n",
                      repo->head->commit_id, repo->id);
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL, "Data corrupt");
        goto out;
    }

    if (strcmp (head->root_id, new_root_id) == 0) {
        seaf_message ("No change to the fs tree of repo %s\n", repo->id);
        /* If no file modification and addition are missing, and the new root
         * id is the same as the old one, skip commiting.
         */
        if (!is_initial_commit && !is_force_commit)
            compare_index_changeset (&istate, changeset);

        update_index (&istate, index_path);
        goto out;
    }

    diff_commit_roots (repo->id, repo->version, head->root_id, new_root_id, &diff_results, TRUE);
    desc = diff_results_to_description (diff_results);
    if (!desc)
        desc = g_strdup("");

    if (commit_tree (repo, new_root_id, desc, commit_id) < 0) {
        seaf_warning ("Failed to save commit file");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL, "Internal error");
        goto out;
    }

    if (update_index (&istate, index_path) < 0) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_INTERNAL, "Internal error");
        goto out;
    }

    g_signal_emit_by_name (seaf, "repo-committed", repo);

    ret = g_strdup(commit_id);

out:
    g_free (desc);
    seaf_commit_unref (head);
    g_free (new_root_id);
    changeset_free (changeset);
    g_list_free_full (diff_results, (GDestroyNotify)diff_entry_free);
    discard_index (&istate);
    return ret;
}