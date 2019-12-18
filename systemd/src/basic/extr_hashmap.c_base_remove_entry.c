#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct ordered_hashmap_entry {scalar_t__ iterate_next; scalar_t__ iterate_previous; } ;
typedef  scalar_t__ dib_raw_t ;
struct TYPE_14__ {unsigned int last_rem_idx; int /*<<< orphan*/  rem_count; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_1__ debug; } ;
struct TYPE_15__ {scalar_t__ iterate_list_tail; unsigned int iterate_list_head; } ;
typedef  TYPE_2__ OrderedHashmap ;
typedef  TYPE_3__ HashmapBase ;

/* Variables and functions */
 scalar_t__ DIB_RAW_FREE ; 
 scalar_t__ HASHMAP_TYPE_ORDERED ; 
 scalar_t__ IDX_NIL ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  base_set_dirty (TYPE_3__*) ; 
 unsigned int bucket_calculate_dib (TYPE_3__*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  bucket_mark_free (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  bucket_move_entry (TYPE_3__*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  bucket_set_dib (TYPE_3__*,unsigned int,unsigned int) ; 
 scalar_t__* dib_raw_ptr (TYPE_3__*) ; 
 int /*<<< orphan*/  n_entries_dec (TYPE_3__*) ; 
 unsigned int next_idx (TYPE_3__*,unsigned int) ; 
 struct ordered_hashmap_entry* ordered_bucket_at (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void base_remove_entry(HashmapBase *h, unsigned idx) {
        unsigned left, right, prev, dib;
        dib_raw_t raw_dib, *dibs;

        dibs = dib_raw_ptr(h);
        assert(dibs[idx] != DIB_RAW_FREE);

#if ENABLE_DEBUG_HASHMAP
        h->debug.rem_count++;
        h->debug.last_rem_idx = idx;
#endif

        left = idx;
        /* Find the stop bucket ("right"). It is either free or has DIB == 0. */
        for (right = next_idx(h, left); ; right = next_idx(h, right)) {
                raw_dib = dibs[right];
                if (IN_SET(raw_dib, 0, DIB_RAW_FREE))
                        break;

                /* The buckets are not supposed to be all occupied and with DIB > 0.
                 * That would mean we could make everyone better off by shifting them
                 * backward. This scenario is impossible. */
                assert(left != right);
        }

        if (h->type == HASHMAP_TYPE_ORDERED) {
                OrderedHashmap *lh = (OrderedHashmap*) h;
                struct ordered_hashmap_entry *le = ordered_bucket_at(lh, idx);

                if (le->iterate_next != IDX_NIL)
                        ordered_bucket_at(lh, le->iterate_next)->iterate_previous = le->iterate_previous;
                else
                        lh->iterate_list_tail = le->iterate_previous;

                if (le->iterate_previous != IDX_NIL)
                        ordered_bucket_at(lh, le->iterate_previous)->iterate_next = le->iterate_next;
                else
                        lh->iterate_list_head = le->iterate_next;
        }

        /* Now shift all buckets in the interval (left, right) one step backwards */
        for (prev = left, left = next_idx(h, left); left != right;
             prev = left, left = next_idx(h, left)) {
                dib = bucket_calculate_dib(h, left, dibs[left]);
                assert(dib != 0);
                bucket_move_entry(h, NULL, left, prev);
                bucket_set_dib(h, prev, dib - 1);
        }

        bucket_mark_free(h, prev);
        n_entries_dec(h);
        base_set_dirty(h);
}