#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_17__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_20__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_19__ {char* data; } ;
struct TYPE_18__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  host; int /*<<< orphan*/  error; int /*<<< orphan*/  token; } ;
typedef  TYPE_2__ HttpTxTask ;
typedef  TYPE_3__ GList ;
typedef  TYPE_4__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int HTTP_OK ; 
 int ID_LIST_SEGMENT_N ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_SERVER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_3__* g_list_delete_link (TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* g_list_prepend (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_curl_errors (TYPE_2__*,int) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_2__*,int) ; 
 scalar_t__ http_post (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_loadb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_debug (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
upload_check_id_list_segment (HttpTxTask *task, Connection *conn, const char *url,
                              GList **send_id_list, GList **recv_id_list)
{
    json_t *array;
    json_error_t jerror;
    char *obj_id;
    int n_sent = 0;
    char *data = NULL;
    int len;
    CURL *curl;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    int ret = 0;

    /* Convert object id list to JSON format. */

    array = json_array ();

    while (*send_id_list != NULL) {
        obj_id = (*send_id_list)->data;
        json_array_append_new (array, json_string(obj_id));

        *send_id_list = g_list_delete_link (*send_id_list, *send_id_list);
        g_free (obj_id);

        if (++n_sent >= ID_LIST_SEGMENT_N)
            break;
    }

    seaf_debug ("Check %d ids for %s:%s.\n",
                n_sent, task->host, task->repo_id);

    data = json_dumps (array, 0);
    len = strlen(data);
    json_decref (array);

    /* Send fs object id list. */

    curl = conn->curl;

    int curl_error;
    if (http_post (curl, url, task->token,
                   data, len,
                   &status, &rsp_content, &rsp_size, TRUE, &curl_error) < 0) {
        conn->release = TRUE;
        handle_curl_errors (task, curl_error);
        ret = -1;
        goto out;
    }

    if (status != HTTP_OK) {
        seaf_warning ("Bad response code for POST %s: %d.\n", url, status);
        handle_http_errors (task, status);
        ret = -1;
        goto out;
    }

    /* Process needed object id list. */

    array = json_loadb (rsp_content, rsp_size, 0, &jerror);
    if (!array) {
        seaf_warning ("Invalid JSON response from the server: %s.\n", jerror.text);
        task->error = SYNC_ERROR_ID_SERVER;
        ret = -1;
        goto out;
    }

    int i;
    size_t n = json_array_size (array);
    json_t *str;

    seaf_debug ("%lu objects or blocks are needed for %s:%s.\n",
                n, task->host, task->repo_id);

    for (i = 0; i < n; ++i) {
        str = json_array_get (array, i);
        if (!str) {
            seaf_warning ("Invalid JSON response from the server.\n");
            json_decref (array);
            ret = -1;
            goto out;
        }

        *recv_id_list = g_list_prepend (*recv_id_list, g_strdup(json_string_value(str)));
    }

    json_decref (array);

out:
    curl_easy_reset (curl);
    g_free (data);
    g_free (rsp_content);

    return ret;
}