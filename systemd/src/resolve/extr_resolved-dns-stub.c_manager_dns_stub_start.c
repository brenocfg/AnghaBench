#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dns_stub_listener_mode; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ DNS_STUB_LISTENER_NO ; 
 scalar_t__ DNS_STUB_LISTENER_TCP ; 
 scalar_t__ DNS_STUB_LISTENER_UDP ; 
 int DNS_STUB_LISTENER_YES ; 
 int EADDRINUSE ; 
 scalar_t__ EPERM ; 
 scalar_t__ IN_SET (int,int,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int log_error_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*) ; 
 int /*<<< orphan*/  manager_dns_stub_stop (TYPE_1__*) ; 
 int manager_dns_stub_tcp_fd (TYPE_1__*) ; 
 int manager_dns_stub_udp_fd (TYPE_1__*) ; 

int manager_dns_stub_start(Manager *m) {
        const char *t = "UDP";
        int r = 0;

        assert(m);

        if (m->dns_stub_listener_mode == DNS_STUB_LISTENER_NO)
                log_debug("Not creating stub listener.");
        else
                log_debug("Creating stub listener using %s.",
                          m->dns_stub_listener_mode == DNS_STUB_LISTENER_UDP ? "UDP" :
                          m->dns_stub_listener_mode == DNS_STUB_LISTENER_TCP ? "TCP" :
                          "UDP/TCP");

        if (IN_SET(m->dns_stub_listener_mode, DNS_STUB_LISTENER_YES, DNS_STUB_LISTENER_UDP))
                r = manager_dns_stub_udp_fd(m);

        if (r >= 0 &&
            IN_SET(m->dns_stub_listener_mode, DNS_STUB_LISTENER_YES, DNS_STUB_LISTENER_TCP)) {
                t = "TCP";
                r = manager_dns_stub_tcp_fd(m);
        }

        if (IN_SET(r, -EADDRINUSE, -EPERM)) {
                if (r == -EADDRINUSE)
                        log_warning_errno(r,
                                          "Another process is already listening on %s socket 127.0.0.53:53.\n"
                                          "Turning off local DNS stub support.", t);
                else
                        log_warning_errno(r,
                                          "Failed to listen on %s socket 127.0.0.53:53: %m.\n"
                                          "Turning off local DNS stub support.", t);
                manager_dns_stub_stop(m);
        } else if (r < 0)
                return log_error_errno(r, "Failed to listen on %s socket 127.0.0.53:53: %m", t);

        return 0;
}