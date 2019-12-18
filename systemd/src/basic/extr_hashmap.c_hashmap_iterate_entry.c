#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ put_count; int rem_count; scalar_t__ last_rem_idx; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_1__ debug; } ;
struct TYPE_10__ {int idx; scalar_t__ put_count; int rem_count; scalar_t__ prev_idx; } ;
typedef  int /*<<< orphan*/  OrderedHashmap ;
typedef  TYPE_2__ Iterator ;
typedef  TYPE_3__ HashmapBase ;

/* Variables and functions */
 scalar_t__ HASHMAP_TYPE_ORDERED ; 
 scalar_t__ IDX_FIRST ; 
 int IDX_NIL ; 
 int /*<<< orphan*/  assert (int) ; 
 int hashmap_iterate_in_insertion_order (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int hashmap_iterate_in_internal_order (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static unsigned hashmap_iterate_entry(HashmapBase *h, Iterator *i) {
        if (!h) {
                i->idx = IDX_NIL;
                return IDX_NIL;
        }

#if ENABLE_DEBUG_HASHMAP
        if (i->idx == IDX_FIRST) {
                i->put_count = h->debug.put_count;
                i->rem_count = h->debug.rem_count;
        } else {
                /* While iterating, must not add any new entries */
                assert(i->put_count == h->debug.put_count);
                /* ... or remove entries other than the current one */
                assert(i->rem_count == h->debug.rem_count ||
                       (i->rem_count == h->debug.rem_count - 1 &&
                        i->prev_idx == h->debug.last_rem_idx));
                /* Reset our removals counter */
                i->rem_count = h->debug.rem_count;
        }
#endif

        return h->type == HASHMAP_TYPE_ORDERED ? hashmap_iterate_in_insertion_order((OrderedHashmap*) h, i)
                                               : hashmap_iterate_in_internal_order(h, i);
}