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
struct TYPE_5__ {void* data_hash_table; int /*<<< orphan*/  data_hash_table_size; struct TYPE_5__* header; int /*<<< orphan*/  data_hash_table_offset; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_DATA_HASH_TABLE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int journal_file_move_to (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 

int journal_file_map_data_hash_table(JournalFile *f) {
        uint64_t s, p;
        void *t;
        int r;

        assert(f);
        assert(f->header);

        if (f->data_hash_table)
                return 0;

        p = le64toh(f->header->data_hash_table_offset);
        s = le64toh(f->header->data_hash_table_size);

        r = journal_file_move_to(f,
                                 OBJECT_DATA_HASH_TABLE,
                                 true,
                                 p, s,
                                 &t, NULL);
        if (r < 0)
                return r;

        f->data_hash_table = t;
        return 0;
}