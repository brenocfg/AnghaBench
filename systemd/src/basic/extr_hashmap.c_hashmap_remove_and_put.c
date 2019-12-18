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
struct TYPE_3__ {void const* key; } ;
struct plain_hashmap_entry {void* value; TYPE_1__ b; } ;
struct TYPE_4__ {struct plain_hashmap_entry p; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 unsigned int IDX_NIL ; 
 int /*<<< orphan*/  IDX_PUT ; 
 int /*<<< orphan*/  assert_se (int) ; 
 TYPE_2__* bucket_at_swap (struct swap_entries*,int /*<<< orphan*/ ) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 int hashmap_put_boldly (int /*<<< orphan*/ *,unsigned int,struct swap_entries*,int) ; 
 int /*<<< orphan*/  remove_entry (int /*<<< orphan*/ *,unsigned int) ; 

int hashmap_remove_and_put(Hashmap *h, const void *old_key, const void *new_key, void *value) {
        struct swap_entries swap;
        struct plain_hashmap_entry *e;
        unsigned old_hash, new_hash, idx;

        if (!h)
                return -ENOENT;

        old_hash = bucket_hash(h, old_key);
        idx = bucket_scan(h, old_hash, old_key);
        if (idx == IDX_NIL)
                return -ENOENT;

        new_hash = bucket_hash(h, new_key);
        if (bucket_scan(h, new_hash, new_key) != IDX_NIL)
                return -EEXIST;

        remove_entry(h, idx);

        e = &bucket_at_swap(&swap, IDX_PUT)->p;
        e->b.key = new_key;
        e->value = value;
        assert_se(hashmap_put_boldly(h, new_hash, &swap, false) == 1);

        return 0;
}