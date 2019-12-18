#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_7__ {int /*<<< orphan*/  n_entries; int /*<<< orphan*/  entry_array_offset; int /*<<< orphan*/  entry_offset; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
typedef  TYPE_2__ Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  OBJECT_DATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int find_data_object_by_boot_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,scalar_t__*) ; 
 int generic_array_bisect_plus_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int journal_file_move_to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_object_monotonic ; 
 int /*<<< orphan*/  test_object_offset ; 

int journal_file_move_to_entry_by_monotonic_for_data(
                JournalFile *f,
                uint64_t data_offset,
                sd_id128_t boot_id,
                uint64_t monotonic,
                direction_t direction,
                Object **ret, uint64_t *offset) {

        Object *o, *d;
        int r;
        uint64_t b, z;

        assert(f);

        /* First, seek by time */
        r = find_data_object_by_boot_id(f, boot_id, &o, &b);
        if (r < 0)
                return r;
        if (r == 0)
                return -ENOENT;

        r = generic_array_bisect_plus_one(f,
                                          le64toh(o->data.entry_offset),
                                          le64toh(o->data.entry_array_offset),
                                          le64toh(o->data.n_entries),
                                          monotonic,
                                          test_object_monotonic,
                                          direction,
                                          NULL, &z, NULL);
        if (r <= 0)
                return r;

        /* And now, continue seeking until we find an entry that
         * exists in both bisection arrays */

        for (;;) {
                Object *qo;
                uint64_t p, q;

                r = journal_file_move_to_object(f, OBJECT_DATA, data_offset, &d);
                if (r < 0)
                        return r;

                r = generic_array_bisect_plus_one(f,
                                                  le64toh(d->data.entry_offset),
                                                  le64toh(d->data.entry_array_offset),
                                                  le64toh(d->data.n_entries),
                                                  z,
                                                  test_object_offset,
                                                  direction,
                                                  NULL, &p, NULL);
                if (r <= 0)
                        return r;

                r = journal_file_move_to_object(f, OBJECT_DATA, b, &o);
                if (r < 0)
                        return r;

                r = generic_array_bisect_plus_one(f,
                                                  le64toh(o->data.entry_offset),
                                                  le64toh(o->data.entry_array_offset),
                                                  le64toh(o->data.n_entries),
                                                  p,
                                                  test_object_offset,
                                                  direction,
                                                  &qo, &q, NULL);

                if (r <= 0)
                        return r;

                if (p == q) {
                        if (ret)
                                *ret = qo;
                        if (offset)
                                *offset = q;

                        return 1;
                }

                z = q;
        }
}