#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ head_entry_seqnum; struct TYPE_4__* header; void* tail_entry_seqnum; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* htole64 (scalar_t__) ; 
 scalar_t__ le64toh (void*) ; 

__attribute__((used)) static uint64_t journal_file_entry_seqnum(JournalFile *f, uint64_t *seqnum) {
        uint64_t r;

        assert(f);
        assert(f->header);

        r = le64toh(f->header->tail_entry_seqnum) + 1;

        if (seqnum) {
                /* If an external seqnum counter was passed, we update
                 * both the local and the external one, and set it to
                 * the maximum of both */

                if (*seqnum + 1 > r)
                        r = *seqnum + 1;

                *seqnum = r;
        }

        f->header->tail_entry_seqnum = htole64(r);

        if (f->header->head_entry_seqnum == 0)
                f->header->head_entry_seqnum = htole64(r);

        return r;
}