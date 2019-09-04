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
typedef  int /*<<< orphan*/  options ;
struct TYPE_7__ {int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_repo_ro; int /*<<< orphan*/ * fset; } ;
struct TYPE_6__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  email; int /*<<< orphan*/  version; int /*<<< orphan*/  id; int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_readonly; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_2__ AddOptions ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ add_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_deleted (struct index_state*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scan_worktree_for_changes (struct index_state *istate, SeafRepo *repo,
                           SeafileCrypt *crypt, GList *ignore_list,
                           LockedFileSet *fset)
{
    remove_deleted (istate, repo->worktree, "", ignore_list, fset,
                    repo->id, repo->is_readonly, repo->changeset);

    AddOptions options;
    memset (&options, 0, sizeof(options));
    options.fset = fset;
    options.is_repo_ro = repo->is_readonly;
    options.changeset = repo->changeset;

    if (add_recursive (repo->id, repo->version, repo->email,
                       istate, repo->worktree, "", crypt, FALSE, ignore_list,
                       NULL, NULL, &options) < 0)
        return -1;

    return 0;
}