#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct swap_entries {int dummy; } ;
struct TYPE_4__ {void const* key; } ;
struct plain_hashmap_entry {void* value; TYPE_1__ b; } ;
struct TYPE_6__ {void* key; } ;
struct TYPE_5__ {struct plain_hashmap_entry p; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 unsigned int IDX_NIL ; 
 int /*<<< orphan*/  IDX_PUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 TYPE_3__* bucket_at (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* bucket_at_swap (struct swap_entries*,int /*<<< orphan*/ ) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 int hashmap_put_boldly (int /*<<< orphan*/ *,unsigned int,struct swap_entries*,int) ; 
 unsigned int prev_idx (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  remove_entry (int /*<<< orphan*/ *,unsigned int) ; 

int hashmap_remove_and_replace(Hashmap *h, const void *old_key, const void *new_key, void *value) {
        struct swap_entries swap;
        struct plain_hashmap_entry *e;
        unsigned old_hash, new_hash, idx_old, idx_new;

        if (!h)
                return -ENOENT;

        old_hash = bucket_hash(h, old_key);
        idx_old = bucket_scan(h, old_hash, old_key);
        if (idx_old == IDX_NIL)
                return -ENOENT;

        old_key = bucket_at(HASHMAP_BASE(h), idx_old)->key;

        new_hash = bucket_hash(h, new_key);
        idx_new = bucket_scan(h, new_hash, new_key);
        if (idx_new != IDX_NIL)
                if (idx_old != idx_new) {
                        remove_entry(h, idx_new);
                        /* Compensate for a possible backward shift. */
                        if (old_key != bucket_at(HASHMAP_BASE(h), idx_old)->key)
                                idx_old = prev_idx(HASHMAP_BASE(h), idx_old);
                        assert(old_key == bucket_at(HASHMAP_BASE(h), idx_old)->key);
                }

        remove_entry(h, idx_old);

        e = &bucket_at_swap(&swap, IDX_PUT)->p;
        e->b.key = new_key;
        e->value = value;
        assert_se(hashmap_put_boldly(h, new_hash, &swap, false) == 1);

        return 0;
}