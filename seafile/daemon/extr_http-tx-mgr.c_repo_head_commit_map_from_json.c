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
typedef  int /*<<< orphan*/  json_t ;
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ json_error_t ;
typedef  scalar_t__ gint64 ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  g_free ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  json_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_loadb (char const*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* json_object_iter (int /*<<< orphan*/ *) ; 
 char* json_object_iter_key (void*) ; 
 void* json_object_iter_next (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * json_object_iter_value (void*) ; 
 char const* json_string_value (int /*<<< orphan*/ *) ; 
 scalar_t__ json_typeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 

__attribute__((used)) static GHashTable *
repo_head_commit_map_from_json (const char *json_str, gint64 len)
{
    json_t *object;
    json_error_t jerror;
    GHashTable *ret;

    object = json_loadb (json_str, (size_t)len, 0, &jerror);
    if (!object) {
        seaf_warning ("Failed to load json: %s\n", jerror.text);
        return NULL;
    }

    ret = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);

    void *iter = json_object_iter (object);
    const char *key;
    json_t *value;
    while (iter) {
        key = json_object_iter_key (iter);
        value = json_object_iter_value (iter);
        if (json_typeof(value) != JSON_STRING) {
            seaf_warning ("Bad json object format when parsing head commit id map.\n");
            g_hash_table_destroy (ret);
            goto out;
        }
        g_hash_table_replace (ret, g_strdup (key), g_strdup(json_string_value(value)));
        iter = json_object_iter_next (object, iter);
    }

out:
    json_decref (object);
    return ret;
}