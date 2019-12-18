#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_6__ {scalar_t__ version; int /*<<< orphan*/  worktree; int /*<<< orphan*/  id; int /*<<< orphan*/  enc_iv; int /*<<< orphan*/  enc_key; int /*<<< orphan*/  enc_version; scalar_t__ encrypted; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 scalar_t__ apply_worktree_changes_to_index (TYPE_1__*,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locked_file_set_free (int /*<<< orphan*/ *) ; 
 scalar_t__ scan_worktree_for_changes (struct index_state*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* seaf ; 
 int /*<<< orphan*/  seaf_repo_free_ignore_files (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * seaf_repo_load_ignore_files (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_locked_file_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/ * seafile_crypt_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
index_add (SeafRepo *repo, struct index_state *istate, gboolean is_force_commit)
{
    SeafileCrypt *crypt = NULL;
    LockedFileSet *fset = NULL;
    GList *ignore_list = NULL;
    int ret = 0;

    if (repo->encrypted) {
        crypt = seafile_crypt_new (repo->enc_version, repo->enc_key, repo->enc_iv);
    }

#if defined WIN32 || defined __APPLE__
    if (repo->version > 0)
        fset = seaf_repo_manager_get_locked_file_set (seaf->repo_mgr, repo->id);
#endif

    ignore_list = seaf_repo_load_ignore_files (repo->worktree);

    if (!is_force_commit) {
        if (apply_worktree_changes_to_index (repo, istate, crypt, ignore_list, fset) < 0) {
            seaf_warning ("Failed to apply worktree changes to index.\n");
            ret = -1;
        }
    } else if (scan_worktree_for_changes (istate, repo, crypt, ignore_list, fset) < 0) {
        seaf_warning ("Failed to scan worktree for changes.\n");
        ret = -1;
    }

    seaf_repo_free_ignore_files (ignore_list);

#if defined WIN32 || defined __APPLE__
    locked_file_set_free (fset);
#endif

    g_free (crypt);

    return ret;
}