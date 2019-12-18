#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  json_t ;
typedef  char* gpointer ;
typedef  size_t SyncStatus ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,char**,char**) ; 
 int /*<<< orphan*/ * json_array () ; 
 int /*<<< orphan*/  json_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object () ; 
 int /*<<< orphan*/  json_object_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  json_string (char*) ; 
 char** path_status_tbl ; 

__attribute__((used)) static json_t *
active_paths_to_json (GHashTable *paths)
{
    json_t *array = NULL, *obj = NULL;
    GHashTableIter iter;
    gpointer key, value;
    char *path;
    SyncStatus status;

    array = json_array ();

    g_hash_table_iter_init (&iter, paths);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        path = key;
        status = (SyncStatus)value;

        obj = json_object ();
        json_object_set (obj, "path", json_string(path));
        json_object_set (obj, "status", json_string(path_status_tbl[status]));

        json_array_append (array, obj);
    }

    return array;
}