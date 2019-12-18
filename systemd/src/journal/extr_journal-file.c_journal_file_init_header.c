#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  h ;
struct TYPE_10__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  seqnum_id; int /*<<< orphan*/  tail_entry_seqnum; int /*<<< orphan*/  compatible_flags; int /*<<< orphan*/  incompatible_flags; int /*<<< orphan*/  header_size; int /*<<< orphan*/  signature; } ;
struct TYPE_9__ {int compress_xz; int compress_lz4; int seal; int /*<<< orphan*/  fd; TYPE_1__* header; } ;
struct TYPE_8__ {int /*<<< orphan*/  tail_entry_seqnum; int /*<<< orphan*/  seqnum_id; } ;
typedef  TYPE_2__ JournalFile ;
typedef  TYPE_3__ Header ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN64 (int) ; 
 int EIO ; 
 int HEADER_COMPATIBLE_SEALED ; 
 int HEADER_INCOMPATIBLE_COMPRESSED_LZ4 ; 
 int HEADER_INCOMPATIBLE_COMPRESSED_XZ ; 
 int /*<<< orphan*/  HEADER_SIGNATURE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int errno ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pwrite (int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int sd_id128_randomize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int journal_file_init_header(JournalFile *f, JournalFile *template) {
        Header h = {};
        ssize_t k;
        int r;

        assert(f);

        memcpy(h.signature, HEADER_SIGNATURE, 8);
        h.header_size = htole64(ALIGN64(sizeof(h)));

        h.incompatible_flags |= htole32(
                f->compress_xz * HEADER_INCOMPATIBLE_COMPRESSED_XZ |
                f->compress_lz4 * HEADER_INCOMPATIBLE_COMPRESSED_LZ4);

        h.compatible_flags = htole32(
                f->seal * HEADER_COMPATIBLE_SEALED);

        r = sd_id128_randomize(&h.file_id);
        if (r < 0)
                return r;

        if (template) {
                h.seqnum_id = template->header->seqnum_id;
                h.tail_entry_seqnum = template->header->tail_entry_seqnum;
        } else
                h.seqnum_id = h.file_id;

        k = pwrite(f->fd, &h, sizeof(h), 0);
        if (k < 0)
                return -errno;

        if (k != sizeof(h))
                return -EIO;

        return 0;
}