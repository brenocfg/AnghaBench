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
struct TYPE_10__ {void* release; int /*<<< orphan*/ * curl; } ;
struct TYPE_9__ {int /*<<< orphan*/  requests; void* success; int /*<<< orphan*/  host; int /*<<< orphan*/  use_fileserver_port; } ;
struct TYPE_8__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  TYPE_2__ GetLockedFilesData ;
typedef  int /*<<< orphan*/  GDestroyNotify ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  TYPE_3__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int HTTP_OK ; 
 void* TRUE ; 
 char* compose_get_locked_files_request (int /*<<< orphan*/ ) ; 
 TYPE_3__* connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ http_locked_files_req_free ; 
 scalar_t__ http_post (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_locked_files (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void *
get_locked_files_thread (void *vdata)
{
    GetLockedFilesData *data = vdata;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    CURL *curl;
    char *url;
    char *req_content = NULL;
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
        url = g_strdup_printf ("%s/seafhttp/repo/locked-files", data->host);
    else
        url = g_strdup_printf ("%s/repo/locked-files", data->host);

    req_content = compose_get_locked_files_request (data->requests);
    if (!req_content)
        goto out;

    if (http_post (curl, url, NULL, req_content, strlen(req_content),
                   &status, &rsp_content, &rsp_size, TRUE, NULL) < 0) {
        conn->release = TRUE;
        goto out;
    }

    if (status == HTTP_OK) {
        if (parse_locked_files (rsp_content, rsp_size, data) < 0)
            goto out;
        data->success = TRUE;
    } else {
        seaf_warning ("Bad response code for GET %s: %d.\n", url, status);
    }

out:
    g_list_free_full (data->requests, (GDestroyNotify)http_locked_files_req_free);

    g_free (url);
    g_free (req_content);
    g_free (rsp_content);
    connection_pool_return_connection (pool, conn);
    return vdata;
}