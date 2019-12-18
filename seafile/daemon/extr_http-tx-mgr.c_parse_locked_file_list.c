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
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int /*<<< orphan*/  g_free ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_array_get (int /*<<< orphan*/ *,size_t) ; 
 size_t json_array_size (int /*<<< orphan*/ *) ; 
 scalar_t__ json_integer_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * json_object_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  json_string_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GHashTable *
parse_locked_file_list (json_t *array)
{
    GHashTable *ret = NULL;
    size_t n, i;
    json_t *obj, *string, *integer;

    ret = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
    if (!ret) {
        return NULL;
    }

    n = json_array_size (array);
    for (i = 0; i < n; ++i) {
        obj = json_array_get (array, i);
        string = json_object_get (obj, "path");
        if (!string) {
            g_hash_table_destroy (ret);
            return NULL;
        }
        integer = json_object_get (obj, "by_me");
        if (!integer) {
            g_hash_table_destroy (ret);
            return NULL;
        }
        g_hash_table_insert (ret,
                             g_strdup(json_string_value(string)),
                             (void*)(long)json_integer_value(integer));
    }

    return ret;
}