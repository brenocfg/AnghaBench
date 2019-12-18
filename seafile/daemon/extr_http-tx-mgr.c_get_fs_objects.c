#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  char* gpointer ;
typedef  int gint64 ;
struct TYPE_22__ {TYPE_1__* fs_mgr; } ;
struct TYPE_21__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * curl; } ;
struct TYPE_20__ {char* data; } ;
struct TYPE_19__ {int repo_id; int /*<<< orphan*/  host; int /*<<< orphan*/  done_fs_objs; int /*<<< orphan*/  error; int /*<<< orphan*/  repo_version; int /*<<< orphan*/  token; int /*<<< orphan*/  use_fileserver_port; } ;
struct TYPE_18__ {int /*<<< orphan*/  object; int /*<<< orphan*/  obj_size; int /*<<< orphan*/  obj_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_2__ ObjectHeader ;
typedef  TYPE_3__ HttpTxTask ;
typedef  TYPE_4__ GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_5__ Connection ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GET_FS_OBJECT_N ; 
 int HTTP_OK ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_SERVER ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_WRITE_LOCAL_DATA ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_4__* g_list_delete_link (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* g_list_prepend (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  handle_curl_errors (TYPE_3__*,int) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_3__*,int) ; 
 scalar_t__ http_post (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int,int*,char**,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,int,int /*<<< orphan*/ ,int) ; 
 int seaf_obj_store_write_obj (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
get_fs_objects (HttpTxTask *task, Connection *conn, GList **fs_list)
{
    json_t *array;
    char *obj_id;
    int n_sent = 0;
    char *data = NULL;
    int len;
    CURL *curl;
    char *url = NULL;
    int status;
    char *rsp_content = NULL;
    gint64 rsp_size;
    int ret = 0;
    GHashTable *requested;

    /* Convert object id list to JSON format. */

    requested = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

    array = json_array ();

    while (*fs_list != NULL) {
        obj_id = (*fs_list)->data;
        json_array_append_new (array, json_string(obj_id));

        *fs_list = g_list_delete_link (*fs_list, *fs_list);

        g_hash_table_replace (requested, obj_id, obj_id);

        if (++n_sent >= GET_FS_OBJECT_N)
            break;
    }

    seaf_debug ("Requesting %d fs objects from %s:%s.\n",
                n_sent, task->host, task->repo_id);

    data = json_dumps (array, 0);
    len = strlen(data);
    json_decref (array);

    /* Send fs object id list. */

    curl = conn->curl;

    if (!task->use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/pack-fs/", task->host, task->repo_id);
    else
        url = g_strdup_printf ("%s/repo/%s/pack-fs/", task->host, task->repo_id);

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

    /* Save received fs objects. */

    int n_recv = 0;
    char *p = rsp_content;
    ObjectHeader *hdr = (ObjectHeader *)p;
    char recv_obj_id[41];
    int n = 0;
    int size;
    int rc;
    while (n < rsp_size) {
        memcpy (recv_obj_id, hdr->obj_id, 40);
        recv_obj_id[40] = 0;
        size = ntohl (hdr->obj_size);
        if (n + sizeof(ObjectHeader) + size > rsp_size) {
            seaf_warning ("Incomplete object package received for repo %.8s.\n",
                          task->repo_id);
            task->error = SYNC_ERROR_ID_SERVER;
            ret = -1;
            goto out;
        }

        ++n_recv;

        rc = seaf_obj_store_write_obj (seaf->fs_mgr->obj_store,
                                       task->repo_id, task->repo_version,
                                       recv_obj_id,
                                       hdr->object,
                                       size, FALSE);
        if (rc < 0) {
            seaf_warning ("Failed to write fs object %s in repo %.8s.\n",
                          recv_obj_id, task->repo_id);
            task->error = SYNC_ERROR_ID_WRITE_LOCAL_DATA;
            ret = -1;
            goto out;
        }

        g_hash_table_remove (requested, recv_obj_id);

        ++(task->done_fs_objs);

        p += (sizeof(ObjectHeader) + size);
        n += (sizeof(ObjectHeader) + size);
        hdr = (ObjectHeader *)p;
    }

    seaf_debug ("Received %d fs objects from %s:%s.\n",
                n_recv, task->host, task->repo_id);

    /* The server may not return all the objects we requested.
     * So we need to add back the remaining object ids into fs_list.
     */
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter, requested);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        obj_id = key;
        *fs_list = g_list_prepend (*fs_list, g_strdup(obj_id));
    }
    g_hash_table_destroy (requested);

out:
    g_free (url);
    g_free (data);
    g_free (rsp_content);
    curl_easy_reset (curl);

    return ret;
}