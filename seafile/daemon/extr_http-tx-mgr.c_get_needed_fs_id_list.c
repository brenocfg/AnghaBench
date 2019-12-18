#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_14__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_19__ {TYPE_5__* fs_mgr; int /*<<< orphan*/  branch_mgr; } ;
struct TYPE_18__ {int /*<<< orphan*/  obj_store; } ;
struct TYPE_17__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_16__ {int n_fs_objs; int /*<<< orphan*/  done_fs_objs; int /*<<< orphan*/  repo_version; int /*<<< orphan*/  repo_id; scalar_t__ is_clone; int /*<<< orphan*/  host; int /*<<< orphan*/  error; int /*<<< orphan*/  token; int /*<<< orphan*/  head; scalar_t__ use_fileserver_port; } ;
struct TYPE_15__ {int /*<<< orphan*/  commit_id; } ;
typedef  TYPE_2__ SeafBranch ;
typedef  TYPE_3__ HttpTxTask ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_4__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_SERVER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ g_hash_table_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 char* g_strdup (char const*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  handle_curl_errors (TYPE_3__*,int) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_3__*,int) ; 
 scalar_t__ http_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,int) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* json_string_value (int /*<<< orphan*/ *) ; 
 TYPE_8__* seaf ; 
 TYPE_2__* seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_debug (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_fs_manager_verify_object (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_obj_store_obj_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_needed_fs_id_list (HttpTxTask *task, Connection *conn, GList **fs_id_list)
{
    SeafBranch *master;
    CURL *curl;
    char *url = NULL;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    int ret = 0;
    json_t *array;
    json_error_t jerror;
    const char *obj_id;

    const char *url_prefix = (task->use_fileserver_port) ? "" : "seafhttp/";

    if (!task->is_clone) {
        master = seaf_branch_manager_get_branch (seaf->branch_mgr,
                                                 task->repo_id,
                                                 "master");
        if (!master) {
            seaf_warning ("Failed to get branch master for repo %.8s.\n",
                          task->repo_id);
            return -1;
        }

        url = g_strdup_printf ("%s/%srepo/%s/fs-id-list/"
                               "?server-head=%s&client-head=%s",
                               task->host, url_prefix, task->repo_id,
                               task->head, master->commit_id);

        seaf_branch_unref (master);
    } else {
        url = g_strdup_printf ("%s/%srepo/%s/fs-id-list/?server-head=%s",
                               task->host, url_prefix, task->repo_id, task->head);
    }

    curl = conn->curl;

    int curl_error;
    if (http_get (curl, url, task->token, &status,
                  &rsp_content, &rsp_size,
                  NULL, NULL, (!task->is_clone), &curl_error) < 0) {
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

    seaf_debug ("Received fs object list size %lu from %s:%s.\n",
                n, task->host, task->repo_id);

    task->n_fs_objs = (int)n;

    GHashTable *checked_objs = g_hash_table_new_full (g_str_hash, g_str_equal,
                                                      g_free, NULL);

    for (i = 0; i < n; ++i) {
        str = json_array_get (array, i);
        if (!str) {
            seaf_warning ("Invalid JSON response from the server.\n");
            json_decref (array);
            string_list_free (*fs_id_list);
            ret = -1;
            goto out;
        }

        obj_id = json_string_value(str);

        if (g_hash_table_lookup (checked_objs, obj_id)) {
            ++(task->done_fs_objs);
            continue;
        }
        char *key = g_strdup(obj_id);
        g_hash_table_replace (checked_objs, key, key);

        if (!seaf_obj_store_obj_exists (seaf->fs_mgr->obj_store,
                                        task->repo_id, task->repo_version,
                                        obj_id)) {
            *fs_id_list = g_list_prepend (*fs_id_list, g_strdup(obj_id));
        } else if (task->is_clone) {
            gboolean io_error = FALSE;
            gboolean sound;
            sound = seaf_fs_manager_verify_object (seaf->fs_mgr,
                                                   task->repo_id, task->repo_version,
                                                   obj_id, FALSE, &io_error);
            if (!sound && !io_error) {
                *fs_id_list = g_list_prepend (*fs_id_list, g_strdup(obj_id));
            } else {
                ++(task->done_fs_objs);
            }
        } else {
            ++(task->done_fs_objs);
        }
    }

    json_decref (array);
    g_hash_table_destroy (checked_objs);

out:
    g_free (url);
    g_free (rsp_content);
    curl_easy_reset (curl);

    return ret;
}