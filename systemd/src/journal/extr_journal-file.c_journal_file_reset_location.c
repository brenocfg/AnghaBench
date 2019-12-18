#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ current_xor_hash; int /*<<< orphan*/  current_boot_id; scalar_t__ current_monotonic; scalar_t__ current_realtime; scalar_t__ current_seqnum; scalar_t__ current_offset; int /*<<< orphan*/  location_type; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  LOCATION_HEAD ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ ) ; 

void journal_file_reset_location(JournalFile *f) {
        f->location_type = LOCATION_HEAD;
        f->current_offset = 0;
        f->current_seqnum = 0;
        f->current_realtime = 0;
        f->current_monotonic = 0;
        zero(f->current_boot_id);
        f->current_xor_hash = 0;
}