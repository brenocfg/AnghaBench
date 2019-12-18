#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  mq_mgr; int /*<<< orphan*/  http_tx_mgr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * data; struct TYPE_13__* next; } ;
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {int /*<<< orphan*/  recv_bytes; void* last_recv_bytes; int /*<<< orphan*/  sent_bytes; void* last_sent_bytes; } ;
typedef  TYPE_1__ SeafSyncManager ;
typedef  int /*<<< orphan*/  HttpTxTask ;
typedef  TYPE_2__ GString ;
typedef  TYPE_3__ GList ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  format_http_task_detail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* g_atomic_int_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_atomic_int_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (TYPE_3__*) ; 
 int /*<<< orphan*/  g_string_free (TYPE_2__*,int) ; 
 TYPE_2__* g_string_new (int /*<<< orphan*/ *) ; 
 TYPE_3__* http_tx_manager_get_download_tasks (int /*<<< orphan*/ ) ; 
 TYPE_3__* http_tx_manager_get_upload_tasks (int /*<<< orphan*/ ) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_mq_manager_publish_notification (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
update_tx_state (void *vmanager)
{
    SeafSyncManager *mgr = vmanager;
    GString *buf = g_string_new (NULL);
    GList *tasks, *ptr;
    HttpTxTask *http_task;

    mgr->last_sent_bytes = g_atomic_int_get (&mgr->sent_bytes);
    g_atomic_int_set (&mgr->sent_bytes, 0);
    mgr->last_recv_bytes = g_atomic_int_get (&mgr->recv_bytes);
    g_atomic_int_set (&mgr->recv_bytes, 0);

    tasks = http_tx_manager_get_upload_tasks (seaf->http_tx_mgr);
    for (ptr = tasks; ptr; ptr = ptr->next) {
        http_task = ptr->data;
        format_http_task_detail (http_task, buf);
    }
    g_list_free (tasks);

    tasks = http_tx_manager_get_download_tasks (seaf->http_tx_mgr);
    for (ptr = tasks; ptr; ptr = ptr->next) {
        http_task = ptr->data;
        format_http_task_detail (http_task, buf);
    }
    g_list_free (tasks);

    if (buf->len != 0)
        seaf_mq_manager_publish_notification (seaf->mq_mgr, "transfer",
                                              buf->str);

    g_string_free (buf, TRUE);

    return TRUE;
}