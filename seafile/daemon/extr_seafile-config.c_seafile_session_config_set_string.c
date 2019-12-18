#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql ;
struct TYPE_3__ {int /*<<< orphan*/ * http_proxy_password; int /*<<< orphan*/ * http_proxy_username; int /*<<< orphan*/ * http_proxy_addr; int /*<<< orphan*/ * http_proxy_type; void* use_http_proxy; void* disable_verify_certificate; void* sync_extra_temp_file; int /*<<< orphan*/ * client_name; int /*<<< orphan*/  config_db; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 void* FALSE ; 
 char* KEY_CLIENT_NAME ; 
 char* KEY_DISABLE_VERIFY_CERTIFICATE ; 
 char* KEY_PROXY_ADDR ; 
 char* KEY_PROXY_PASSWORD ; 
 char* KEY_PROXY_TYPE ; 
 char* KEY_PROXY_USERNAME ; 
 char* KEY_SYNC_EXTRA_TEMP_FILE ; 
 char* KEY_USE_PROXY ; 
 void* TRUE ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 scalar_t__ g_strcmp0 (char const*,char*) ; 
 int /*<<< orphan*/ * g_strdup (char const*) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*,char const*) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seafile_session_config_set_string (SeafileSession *session,
                                   const char *key,
                                   const char *value)
{
    char sql[256];

    sqlite3_snprintf (sizeof(sql), sql,
                      "REPLACE INTO Config VALUES ('%q', '%q');",
                      key, value);
    if (sqlite_query_exec (session->config_db, sql) < 0)
        return -1;

    if (g_strcmp0 (key, KEY_CLIENT_NAME) == 0) {
        g_free (session->client_name);
        session->client_name = g_strdup(value);
    }

    if (g_strcmp0(key, KEY_SYNC_EXTRA_TEMP_FILE) == 0) {
        if (g_strcmp0(value, "true") == 0)
            session->sync_extra_temp_file = TRUE;
        else
            session->sync_extra_temp_file = FALSE;
    }

    if (g_strcmp0(key, KEY_DISABLE_VERIFY_CERTIFICATE) == 0) {
        if (g_strcmp0(value, "true") == 0)
            session->disable_verify_certificate = TRUE;
        else
            session->disable_verify_certificate = FALSE;
    }

    if (g_strcmp0(key, KEY_USE_PROXY) == 0) {
        if (g_strcmp0(value, "true") == 0)
            session->use_http_proxy = TRUE;
        else
            session->use_http_proxy = FALSE;
    }

    if (g_strcmp0(key, KEY_PROXY_TYPE) == 0) {
        session->http_proxy_type =
            g_strcmp0(value, "none") == 0 ? NULL : g_strdup(value);
    }

    if (g_strcmp0(key, KEY_PROXY_ADDR) == 0) {
        session->http_proxy_addr = g_strdup(value);
    }

    if (g_strcmp0(key, KEY_PROXY_USERNAME) == 0) {
        session->http_proxy_username = g_strdup(value);
    }

    if (g_strcmp0(key, KEY_PROXY_PASSWORD) == 0) {
        session->http_proxy_password = g_strdup(value);
    }

    return 0;
}