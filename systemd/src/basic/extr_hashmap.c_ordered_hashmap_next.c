#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* value; } ;
struct ordered_hashmap_entry {unsigned int iterate_next; TYPE_1__ p; } ;
typedef  int /*<<< orphan*/  OrderedHashmap ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 struct ordered_hashmap_entry* ordered_bucket_at (int /*<<< orphan*/ *,unsigned int) ; 

void *ordered_hashmap_next(OrderedHashmap *h, const void *key) {
        struct ordered_hashmap_entry *e;
        unsigned hash, idx;

        if (!h)
                return NULL;

        hash = bucket_hash(h, key);
        idx = bucket_scan(h, hash, key);
        if (idx == IDX_NIL)
                return NULL;

        e = ordered_bucket_at(h, idx);
        if (e->iterate_next == IDX_NIL)
                return NULL;
        return ordered_bucket_at(h, e->iterate_next)->p.value;
}