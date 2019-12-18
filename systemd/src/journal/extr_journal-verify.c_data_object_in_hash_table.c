#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_15__ {TYPE_1__* data_hash_table; TYPE_3__* header; } ;
struct TYPE_12__ {int /*<<< orphan*/  next_hash_offset; } ;
struct TYPE_14__ {TYPE_2__ data; } ;
struct TYPE_13__ {int /*<<< orphan*/  data_hash_table_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  head_hash_offset; } ;
typedef  TYPE_4__ Object ;
typedef  TYPE_5__ JournalFile ;
typedef  int /*<<< orphan*/  HashItem ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_DATA ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int journal_file_map_data_hash_table (TYPE_5__*) ; 
 int journal_file_move_to_object (TYPE_5__*,int /*<<< orphan*/ ,size_t,TYPE_4__**) ; 
 int le64toh (int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 

__attribute__((used)) static int data_object_in_hash_table(JournalFile *f, uint64_t hash, uint64_t p) {
        uint64_t n, h, q;
        int r;
        assert(f);

        n = le64toh(f->header->data_hash_table_size) / sizeof(HashItem);
        if (n <= 0)
                return 0;

        r = journal_file_map_data_hash_table(f);
        if (r < 0)
                return log_error_errno(r, "Failed to map data hash table: %m");

        h = hash % n;

        q = le64toh(f->data_hash_table[h].head_hash_offset);
        while (q != 0) {
                Object *o;

                if (p == q)
                        return 1;

                r = journal_file_move_to_object(f, OBJECT_DATA, q, &o);
                if (r < 0)
                        return r;

                q = le64toh(o->data.next_hash_offset);
        }

        return 0;
}