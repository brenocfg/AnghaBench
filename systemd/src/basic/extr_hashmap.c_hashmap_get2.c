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
struct TYPE_2__ {scalar_t__ key; } ;
struct plain_hashmap_entry {void* value; TYPE_1__ b; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 struct plain_hashmap_entry* plain_bucket_at (int /*<<< orphan*/ *,unsigned int) ; 

void *hashmap_get2(Hashmap *h, const void *key, void **key2) {
        struct plain_hashmap_entry *e;
        unsigned hash, idx;

        if (!h)
                return NULL;

        hash = bucket_hash(h, key);
        idx = bucket_scan(h, hash, key);
        if (idx == IDX_NIL)
                return NULL;

        e = plain_bucket_at(h, idx);
        if (key2)
                *key2 = (void*) e->b.key;

        return e->value;
}