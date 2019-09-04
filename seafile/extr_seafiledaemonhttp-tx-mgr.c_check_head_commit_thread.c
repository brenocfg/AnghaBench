#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_11__ {TYPE_1__* http_tx_mgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  error_code; void* success; void* is_deleted; int /*<<< orphan*/  token; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  host; int /*<<< orphan*/  use_fileserver_port; } ;
struct TYPE_9__ {void* release; int /*<<< orphan*/ * curl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  TYPE_2__ Connection ;
typedef  TYPE_3__ CheckHeadData ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int HTTP_OK ; 
 int HTTP_REPO_DELETED ; 
 void* TRUE ; 
 TYPE_2__* connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  curl_error_to_http_task_error (int) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_error_to_http_task_error (int) ; 
 scalar_t__ http_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int*) ; 
 scalar_t__ parse_head_commit_info (char*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,...) ; 

__attribute__((used)) static void *
check_head_commit_thread (void *vdata)
{
    CheckHeadData *data = vdata;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    CURL *curl;
    char *url;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;

    pool = find_connection_pool (priv, data->host);
    if (!pool) {
        seaf_warning ("Failed to create connection pool for host %s.\n", data->host);
        return vdata;
    }

    conn = connection_pool_get_connection (pool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", data->host);
        return vdata;
    }

    curl = conn->curl;

    if (!data->use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/commit/HEAD",
                               data->host, data->repo_id);
    else
        url = g_strdup_printf ("%s/repo/%s/commit/HEAD",
                               data->host, data->repo_id);

    int curl_error;
    if (http_get (curl, url, data->token, &status, &rsp_content, &rsp_size,
                  NULL, NULL, TRUE, &curl_error) < 0) {
        conn->release = TRUE;
        data->error_code = curl_error_to_http_task_error (curl_error);
        goto out;
    }

    if (status == HTTP_OK) {
        if (parse_head_commit_info (rsp_content, rsp_size, data) < 0)
            goto out;
        data->success = TRUE;
    } else if (status == HTTP_REPO_DELETED) {
        data->is_deleted = TRUE;
        data->success = TRUE;
    } else {
        seaf_warning ("Bad response code for GET %s: %d.\n", url, status);
        data->error_code = http_error_to_http_task_error (status);
    }

out:
    g_free (url);
    g_free (rsp_content);
    connection_pool_return_connection (pool, conn);
    return vdata;
}