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
struct signalfd_siginfo {int dummy; } ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_5__ {int /*<<< orphan*/  events; } ;
typedef  TYPE_1__ Uploader ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  close_fd_input (TYPE_1__*) ; 
 int /*<<< orphan*/  close_journal_input (TYPE_1__*) ; 
 int /*<<< orphan*/  log_received_signal (int /*<<< orphan*/ ,struct signalfd_siginfo const*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dispatch_sigterm(sd_event_source *event,
                            const struct signalfd_siginfo *si,
                            void *userdata) {
        Uploader *u = userdata;

        assert(u);

        log_received_signal(LOG_INFO, si);

        close_fd_input(u);
        close_journal_input(u);

        sd_event_exit(u->events, 0);
        return 0;
}