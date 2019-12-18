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
struct hashmap_base_entry {int dummy; } ;
typedef  int /*<<< orphan*/  HashmapBase ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 struct hashmap_base_entry* bucket_at (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 void* entry_value (int /*<<< orphan*/ *,struct hashmap_base_entry*) ; 
 int /*<<< orphan*/  remove_entry (int /*<<< orphan*/ *,unsigned int) ; 

void *internal_hashmap_remove_value(HashmapBase *h, const void *key, void *value) {
        struct hashmap_base_entry *e;
        unsigned hash, idx;

        if (!h)
                return NULL;

        hash = bucket_hash(h, key);
        idx = bucket_scan(h, hash, key);
        if (idx == IDX_NIL)
                return NULL;

        e = bucket_at(h, idx);
        if (entry_value(h, e) != value)
                return NULL;

        remove_entry(h, idx);

        return value;
}