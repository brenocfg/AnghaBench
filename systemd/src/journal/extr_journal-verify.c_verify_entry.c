#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_18__ {int /*<<< orphan*/  hash; } ;
struct TYPE_17__ {TYPE_1__* items; } ;
struct TYPE_19__ {TYPE_3__ data; int /*<<< orphan*/  mmap; TYPE_2__ entry; } ;
struct TYPE_16__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  object_offset; } ;
typedef  TYPE_4__ Object ;
typedef  TYPE_4__ MMapFileDescriptor ;
typedef  TYPE_4__ JournalFile ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  OBJECT_DATA ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  contains_uint64 (int /*<<< orphan*/ ,TYPE_4__*,size_t,size_t) ; 
 int data_object_in_hash_table (TYPE_4__*,size_t,size_t) ; 
 int /*<<< orphan*/  error (size_t,char*) ; 
 size_t journal_file_entry_n_items (TYPE_4__*) ; 
 int journal_file_move_to_object (TYPE_4__*,int /*<<< orphan*/ ,size_t,TYPE_4__**) ; 
 size_t le64toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_entry(
                JournalFile *f,
                Object *o, uint64_t p,
                MMapFileDescriptor *cache_data_fd, uint64_t n_data) {

        uint64_t i, n;
        int r;

        assert(f);
        assert(o);
        assert(cache_data_fd);

        n = journal_file_entry_n_items(o);
        for (i = 0; i < n; i++) {
                uint64_t q, h;
                Object *u;

                q = le64toh(o->entry.items[i].object_offset);
                h = le64toh(o->entry.items[i].hash);

                if (!contains_uint64(f->mmap, cache_data_fd, n_data, q)) {
                        error(p, "Invalid data object of entry");
                        return -EBADMSG;
                }

                r = journal_file_move_to_object(f, OBJECT_DATA, q, &u);
                if (r < 0)
                        return r;

                if (le64toh(u->data.hash) != h) {
                        error(p, "Hash mismatch for data object of entry");
                        return -EBADMSG;
                }

                r = data_object_in_hash_table(f, h, q);
                if (r < 0)
                        return r;
                if (r == 0) {
                        error(p, "Data object missing from hash table");
                        return -EBADMSG;
                }
        }

        return 0;
}