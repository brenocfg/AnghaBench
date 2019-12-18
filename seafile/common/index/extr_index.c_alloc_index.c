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
struct index_state {int initialized; int name_hash_initialized; void* i_name_hash; void* name_hash; int /*<<< orphan*/  cache_alloc; int /*<<< orphan*/  cache; int /*<<< orphan*/  cache_nr; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_free ; 
 void* g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 

__attribute__((used)) static void alloc_index (struct index_state *istate)
{
    istate->cache_alloc = alloc_nr(istate->cache_nr);
    istate->cache = calloc(istate->cache_alloc, sizeof(struct cache_entry *));
    istate->name_hash = g_hash_table_new_full (g_str_hash, g_str_equal,
                                               g_free, NULL);
#if defined WIN32 || defined __APPLE__
    istate->i_name_hash = g_hash_table_new_full (g_str_hash, g_str_equal,
                                                 g_free, NULL);
#endif
    istate->initialized = 1;
    istate->name_hash_initialized = 1;
}