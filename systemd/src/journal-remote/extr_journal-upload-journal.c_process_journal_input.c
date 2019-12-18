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
struct TYPE_5__ {int /*<<< orphan*/  entry_state; int /*<<< orphan*/  journal; scalar_t__ uploading; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_CURSOR ; 
 int /*<<< orphan*/  journal_input_callback ; 
 int log_error_errno (int,char*) ; 
 int sd_journal_next_skip (int /*<<< orphan*/ ,int) ; 
 int start_upload (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int process_journal_input(Uploader *u, int skip) {
        int r;

        if (u->uploading)
                return 0;

        r = sd_journal_next_skip(u->journal, skip);
        if (r < 0)
                return log_error_errno(r, "Failed to skip to next entry: %m");
        else if (r < skip)
                return 0;

        /* have data */
        u->entry_state = ENTRY_CURSOR;
        return start_upload(u, journal_input_callback, u);
}