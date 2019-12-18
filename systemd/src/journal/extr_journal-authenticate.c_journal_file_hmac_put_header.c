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
struct TYPE_7__ {TYPE_1__* header; int /*<<< orphan*/  hmac; int /*<<< orphan*/  seal; } ;
struct TYPE_6__ {int /*<<< orphan*/  data_hash_table_offset; int /*<<< orphan*/  seqnum_id; int /*<<< orphan*/  file_id; int /*<<< orphan*/ * signature; } ;
typedef  TYPE_2__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  Header ; 
 int /*<<< orphan*/  arena_size ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  boot_id ; 
 int /*<<< orphan*/  data_hash_table_offset ; 
 int /*<<< orphan*/  file_id ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int journal_file_hmac_start (TYPE_2__*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqnum_id ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  tail_object_offset ; 

int journal_file_hmac_put_header(JournalFile *f) {
        int r;

        assert(f);

        if (!f->seal)
                return 0;

        r = journal_file_hmac_start(f);
        if (r < 0)
                return r;

        /* All but state+reserved, boot_id, arena_size,
         * tail_object_offset, n_objects, n_entries,
         * tail_entry_seqnum, head_entry_seqnum, entry_array_offset,
         * head_entry_realtime, tail_entry_realtime,
         * tail_entry_monotonic, n_data, n_fields, n_tags,
         * n_entry_arrays. */

        gcry_md_write(f->hmac, f->header->signature, offsetof(Header, state) - offsetof(Header, signature));
        gcry_md_write(f->hmac, &f->header->file_id, offsetof(Header, boot_id) - offsetof(Header, file_id));
        gcry_md_write(f->hmac, &f->header->seqnum_id, offsetof(Header, arena_size) - offsetof(Header, seqnum_id));
        gcry_md_write(f->hmac, &f->header->data_hash_table_offset, offsetof(Header, tail_object_offset) - offsetof(Header, data_hash_table_offset));

        return 0;
}