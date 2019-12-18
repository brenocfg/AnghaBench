#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ llmnr_support; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int EADDRINUSE ; 
 scalar_t__ RESOLVE_SUPPORT_NO ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_warning (char*) ; 
 int manager_llmnr_ipv4_tcp_fd (TYPE_1__*) ; 
 int manager_llmnr_ipv4_udp_fd (TYPE_1__*) ; 
 int manager_llmnr_ipv6_tcp_fd (TYPE_1__*) ; 
 int manager_llmnr_ipv6_udp_fd (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_llmnr_stop (TYPE_1__*) ; 
 scalar_t__ socket_ipv6_is_supported () ; 

int manager_llmnr_start(Manager *m) {
        int r;

        assert(m);

        if (m->llmnr_support == RESOLVE_SUPPORT_NO)
                return 0;

        r = manager_llmnr_ipv4_udp_fd(m);
        if (r == -EADDRINUSE)
                goto eaddrinuse;
        if (r < 0)
                return r;

        r = manager_llmnr_ipv4_tcp_fd(m);
        if (r == -EADDRINUSE)
                goto eaddrinuse;
        if (r < 0)
                return r;

        if (socket_ipv6_is_supported()) {
                r = manager_llmnr_ipv6_udp_fd(m);
                if (r == -EADDRINUSE)
                        goto eaddrinuse;
                if (r < 0)
                        return r;

                r = manager_llmnr_ipv6_tcp_fd(m);
                if (r == -EADDRINUSE)
                        goto eaddrinuse;
                if (r < 0)
                        return r;
        }

        return 0;

eaddrinuse:
        log_warning("Another LLMNR responder prohibits binding the socket to the same port. Turning off LLMNR support.");
        m->llmnr_support = RESOLVE_SUPPORT_NO;
        manager_llmnr_stop(m);

        return 0;
}