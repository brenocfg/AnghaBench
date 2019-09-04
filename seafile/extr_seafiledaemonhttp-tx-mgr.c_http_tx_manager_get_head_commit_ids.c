#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {TYPE_1__* http_tx_mgr; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  HttpTxManager ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  TYPE_2__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int HTTP_OK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char const*) ; 
 scalar_t__ http_post (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * repo_head_commit_map_from_json (char*,int /*<<< orphan*/ ) ; 
 char* repo_id_list_to_json (int /*<<< orphan*/ *) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

GHashTable *
http_tx_manager_get_head_commit_ids (HttpTxManager *manager,
                                     const char *host,
                                     gboolean use_fileserver_port,
                                     GList *repo_id_list)
{
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    CURL *curl;
    char *url;
    char *req_content = NULL;
    gint64 req_size;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    GHashTable *map = NULL;

    pool = find_connection_pool (priv, host);
    if (!pool) {
        seaf_warning ("Failed to create connection pool for host %s.\n", host);
        return NULL;
    }

    conn = connection_pool_get_connection (pool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", host);
        return NULL;
    }

    curl = conn->curl;

    if (!use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/head-commits-multi/", host);
    else
        url = g_strdup_printf ("%s/repo/head-commits-multi/", host);

    req_content = repo_id_list_to_json (repo_id_list);
    req_size = strlen(req_content);

    if (http_post (curl, url, NULL, req_content, req_size,
                   &status, &rsp_content, &rsp_size, TRUE, NULL) < 0) {
        conn->release = TRUE;
        goto out;
    }

    if (status != HTTP_OK) {
        seaf_warning ("Bad response code for POST %s: %d\n", url, status);
        goto out;
    }

    map = repo_head_commit_map_from_json (rsp_content, rsp_size);

out:
    g_free (url);
    connection_pool_return_connection (pool, conn);
    /* returned by json_dumps(). */
    free (req_content);
    g_free (rsp_content);
    return map;
}