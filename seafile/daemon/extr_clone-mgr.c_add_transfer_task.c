#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  http_tx_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  tx_id; int /*<<< orphan*/  repo_name; int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  email; int /*<<< orphan*/  http_protocol_version; int /*<<< orphan*/  worktree; int /*<<< orphan*/  passwd; int /*<<< orphan*/  server_head_id; int /*<<< orphan*/  token; int /*<<< orphan*/  effective_url; int /*<<< orphan*/  repo_version; } ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int http_tx_manager_add_download (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_2__* seaf ; 

__attribute__((used)) static int
add_transfer_task (CloneTask *task, GError **error)
{
    int ret = http_tx_manager_add_download (seaf->http_tx_mgr,
                                            task->repo_id,
                                            task->repo_version,
                                            task->effective_url,
                                            task->token,
                                            task->server_head_id,
                                            TRUE,
                                            task->passwd,
                                            task->worktree,
                                            task->http_protocol_version,
                                            task->email,
                                            task->use_fileserver_port,
                                            task->repo_name,
                                            error);
    if (ret < 0)
        return -1;
    task->tx_id = g_strdup(task->repo_id);
    return 0;
}