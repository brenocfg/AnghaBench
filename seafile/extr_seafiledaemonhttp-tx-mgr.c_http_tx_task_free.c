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
struct TYPE_6__ {int /*<<< orphan*/  ev_mgr; } ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* repo_name; int /*<<< orphan*/  cevent_id; int /*<<< orphan*/  blk_ref_cnts; struct TYPE_5__* email; struct TYPE_5__* worktree; struct TYPE_5__* passwd; struct TYPE_5__* token; struct TYPE_5__* host; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  cevent_manager_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 
 TYPE_2__* seaf ; 

__attribute__((used)) static void
http_tx_task_free (HttpTxTask *task)
{
    g_free (task->host);
    g_free (task->token);
    g_free (task->passwd);
    g_free (task->worktree);
    g_free (task->email);
    if (task->type == HTTP_TASK_TYPE_DOWNLOAD) {
        g_hash_table_destroy (task->blk_ref_cnts);
        cevent_manager_unregister (seaf->ev_mgr, task->cevent_id);
        g_free (task->repo_name);
    }
    g_free (task);
}