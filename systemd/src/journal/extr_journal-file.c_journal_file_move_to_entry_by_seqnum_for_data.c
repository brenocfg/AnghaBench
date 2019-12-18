#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_6__ {int /*<<< orphan*/  n_entries; int /*<<< orphan*/  entry_array_offset; int /*<<< orphan*/  entry_offset; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
typedef  TYPE_2__ Object ;
typedef  int /*<<< orphan*/  JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_DATA ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int generic_array_bisect_plus_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int journal_file_move_to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_object_seqnum ; 

int journal_file_move_to_entry_by_seqnum_for_data(
                JournalFile *f,
                uint64_t data_offset,
                uint64_t seqnum,
                direction_t direction,
                Object **ret, uint64_t *offset) {

        Object *d;
        int r;

        assert(f);

        r = journal_file_move_to_object(f, OBJECT_DATA, data_offset, &d);
        if (r < 0)
                return r;

        return generic_array_bisect_plus_one(f,
                                             le64toh(d->data.entry_offset),
                                             le64toh(d->data.entry_array_offset),
                                             le64toh(d->data.n_entries),
                                             seqnum,
                                             test_object_seqnum,
                                             direction,
                                             ret, offset, NULL);
}