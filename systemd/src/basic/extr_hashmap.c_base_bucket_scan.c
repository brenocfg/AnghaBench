#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct hashmap_base_entry {int /*<<< orphan*/  key; } ;
typedef  scalar_t__ dib_raw_t ;
struct TYPE_10__ {TYPE_1__* hash_ops; } ;
struct TYPE_9__ {scalar_t__ (* compare ) (int /*<<< orphan*/ ,void const*) ;} ;
typedef  TYPE_2__ HashmapBase ;

/* Variables and functions */
 scalar_t__ DIB_RAW_FREE ; 
 int IDX_NIL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct hashmap_base_entry* bucket_at (TYPE_2__*,unsigned int) ; 
 unsigned int bucket_calculate_dib (TYPE_2__*,unsigned int,scalar_t__) ; 
 scalar_t__* dib_raw_ptr (TYPE_2__*) ; 
 unsigned int n_buckets (TYPE_2__*) ; 
 unsigned int next_idx (TYPE_2__*,unsigned int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static unsigned base_bucket_scan(HashmapBase *h, unsigned idx, const void *key) {
        struct hashmap_base_entry *e;
        unsigned dib, distance;
        dib_raw_t *dibs = dib_raw_ptr(h);

        assert(idx < n_buckets(h));

        for (distance = 0; ; distance++) {
                if (dibs[idx] == DIB_RAW_FREE)
                        return IDX_NIL;

                dib = bucket_calculate_dib(h, idx, dibs[idx]);

                if (dib < distance)
                        return IDX_NIL;
                if (dib == distance) {
                        e = bucket_at(h, idx);
                        if (h->hash_ops->compare(e->key, key) == 0)
                                return idx;
                }

                idx = next_idx(h, idx);
        }
}