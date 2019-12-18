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
struct index_state {int cache_nr; int cache_alloc; int cache_changed; scalar_t__ cache; } ;
struct cache_entry {int dummy; } ;
typedef  int /*<<< orphan*/  ce ;

/* Variables and functions */
 int ADD_CACHE_JUST_APPEND ; 
 int add_index_entry_with_check (struct index_state*,struct cache_entry*,int) ; 
 int alloc_nr (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 scalar_t__ realloc (scalar_t__,int) ; 
 int /*<<< orphan*/  set_index_entry (struct index_state*,int,struct cache_entry*) ; 

int add_index_entry(struct index_state *istate, struct cache_entry *ce, int option)
{
    int pos;

    if (option & ADD_CACHE_JUST_APPEND)
        pos = istate->cache_nr;
    else {
        int ret;
        ret = add_index_entry_with_check(istate, ce, option);
        if (ret <= 0)
            return ret;
        pos = ret - 1;
    }

    /* Make sure the array is big enough .. */
    if (istate->cache_nr == istate->cache_alloc) {
        istate->cache_alloc = alloc_nr(istate->cache_alloc);
        istate->cache = realloc(istate->cache,
                                istate->cache_alloc * sizeof(struct cache_entry *));
    }

    /* Add it in.. */
    istate->cache_nr++;
    if (istate->cache_nr > pos + 1)
        memmove(istate->cache + pos + 1,
                istate->cache + pos,
                (istate->cache_nr - pos - 1) * sizeof(ce));
    set_index_entry(istate, pos, ce);
    istate->cache_changed = 1;
    return 0;
}