#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_9__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_8__ {scalar_t__ runtime_state; scalar_t__ type; scalar_t__ done_blocks; scalar_t__ n_blocks; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  done_fs_objs; int /*<<< orphan*/  n_fs_objs; int /*<<< orphan*/  done_download; int /*<<< orphan*/  total_download; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  uploaded_bytes; int /*<<< orphan*/  total_bytes; scalar_t__ multipart_upload; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafileTask ;
typedef  TYPE_2__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_RT_STATE_BLOCK ; 
 scalar_t__ HTTP_TASK_RT_STATE_FS ; 
 scalar_t__ HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  g_object_set (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/  http_task_rt_state_to_str (scalar_t__) ; 
 int /*<<< orphan*/  http_task_state_to_str (int /*<<< orphan*/ ) ; 
 char* http_tx_task_get_rate (TYPE_2__*) ; 
 TYPE_4__* seaf ; 
 TYPE_1__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * seafile_task_new () ; 

__attribute__((used)) static SeafileTask *
convert_http_task (HttpTxTask *task)
{
    SeafileTask *t = seafile_task_new();

    g_object_set (t,
                  "repo_id", task->repo_id,
                  "state", http_task_state_to_str(task->state),
                  "rt_state", http_task_rt_state_to_str(task->runtime_state),
                  NULL);

    if (task->type == HTTP_TASK_TYPE_DOWNLOAD) {
        g_object_set (t, "ttype", "download", NULL);
        if (task->runtime_state == HTTP_TASK_RT_STATE_BLOCK) {
            g_object_set (t, "block_total", task->total_download,
                          "block_done", task->done_download,
                          NULL);
            g_object_set (t, "rate", http_tx_task_get_rate(task), NULL);
        } else if (task->runtime_state == HTTP_TASK_RT_STATE_FS) {
            g_object_set (t, "fs_objects_total", task->n_fs_objs,
                          "fs_objects_done", task->done_fs_objs,
                          NULL);
        }
    } else {
        g_object_set (t, "ttype", "upload", NULL);
        if (task->runtime_state == HTTP_TASK_RT_STATE_BLOCK) {
            SyncInfo *info = seaf_sync_manager_get_sync_info (seaf->sync_mgr, task->repo_id);
            if (info && info->multipart_upload) {
                g_object_set (t, "block_total", info->total_bytes,
                              "block_done", info->uploaded_bytes,
                              NULL);
            } else {
                g_object_set (t, "block_total", (gint64)task->n_blocks,
                              "block_done", (gint64)task->done_blocks,
                              NULL);
            }
            g_object_set (t, "rate", http_tx_task_get_rate(task), NULL);
        }
    }

    return t;
}