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
struct plain_hashmap_entry {void* value; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int ENOENT ; 
 unsigned int IDX_NIL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 unsigned int bucket_hash (int /*<<< orphan*/ *,void const*) ; 
 unsigned int bucket_scan (int /*<<< orphan*/ *,unsigned int,void const*) ; 
 int /*<<< orphan*/  hashmap_set_dirty (int /*<<< orphan*/ *) ; 
 struct plain_hashmap_entry* plain_bucket_at (int /*<<< orphan*/ *,unsigned int) ; 

int hashmap_update(Hashmap *h, const void *key, void *value) {
        struct plain_hashmap_entry *e;
        unsigned hash, idx;

        assert(h);

        hash = bucket_hash(h, key);
        idx = bucket_scan(h, hash, key);
        if (idx == IDX_NIL)
                return -ENOENT;

        e = plain_bucket_at(h, idx);
        e->value = value;
        hashmap_set_dirty(h);

        return 0;
}