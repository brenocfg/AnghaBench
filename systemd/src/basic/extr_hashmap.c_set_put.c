#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swap_entries {int dummy; } ;
struct hashmap_base_entry {void const* key; } ;
struct TYPE_3__ {struct hashmap_base_entry b; } ;
struct TYPE_4__ {TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 int /*<<< orphan*/  IDX_PUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_2__* bucket_at_swap (struct swap_entries*,int /*<<< orphan*/ ) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 int hashmap_put_boldly (int /*<<< orphan*/ *,unsigned int,struct swap_entries*,int) ; 

int set_put(Set *s, const void *key) {
        struct swap_entries swap;
        struct hashmap_base_entry *e;
        unsigned hash, idx;

        assert(s);

        hash = bucket_hash(s, key);
        idx = bucket_scan(s, hash, key);
        if (idx != IDX_NIL)
                return 0;

        e = &bucket_at_swap(&swap, IDX_PUT)->p.b;
        e->key = key;
        return hashmap_put_boldly(s, hash, &swap, true);
}