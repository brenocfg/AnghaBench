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
struct plain_hashmap_entry {TYPE_1__ b; void* value; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 unsigned int IDX_NIL ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 struct plain_hashmap_entry* plain_bucket_at (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  remove_entry (int /*<<< orphan*/ *,unsigned int) ; 

void *hashmap_remove2(Hashmap *h, const void *key, void **rkey) {
        struct plain_hashmap_entry *e;
        unsigned hash, idx;
        void *data;

        if (!h) {
                if (rkey)
                        *rkey = NULL;
                return NULL;
        }

        hash = bucket_hash(h, key);
        idx = bucket_scan(h, hash, key);
        if (idx == IDX_NIL) {
                if (rkey)
                        *rkey = NULL;
                return NULL;
        }

        e = plain_bucket_at(h, idx);
        data = e->value;
        if (rkey)
                *rkey = (void*) e->b.key;

        remove_entry(h, idx);

        return data;
}