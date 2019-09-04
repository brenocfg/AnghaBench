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
struct index_state {int cache_changed; int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_free (struct cache_entry*) ; 
 int /*<<< orphan*/  memmove (struct cache_entry**,struct cache_entry**,int) ; 
 int /*<<< orphan*/  remove_name_hash (struct index_state*,struct cache_entry*) ; 

int remove_index_entry_at(struct index_state *istate, int pos)
{
    struct cache_entry *ce = istate->cache[pos];

    /* record_resolve_undo(istate, ce); */
    remove_name_hash(istate, ce);
    cache_entry_free (ce);
    istate->cache_changed = 1;
    istate->cache_nr--;
    if (pos >= istate->cache_nr)
        return 0;
    memmove(istate->cache + pos,
            istate->cache + pos + 1,
            (istate->cache_nr - pos) * sizeof(struct cache_entry *));
    return 1;
}