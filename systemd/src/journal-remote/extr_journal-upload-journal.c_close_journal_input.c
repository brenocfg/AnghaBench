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
struct TYPE_4__ {scalar_t__ timeout; int /*<<< orphan*/ * journal; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  sd_journal_close (int /*<<< orphan*/ *) ; 

void close_journal_input(Uploader *u) {
        assert(u);

        if (u->journal) {
                log_debug("Closing journal input.");

                sd_journal_close(u->journal);
                u->journal = NULL;
        }
        u->timeout = 0;
}