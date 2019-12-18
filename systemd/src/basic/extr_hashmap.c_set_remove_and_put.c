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

int set_remove_and_put(Set *s, const void *old_key, const void *new_key) {
        struct swap_entries swap;
        struct hashmap_base_entry *e;
        unsigned old_hash, new_hash, idx;

        if (!s)
                return -ENOENT;

        old_hash = bucket_hash(s, old_key);
        idx = bucket_scan(s, old_hash, old_key);
        if (idx == IDX_NIL)
                return -ENOENT;

        new_hash = bucket_hash(s, new_key);
        if (bucket_scan(s, new_hash, new_key) != IDX_NIL)
                return -EEXIST;

        remove_entry(s, idx);

        e = &bucket_at_swap(&swap, IDX_PUT)->p.b;
        e->key = new_key;
        assert_se(hashmap_put_boldly(s, new_hash, &swap, false) == 1);

        return 0;
}