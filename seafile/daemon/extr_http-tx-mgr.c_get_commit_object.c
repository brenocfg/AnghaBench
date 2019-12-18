#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_12__ {TYPE_1__* commit_mgr; } ;
struct TYPE_11__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_10__ {int repo_id; char* head; int /*<<< orphan*/  error; int /*<<< orphan*/  repo_version; int /*<<< orphan*/  token; int /*<<< orphan*/  host; int /*<<< orphan*/  use_fileserver_port; } ;
struct TYPE_9__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_2__ HttpTxTask ;
typedef  TYPE_3__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_WRITE_LOCAL_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  handle_curl_errors (TYPE_2__*,int) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_2__*,int) ; 
 scalar_t__ http_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* seaf ; 
 int seaf_obj_store_write_obj (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int) ; 

__attribute__((used)) static int
get_commit_object (HttpTxTask *task, Connection *conn)
{
    CURL *curl;
    char *url;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    int ret = 0;

    curl = conn->curl;

    if (!task->use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/commit/%s",
                               task->host, task->repo_id, task->head);
    else
        url = g_strdup_printf ("%s/repo/%s/commit/%s",
                               task->host, task->repo_id, task->head);

    int curl_error;
    if (http_get (curl, url, task->token, &status,
                  &rsp_content, &rsp_size,
                  NULL, NULL, TRUE, &curl_error) < 0) {
        conn->release = TRUE;
        handle_curl_errors (task, curl_error);
        ret = -1;
        goto out;
    }

    if (status != HTTP_OK) {
        seaf_warning ("Bad response code for GET %s: %d.\n", url, status);
        handle_http_errors (task, status);
        ret = -1;
        goto out;
    }

    int rc = seaf_obj_store_write_obj (seaf->commit_mgr->obj_store,
                                       task->repo_id, task->repo_version,
                                       task->head,
                                       rsp_content,
                                       rsp_size,
                                       FALSE);
    if (rc < 0) {
        seaf_warning ("Failed to save commit %s in repo %.8s.\n",
                      task->head, task->repo_id);
        task->error = SYNC_ERROR_ID_WRITE_LOCAL_DATA;
        ret = -1;
    }

out:
    g_free (url);
    g_free (rsp_content);
    curl_easy_reset (curl);

    return ret;
}