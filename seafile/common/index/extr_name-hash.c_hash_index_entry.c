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
struct index_state {int /*<<< orphan*/  name_hash; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/ * next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CE_HASHED ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 unsigned int hash_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void** insert_hash (unsigned int,struct cache_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hash_index_entry(struct index_state *istate, struct cache_entry *ce)
{
    void **pos;
    unsigned int hash;

    if (ce->ce_flags & CE_HASHED)
        return;
    ce->ce_flags |= CE_HASHED;
    ce->next = NULL;
    hash = hash_name(ce->name, ce_namelen(ce));
    pos = insert_hash(hash, ce, &istate->name_hash);
    if (pos) {
        ce->next = *pos;
        *pos = ce;
    }

    /* if (ignore_case) */
    /*  hash_index_entry_directories(istate, ce); */
}