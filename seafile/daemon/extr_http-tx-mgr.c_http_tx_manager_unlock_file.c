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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {TYPE_1__* http_tx_mgr; } ;
struct TYPE_7__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_6__ {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  HttpTxManager ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  TYPE_2__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char const*,char const*,char*) ; 
 char* g_uri_escape_string (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ http_put (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 

int
http_tx_manager_unlock_file (HttpTxManager *manager,
                             const char *host,
                             gboolean use_fileserver_port,
                             const char *token,
                             const char *repo_id,
                             const char *path)
{
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    CURL *curl;
    char *url;
    int status;
    int ret = 0;

    pool = find_connection_pool (priv, host);
    if (!pool) {
        seaf_warning ("Failed to create connection pool for host %s.\n", host);
        return -1;
    }

    conn = connection_pool_get_connection (pool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", host);
        return -1;
    }

    curl = conn->curl;

    char *esc_path = g_uri_escape_string(path, NULL, FALSE);
    if (!use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/unlock-file?p=%s", host, repo_id, esc_path);
    else
        url = g_strdup_printf ("%s/repo/%s/unlock-file?p=%s", host, repo_id, esc_path);
    g_free (esc_path);

    if (http_put (curl, url, token, NULL, 0, NULL, NULL,
                  &status, NULL, NULL, TRUE, NULL) < 0) {
        conn->release = TRUE;
        ret = -1;
        goto out;
    }

    if (status != HTTP_OK) {
        seaf_warning ("Bad response code for PUT %s: %d.\n", url, status);
        ret = -1;
    }

out:
    g_free (url);
    connection_pool_return_connection (pool, conn);
    return ret;
}