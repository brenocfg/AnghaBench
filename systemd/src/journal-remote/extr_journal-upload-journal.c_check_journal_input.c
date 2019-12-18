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
struct TYPE_5__ {int /*<<< orphan*/  journal; scalar_t__ input_event; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int SD_JOURNAL_NOP ; 
 int /*<<< orphan*/  close_journal_input (TYPE_1__*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int process_journal_input (TYPE_1__*,int) ; 
 int sd_journal_process (int /*<<< orphan*/ ) ; 

int check_journal_input(Uploader *u) {
        if (u->input_event) {
                int r;

                r = sd_journal_process(u->journal);
                if (r < 0) {
                        log_error_errno(r, "Failed to process journal: %m");
                        close_journal_input(u);
                        return r;
                }

                if (r == SD_JOURNAL_NOP)
                        return 0;
        }

        return process_journal_input(u, 1);
}