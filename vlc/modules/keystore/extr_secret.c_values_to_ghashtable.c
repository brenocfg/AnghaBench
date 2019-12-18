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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 unsigned int KEY_MAX ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 scalar_t__* ppsz_keys ; 

__attribute__((used)) static GHashTable *
values_to_ghashtable(const char *const ppsz_values[KEY_MAX])
{
    GHashTable *p_hash = g_hash_table_new_full(g_str_hash, g_str_equal,
                                               NULL, NULL);
    if (!p_hash)
        return NULL;
    for (unsigned int i = 0; i < KEY_MAX; ++i)
    {
        if (ppsz_values[i])
            g_hash_table_insert(p_hash, (gpointer) ppsz_keys[i],
                                (gpointer) ppsz_values[i]);
    }
    return p_hash;
}