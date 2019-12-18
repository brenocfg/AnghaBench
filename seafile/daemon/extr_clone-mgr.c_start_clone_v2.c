#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_14__ {scalar_t__ server_url; int /*<<< orphan*/  peer_port; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  email; int /*<<< orphan*/  token; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  worktree; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_STATE_FETCH ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  REPO_PROP_SERVER_URL ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_WRITE_LOCAL_DATA ; 
 scalar_t__ add_transfer_task (TYPE_2__*,int /*<<< orphan*/ **) ; 
 scalar_t__ g_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ g_mkdir_with_parents (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_clone_done_v2 (TYPE_1__*,TYPE_2__*) ; 
 TYPE_9__* seaf ; 
 TYPE_1__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_email (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_relay_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_token (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_to_error (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_clone_v2 (CloneTask *task)
{
    GError *error = NULL;

    if (g_access (task->worktree, F_OK) != 0 &&
        g_mkdir_with_parents (task->worktree, 0777) < 0) {
        seaf_warning ("[clone mgr] Failed to create worktree %s.\n",
                      task->worktree);
        transition_to_error (task, SYNC_ERROR_ID_WRITE_LOCAL_DATA);
        return;
    }

    SeafRepo *repo = seaf_repo_manager_get_repo (seaf->repo_mgr, task->repo_id);
    if (repo != NULL) {
        seaf_repo_manager_set_repo_token (seaf->repo_mgr, repo, task->token);
        seaf_repo_manager_set_repo_email (seaf->repo_mgr, repo, task->email);
        seaf_repo_manager_set_repo_relay_info (seaf->repo_mgr, repo->id,
                                               task->peer_addr, task->peer_port);
        if (task->server_url) {
            seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                                 repo->id,
                                                 REPO_PROP_SERVER_URL,
                                                 task->server_url);
        }

        mark_clone_done_v2 (repo, task);
        return;
    }

    if (add_transfer_task (task, &error) == 0)
        transition_state (task, CLONE_STATE_FETCH);
    else
        transition_to_error (task, SYNC_ERROR_ID_NOT_ENOUGH_MEMORY);
}