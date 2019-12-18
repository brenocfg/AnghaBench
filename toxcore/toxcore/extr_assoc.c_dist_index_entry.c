#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_6__ {TYPE_2__* list; } ;
typedef  TYPE_1__ candidates_bucket ;
typedef  size_t bucket_t ;
struct TYPE_8__ {size_t candidates_bucket_count; size_t candidates_bucket_size; TYPE_1__* candidates; } ;
struct TYPE_7__ {scalar_t__ hash; } ;
typedef  TYPE_2__ Client_entry ;
typedef  TYPE_3__ Assoc ;

/* Variables and functions */
 size_t DISTANCE_INDEX_INDEX_MASK ; 

__attribute__((used)) static Client_entry *dist_index_entry(Assoc *assoc, uint64_t dist_ind)
{
    if ((dist_ind & DISTANCE_INDEX_INDEX_MASK) == DISTANCE_INDEX_INDEX_MASK)
        return NULL;

    size_t total = assoc->candidates_bucket_count * assoc->candidates_bucket_size;
    uint32_t index = dist_ind & DISTANCE_INDEX_INDEX_MASK;

    if (index < total) {
        bucket_t b_id = index / assoc->candidates_bucket_size;
        candidates_bucket *cnd_bckt = &assoc->candidates[b_id];
        size_t b_ix = index % assoc->candidates_bucket_size;
        Client_entry *entry = &cnd_bckt->list[b_ix];

        if (entry->hash)
            return entry;
    }

    return NULL;
}