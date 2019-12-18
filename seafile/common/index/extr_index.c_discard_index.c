#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nsec; scalar_t__ sec; } ;
struct index_state {int cache_nr; scalar_t__ initialized; int /*<<< orphan*/ * alloc; int /*<<< orphan*/ * cache; int /*<<< orphan*/  i_name_hash; int /*<<< orphan*/  name_hash; scalar_t__ name_hash_initialized; TYPE_1__ timestamp; scalar_t__ cache_changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 

int discard_index(struct index_state *istate)
{
    int i;
    for (i = 0; i < istate->cache_nr; ++i)
        cache_entry_free (istate->cache[i]);

    istate->cache_nr = 0;
    istate->cache_changed = 0;
    istate->timestamp.sec = 0;
    istate->timestamp.nsec = 0;
    istate->name_hash_initialized = 0;
    g_hash_table_destroy (istate->name_hash);
#if defined WIN32 || defined __APPLE__
    g_hash_table_destroy (istate->i_name_hash);
#endif
    /* cache_tree_free(&(istate->cache_tree)); */
    /* free(istate->alloc); */
    free(istate->cache);
    istate->alloc = NULL;
    istate->initialized = 0;

    /* no need to throw away allocated active_cache */
    return 0;
}