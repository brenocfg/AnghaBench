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
struct TYPE_5__ {scalar_t__ hostname_fd; int /*<<< orphan*/  full_hostname; int /*<<< orphan*/  mdns_hostname; int /*<<< orphan*/  llmnr_hostname; int /*<<< orphan*/  hostname_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int EPERM ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int determine_hostname (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fallback_hostname () ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning_errno (int /*<<< orphan*/ ,char*) ; 
 int make_fallback_hostnames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_hostname_change ; 
 scalar_t__ open (char*,int) ; 
 scalar_t__ safe_close (scalar_t__) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int manager_watch_hostname(Manager *m) {
        int r;

        assert(m);

        m->hostname_fd = open("/proc/sys/kernel/hostname",
                              O_RDONLY|O_CLOEXEC|O_NONBLOCK|O_NOCTTY);
        if (m->hostname_fd < 0) {
                log_warning_errno(errno, "Failed to watch hostname: %m");
                return 0;
        }

        r = sd_event_add_io(m->event, &m->hostname_event_source, m->hostname_fd, 0, on_hostname_change, m);
        if (r < 0) {
                if (r == -EPERM)
                        /* kernels prior to 3.2 don't support polling this file. Ignore the failure. */
                        m->hostname_fd = safe_close(m->hostname_fd);
                else
                        return log_error_errno(r, "Failed to add hostname event source: %m");
        }

        (void) sd_event_source_set_description(m->hostname_event_source, "hostname");

        r = determine_hostname(&m->full_hostname, &m->llmnr_hostname, &m->mdns_hostname);
        if (r < 0) {
                log_info("Defaulting to hostname '%s'.", fallback_hostname());

                r = make_fallback_hostnames(&m->full_hostname, &m->llmnr_hostname, &m->mdns_hostname);
                if (r < 0)
                        return r;
        } else
                log_info("Using system hostname '%s'.", m->full_hostname);

        return 0;
}