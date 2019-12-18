#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct timespec {int dummy; } ;
struct pollfd {int fd; int revents; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 int EINTR ; 
 int /*<<< orphan*/  ELEMENTSOF (struct pollfd*) ; 
 int POLLERR ; 
 int POLLHUP ; 
 int /*<<< orphan*/  POLLIN ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int log_error_errno (int,char*) ; 
 scalar_t__ ppoll (struct pollfd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_journal_get_timeout (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_journal_process (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * timespec_store (struct timespec*,scalar_t__) ; 

__attribute__((used)) static int wait_for_change(sd_journal *j, int poll_fd) {
        struct pollfd pollfds[] = {
                { .fd = poll_fd, .events = POLLIN },
                { .fd = STDOUT_FILENO },
        };

        struct timespec ts;
        usec_t timeout;
        int r;

        assert(j);
        assert(poll_fd >= 0);

        /* Much like sd_journal_wait() but also keeps an eye on STDOUT, and exits as soon as we see a POLLHUP on that,
         * i.e. when it is closed. */

        r = sd_journal_get_timeout(j, &timeout);
        if (r < 0)
                return log_error_errno(r, "Failed to determine journal waiting time: %m");

        if (ppoll(pollfds, ELEMENTSOF(pollfds),
                  timeout == USEC_INFINITY ? NULL : timespec_store(&ts, timeout), NULL) < 0) {
                if (errno == EINTR)
                        return 0;

                return log_error_errno(errno, "Couldn't wait for journal event: %m");
        }

        if (pollfds[1].revents & (POLLHUP|POLLERR)) /* STDOUT has been closed? */
                return log_debug_errno(SYNTHETIC_ERRNO(ECANCELED),
                                       "Standard output has been closed.");

        r = sd_journal_process(j);
        if (r < 0)
                return log_error_errno(r, "Failed to process journal events: %m");

        return 0;
}