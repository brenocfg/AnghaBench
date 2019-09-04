#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_15__ {TYPE_1__* http_tx_mgr; } ;
struct TYPE_14__ {void* release; int /*<<< orphan*/ * curl; } ;
struct TYPE_13__ {scalar_t__ data; struct TYPE_13__* next; } ;
struct TYPE_12__ {TYPE_3__* requests; void* success; int /*<<< orphan*/  host; int /*<<< orphan*/  use_fileserver_port; } ;
struct TYPE_11__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  HttpFolderPermReq ;
typedef  TYPE_2__ GetFolderPermsData ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  TYPE_4__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int HTTP_OK ; 
 void* TRUE ; 
 char* compose_get_folder_perms_request (TYPE_3__*) ; 
 TYPE_4__* connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_list_free (TYPE_3__*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_folder_perm_req_free (int /*<<< orphan*/ *) ; 
 scalar_t__ http_post (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_folder_perms (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void *
get_folder_perms_thread (void *vdata)
{
    GetFolderPermsData *data = vdata;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    CURL *curl;
    char *url;
    char *req_content = NULL;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    GList *ptr;

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
        url = g_strdup_printf ("%s/seafhttp/repo/folder-perm", data->host);
    else
        url = g_strdup_printf ("%s/repo/folder-perm", data->host);

    req_content = compose_get_folder_perms_request (data->requests);
    if (!req_content)
        goto out;

    if (http_post (curl, url, NULL, req_content, strlen(req_content),
                   &status, &rsp_content, &rsp_size, TRUE, NULL) < 0) {
        conn->release = TRUE;
        goto out;
    }

    if (status == HTTP_OK) {
        if (parse_folder_perms (rsp_content, rsp_size, data) < 0)
            goto out;
        data->success = TRUE;
    } else {
        seaf_warning ("Bad response code for GET %s: %d.\n", url, status);
    }

out:
    for (ptr = data->requests; ptr; ptr = ptr->next)
        http_folder_perm_req_free ((HttpFolderPermReq *)ptr->data);
    g_list_free (data->requests);

    g_free (url);
    g_free (req_content);
    g_free (rsp_content);
    connection_pool_return_connection (pool, conn);
    return vdata;
}