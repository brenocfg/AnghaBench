#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  direction_t ;
struct TYPE_5__ {int /*<<< orphan*/  n_entries; struct TYPE_5__* header; int /*<<< orphan*/  entry_array_offset; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int generic_array_bisect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_object_realtime ; 

int journal_file_move_to_entry_by_realtime(
                JournalFile *f,
                uint64_t realtime,
                direction_t direction,
                Object **ret,
                uint64_t *offset) {
        assert(f);
        assert(f->header);

        return generic_array_bisect(f,
                                    le64toh(f->header->entry_array_offset),
                                    le64toh(f->header->n_entries),
                                    realtime,
                                    test_object_realtime,
                                    direction,
                                    ret, offset, NULL);
}