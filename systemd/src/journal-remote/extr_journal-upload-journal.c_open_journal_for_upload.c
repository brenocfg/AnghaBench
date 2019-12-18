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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  sd_journal ;
struct TYPE_5__ {int timeout; int /*<<< orphan*/  input_event; int /*<<< orphan*/  events; int /*<<< orphan*/ * journal; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int JOURNAL_UPLOAD_POLL_TIMEOUT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dispatch_journal_input ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int log_error_errno (int,char*,...) ; 
 int process_journal_input (TYPE_1__*,int) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_journal_get_events (int /*<<< orphan*/ *) ; 
 int sd_journal_get_fd (int /*<<< orphan*/ *) ; 
 int sd_journal_reliable_fd (int /*<<< orphan*/ *) ; 
 int sd_journal_seek_cursor (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  sd_journal_set_data_threshold (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int open_journal_for_upload(Uploader *u,
                            sd_journal *j,
                            const char *cursor,
                            bool after_cursor,
                            bool follow) {
        int fd, r, events;

        u->journal = j;

        sd_journal_set_data_threshold(j, 0);

        if (follow) {
                fd = sd_journal_get_fd(j);
                if (fd < 0)
                        return log_error_errno(fd, "sd_journal_get_fd failed: %m");

                events = sd_journal_get_events(j);

                r = sd_journal_reliable_fd(j);
                assert(r >= 0);
                if (r > 0)
                        u->timeout = -1;
                else
                        u->timeout = JOURNAL_UPLOAD_POLL_TIMEOUT;

                r = sd_event_add_io(u->events, &u->input_event,
                                    fd, events, dispatch_journal_input, u);
                if (r < 0)
                        return log_error_errno(r, "Failed to register input event: %m");

                log_debug("Listening for journal events on fd:%d, timeout %d",
                          fd, u->timeout == (uint64_t) -1 ? -1 : (int) u->timeout);
        } else
                log_debug("Not listening for journal events.");

        if (cursor) {
                r = sd_journal_seek_cursor(j, cursor);
                if (r < 0)
                        return log_error_errno(r, "Failed to seek to cursor %s: %m",
                                               cursor);
        }

        return process_journal_input(u, 1 + !!after_cursor);
}