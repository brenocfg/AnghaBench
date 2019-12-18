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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  bus_forward_agent_released (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_error (char*) ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  manager_notify_cgroup_empty (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ memchr (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t recv (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int manager_dispatch_cgroups_agent_fd(sd_event_source *source, int fd, uint32_t revents, void *userdata) {
        Manager *m = userdata;
        char buf[PATH_MAX];
        ssize_t n;

        n = recv(fd, buf, sizeof(buf), 0);
        if (n < 0)
                return log_error_errno(errno, "Failed to read cgroups agent message: %m");
        if (n == 0) {
                log_error("Got zero-length cgroups agent message, ignoring.");
                return 0;
        }
        if ((size_t) n >= sizeof(buf)) {
                log_error("Got overly long cgroups agent message, ignoring.");
                return 0;
        }

        if (memchr(buf, 0, n)) {
                log_error("Got cgroups agent message with embedded NUL byte, ignoring.");
                return 0;
        }
        buf[n] = 0;

        manager_notify_cgroup_empty(m, buf);
        (void) bus_forward_agent_released(m, buf);

        return 0;
}