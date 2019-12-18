#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_10__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_13__ {int /*<<< orphan*/  client_id; scalar_t__ client_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_11__ {int /*<<< orphan*/  error; int /*<<< orphan*/  repo_name; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  token; int /*<<< orphan*/  host; scalar_t__ use_fileserver_port; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ HttpTxTask ;
typedef  TYPE_3__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HTTP_FORBIDDEN ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  HTTP_TASK_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_ACCESS_DENIED ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_NO_WRITE_PERMISSION ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_PERM_NOT_SYNCABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char const*,char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,...) ; 
 char* g_uri_escape_string (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_curl_errors (TYPE_2__*,int) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_2__*,int) ; 
 scalar_t__ http_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 char* json_string_value (int /*<<< orphan*/ *) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_repo_manager_record_sync_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,...) ; 

__attribute__((used)) static int
check_permission (HttpTxTask *task, Connection *conn)
{
    CURL *curl;
    char *url;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    int ret = 0;
    json_t *rsp_obj = NULL, *reason = NULL, *unsyncable_path = NULL;
    const char *reason_str = NULL, *unsyncable_path_str = NULL;
    json_error_t jerror;

    curl = conn->curl;

    const char *type = (task->type == HTTP_TASK_TYPE_DOWNLOAD) ? "download" : "upload";
    const char *url_prefix = (task->use_fileserver_port) ? "" : "seafhttp/";
    if (seaf->client_name) {
        char *client_name = g_uri_escape_string (seaf->client_name,
                                                 NULL, FALSE);
        url = g_strdup_printf ("%s/%srepo/%s/permission-check/?op=%s"
                               "&client_id=%s&client_name=%s",
                               task->host, url_prefix, task->repo_id, type,
                               seaf->client_id, client_name);
        g_free (client_name);
    } else {
        url = g_strdup_printf ("%s/%srepo/%s/permission-check/?op=%s",
                               task->host, url_prefix, task->repo_id, type);
    }

    int curl_error;
    if (http_get (curl, url, task->token, &status, &rsp_content, &rsp_size, NULL, NULL, TRUE, &curl_error) < 0) {
        conn->release = TRUE;
        handle_curl_errors (task, curl_error);
        ret = -1;
        goto out;
    }

    if (status != HTTP_OK) {
        seaf_warning ("Bad response code for GET %s: %d.\n", url, status);

        if (status != HTTP_FORBIDDEN || !rsp_content) {
            handle_http_errors (task, status);
            ret = -1;
            goto out;
        }

        rsp_obj = json_loadb (rsp_content, rsp_size, 0 ,&jerror);
        if (!rsp_obj) {
            seaf_warning ("Parse check permission response failed: %s.\n", jerror.text);
            handle_http_errors (task, status);
            json_decref (rsp_obj);
            ret = -1;
            goto out;
        }

        reason = json_object_get (rsp_obj, "reason");
        if (!reason) {
            handle_http_errors (task, status);
            json_decref (rsp_obj);
            ret = -1;
            goto out;
        }

        reason_str = json_string_value (reason);
        if (g_strcmp0 (reason_str, "no write permission") == 0) {
            task->error = SYNC_ERROR_ID_NO_WRITE_PERMISSION;
        } else if (g_strcmp0 (reason_str, "unsyncable share permission") == 0) {
            task->error = SYNC_ERROR_ID_PERM_NOT_SYNCABLE;

            unsyncable_path = json_object_get (rsp_obj, "unsyncable_path");
            if (!unsyncable_path) {
                json_decref (rsp_obj);
                ret = -1;
                goto out;
            }

            unsyncable_path_str = json_string_value (unsyncable_path);
            if (unsyncable_path_str)
                seaf_repo_manager_record_sync_error (task->repo_id, task->repo_name,
                                                     unsyncable_path_str,
                                                     SYNC_ERROR_ID_PERM_NOT_SYNCABLE);
        } else {
            task->error = SYNC_ERROR_ID_ACCESS_DENIED;
        }

        ret = -1;
    }

out:
    g_free (url);
    g_free (rsp_content);
    curl_easy_reset (curl);

    return ret;
}