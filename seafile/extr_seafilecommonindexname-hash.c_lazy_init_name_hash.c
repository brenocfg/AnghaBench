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
struct index_state {int name_hash_initialized; int cache_nr; int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_index_entry (struct index_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lazy_init_name_hash(struct index_state *istate)
{
    int nr;

    if (istate->name_hash_initialized)
        return;
    for (nr = 0; nr < istate->cache_nr; nr++)
        hash_index_entry(istate, istate->cache[nr]);
    istate->name_hash_initialized = 1;
}