#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ server_url; int /*<<< orphan*/  peer_port; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  email; int /*<<< orphan*/  token; } ;
struct TYPE_19__ {scalar_t__ state; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  error; int /*<<< orphan*/  is_clone; } ;
struct TYPE_18__ {int /*<<< orphan*/  tasks; } ;
struct TYPE_17__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/  repo_mgr; } ;
typedef  TYPE_1__ SeafileSession ;
typedef  TYPE_2__ SeafRepo ;
typedef  TYPE_3__ SeafCloneManager ;
typedef  TYPE_4__ HttpTxTask ;
typedef  TYPE_5__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_STATE_CANCELED ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 scalar_t__ HTTP_TASK_STATE_ERROR ; 
 int /*<<< orphan*/  REPO_PROP_SERVER_URL ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_LOCAL_DATA_CORRUPT ; 
 int /*<<< orphan*/  check_folder_permissions (TYPE_5__*) ; 
 TYPE_5__* g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 TYPE_2__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_email (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_relay_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_token (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_state (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_to_error (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_repo_http_fetched (SeafileSession *seaf,
                      HttpTxTask *tx_task,
                      SeafCloneManager *mgr)
{
    CloneTask *task;

    /* Only handle clone task. */
    if (!tx_task->is_clone)
        return;

    task = g_hash_table_lookup (mgr->tasks, tx_task->repo_id);
    g_return_if_fail (task != NULL);

    if (tx_task->state == HTTP_TASK_STATE_CANCELED) {
        /* g_assert (task->state == CLONE_STATE_CANCEL_PENDING); */
        transition_state (task, CLONE_STATE_CANCELED);
        return;
    } else if (tx_task->state == HTTP_TASK_STATE_ERROR) {
        transition_to_error (task, tx_task->error);
        return;
    }

    SeafRepo *repo = seaf_repo_manager_get_repo (seaf->repo_mgr,
                                                 tx_task->repo_id);
    if (repo == NULL) {
        seaf_warning ("[Clone mgr] cannot find repo %s after fetched.\n", 
                   tx_task->repo_id);
        transition_to_error (task, SYNC_ERROR_ID_LOCAL_DATA_CORRUPT);
        return;
    }

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

    check_folder_permissions (task);
}