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
struct hashmap_base_entry {scalar_t__ key; } ;
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 struct hashmap_base_entry* bucket_at (int /*<<< orphan*/ *,unsigned int) ; 
 void* entry_value (int /*<<< orphan*/ *,struct hashmap_base_entry*) ; 
 unsigned int find_first_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_entry (int /*<<< orphan*/ *,unsigned int) ; 

void *internal_hashmap_first_key_and_value(HashmapBase *h, bool remove, void **ret_key) {
        struct hashmap_base_entry *e;
        void *key, *data;
        unsigned idx;

        idx = find_first_entry(h);
        if (idx == IDX_NIL) {
                if (ret_key)
                        *ret_key = NULL;
                return NULL;
        }

        e = bucket_at(h, idx);
        key = (void*) e->key;
        data = entry_value(h, e);

        if (remove)
                remove_entry(h, idx);

        if (ret_key)
                *ret_key = key;

        return data;
}