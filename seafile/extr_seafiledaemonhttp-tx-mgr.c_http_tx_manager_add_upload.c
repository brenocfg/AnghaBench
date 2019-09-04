#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_14__ {int /*<<< orphan*/  job_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_13__ {TYPE_1__* priv; } ;
struct TYPE_12__ {int protocol_version; int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {int /*<<< orphan*/  upload_tasks; } ;
typedef  int /*<<< orphan*/  SeafRepo ;
typedef  TYPE_2__ HttpTxTask ;
typedef  TYPE_3__ HttpTxManager ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HTTP_TASK_STATE_NORMAL ; 
 int /*<<< orphan*/  HTTP_TASK_TYPE_UPLOAD ; 
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_BAD_ARGS ; 
 int /*<<< orphan*/  clean_tasks_for_repo (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 TYPE_2__* http_tx_task_new (TYPE_3__*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_upload_done ; 
 int /*<<< orphan*/  http_upload_thread ; 
 TYPE_5__* seaf ; 
 scalar_t__ seaf_job_manager_schedule_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 

int
http_tx_manager_add_upload (HttpTxManager *manager,
                            const char *repo_id,
                            int repo_version,
                            const char *host,
                            const char *token,
                            int protocol_version,
                            gboolean use_fileserver_port,
                            GError **error)
{
    HttpTxTask *task;
    SeafRepo *repo;

    if (!repo_id || !token || !host) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Empty argument(s)");
        return -1;
    }

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo) {
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_BAD_ARGS, "Repo not found");
        return -1;
    }

    clean_tasks_for_repo (manager, repo_id);

    task = http_tx_task_new (manager, repo_id, repo_version,
                             HTTP_TASK_TYPE_UPLOAD, FALSE,
                             host, token, NULL, NULL);

    task->protocol_version = protocol_version;

    task->state = HTTP_TASK_STATE_NORMAL;

    task->use_fileserver_port = use_fileserver_port;

    g_hash_table_insert (manager->priv->upload_tasks,
                         g_strdup(repo_id),
                         task);

    if (seaf_job_manager_schedule_job (seaf->job_mgr,
                                       http_upload_thread,
                                       http_upload_done,
                                       task) < 0) {
        g_hash_table_remove (manager->priv->upload_tasks, repo_id);
        return -1;
    }

    return 0;
}