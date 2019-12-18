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
struct TYPE_4__ {struct TYPE_4__* effective_url; struct TYPE_4__* server_url; struct TYPE_4__* random_key; struct TYPE_4__* email; struct TYPE_4__* peer_port; struct TYPE_4__* peer_addr; struct TYPE_4__* repo_name; struct TYPE_4__* token; struct TYPE_4__* passwd; struct TYPE_4__* worktree; struct TYPE_4__* tx_id; } ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 

__attribute__((used)) static void
clone_task_free (CloneTask *task)
{
    g_free (task->tx_id);
    g_free (task->worktree);
    g_free (task->passwd);
    g_free (task->token);
    g_free (task->repo_name);
    g_free (task->peer_addr);
    g_free (task->peer_port);
    g_free (task->email);
    g_free (task->random_key);
    g_free (task->server_url);
    g_free (task->effective_url);

    g_free (task);
}