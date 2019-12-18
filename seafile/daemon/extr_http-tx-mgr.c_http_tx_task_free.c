#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  blk_ref_cnts; struct TYPE_4__* repo_name; struct TYPE_4__* email; struct TYPE_4__* worktree; struct TYPE_4__* passwd; struct TYPE_4__* token; struct TYPE_4__* host; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_tx_task_free (HttpTxTask *task)
{
    g_free (task->host);
    g_free (task->token);
    g_free (task->passwd);
    g_free (task->worktree);
    g_free (task->email);
    g_free (task->repo_name);
    if (task->type == HTTP_TASK_TYPE_DOWNLOAD) {
        g_hash_table_destroy (task->blk_ref_cnts);
    }
    g_free (task);
}