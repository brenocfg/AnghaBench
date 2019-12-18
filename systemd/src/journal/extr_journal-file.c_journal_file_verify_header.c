#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_10__ {scalar_t__ st_size; } ;
struct TYPE_11__ {scalar_t__ state; scalar_t__ field_hash_table_size; scalar_t__ data_hash_table_size; struct TYPE_11__* header; scalar_t__ seal; int /*<<< orphan*/  compress_lz4; int /*<<< orphan*/  compress_xz; int /*<<< orphan*/  path; int /*<<< orphan*/  tail_entry_realtime; int /*<<< orphan*/  machine_id; scalar_t__ writable; int /*<<< orphan*/  entry_array_offset; int /*<<< orphan*/  tail_object_offset; int /*<<< orphan*/  field_hash_table_offset; int /*<<< orphan*/  data_hash_table_offset; TYPE_1__ last_stat; int /*<<< orphan*/  arena_size; int /*<<< orphan*/  header_size; int /*<<< orphan*/  signature; } ;
typedef  TYPE_2__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EBADMSG ; 
 int /*<<< orphan*/  EBUSY ; 
 int EHOSTDOWN ; 
 int ENODATA ; 
 int EPROTONOSUPPORT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  ETXTBSY ; 
 int /*<<< orphan*/  HEADER_SIGNATURE ; 
 scalar_t__ HEADER_SIZE_MIN ; 
 int /*<<< orphan*/  JOURNAL_HEADER_COMPRESSED_LZ4 (TYPE_2__*) ; 
 int /*<<< orphan*/  JOURNAL_HEADER_COMPRESSED_XZ (TYPE_2__*) ; 
 int /*<<< orphan*/  JOURNAL_HEADER_CONTAINS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ JOURNAL_HEADER_SEALED (TYPE_2__*) ; 
 scalar_t__ STATE_ARCHIVED ; 
 scalar_t__ STATE_OFFLINE ; 
 scalar_t__ STATE_ONLINE ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VALID64 (scalar_t__) ; 
 scalar_t__ _STATE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ le64toh (int /*<<< orphan*/ ) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_entry_arrays ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 
 scalar_t__ warn_wrong_flags (TYPE_2__*,int) ; 

__attribute__((used)) static int journal_file_verify_header(JournalFile *f) {
        uint64_t arena_size, header_size;

        assert(f);
        assert(f->header);

        if (memcmp(f->header->signature, HEADER_SIGNATURE, 8))
                return -EBADMSG;

        /* In both read and write mode we refuse to open files with incompatible
         * flags we don't know. */
        if (warn_wrong_flags(f, false))
                return -EPROTONOSUPPORT;

        /* When open for writing we refuse to open files with compatible flags, too. */
        if (f->writable && warn_wrong_flags(f, true))
                return -EPROTONOSUPPORT;

        if (f->header->state >= _STATE_MAX)
                return -EBADMSG;

        header_size = le64toh(f->header->header_size);

        /* The first addition was n_data, so check that we are at least this large */
        if (header_size < HEADER_SIZE_MIN)
                return -EBADMSG;

        if (JOURNAL_HEADER_SEALED(f->header) && !JOURNAL_HEADER_CONTAINS(f->header, n_entry_arrays))
                return -EBADMSG;

        arena_size = le64toh(f->header->arena_size);

        if (UINT64_MAX - header_size < arena_size || header_size + arena_size > (uint64_t) f->last_stat.st_size)
                return -ENODATA;

        if (le64toh(f->header->tail_object_offset) > header_size + arena_size)
                return -ENODATA;

        if (!VALID64(le64toh(f->header->data_hash_table_offset)) ||
            !VALID64(le64toh(f->header->field_hash_table_offset)) ||
            !VALID64(le64toh(f->header->tail_object_offset)) ||
            !VALID64(le64toh(f->header->entry_array_offset)))
                return -ENODATA;

        if (f->writable) {
                sd_id128_t machine_id;
                uint8_t state;
                int r;

                r = sd_id128_get_machine(&machine_id);
                if (r < 0)
                        return r;

                if (!sd_id128_equal(machine_id, f->header->machine_id))
                        return -EHOSTDOWN;

                state = f->header->state;

                if (state == STATE_ARCHIVED)
                        return -ESHUTDOWN; /* Already archived */
                else if (state == STATE_ONLINE)
                        return log_debug_errno(SYNTHETIC_ERRNO(EBUSY),
                                               "Journal file %s is already online. Assuming unclean closing.",
                                               f->path);
                else if (state != STATE_OFFLINE)
                        return log_debug_errno(SYNTHETIC_ERRNO(EBUSY),
                                               "Journal file %s has unknown state %i.",
                                               f->path, state);

                if (f->header->field_hash_table_size == 0 || f->header->data_hash_table_size == 0)
                        return -EBADMSG;

                /* Don't permit appending to files from the future. Because otherwise the realtime timestamps wouldn't
                 * be strictly ordered in the entries in the file anymore, and we can't have that since it breaks
                 * bisection. */
                if (le64toh(f->header->tail_entry_realtime) > now(CLOCK_REALTIME))
                        return log_debug_errno(SYNTHETIC_ERRNO(ETXTBSY),
                                               "Journal file %s is from the future, refusing to append new data to it that'd be older.",
                                               f->path);
        }

        f->compress_xz = JOURNAL_HEADER_COMPRESSED_XZ(f->header);
        f->compress_lz4 = JOURNAL_HEADER_COMPRESSED_LZ4(f->header);

        f->seal = JOURNAL_HEADER_SEALED(f->header);

        return 0;
}