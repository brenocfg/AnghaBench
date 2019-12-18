#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  void* gpointer ;
struct TYPE_7__ {int /*<<< orphan*/  paths; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  paths_lock; int /*<<< orphan*/  active_paths; } ;
typedef  TYPE_2__ SeafSyncManager ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  TYPE_3__ ActivePathsInfo ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_INDENT (int) ; 
 int /*<<< orphan*/ * active_paths_to_json (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,void**,void**) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 char* json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_string (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

char *
seaf_sync_manager_list_active_paths_json (SeafSyncManager *mgr)
{
    json_t *array = NULL, *obj = NULL, *path_array = NULL;
    GHashTableIter iter;
    gpointer key, value;
    char *repo_id;
    ActivePathsInfo *info;
    char *ret = NULL;

    pthread_mutex_lock (&mgr->priv->paths_lock);

    array = json_array ();

    g_hash_table_iter_init (&iter, mgr->priv->active_paths);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        repo_id = key;
        info = value;

        obj = json_object();
        path_array = active_paths_to_json (info->paths);
        json_object_set (obj, "repo_id", json_string(repo_id));
        json_object_set (obj, "paths", path_array);

        json_array_append (array, obj);
    }

    pthread_mutex_unlock (&mgr->priv->paths_lock);

    ret = json_dumps (array, JSON_INDENT(4));
    if (!ret) {
        seaf_warning ("Failed to convert active paths to json\n");
    }

    json_decref (array);

    return ret;
}