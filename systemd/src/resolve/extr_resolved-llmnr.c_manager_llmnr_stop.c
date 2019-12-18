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
struct TYPE_4__ {void* llmnr_ipv6_tcp_fd; void* llmnr_ipv6_tcp_event_source; void* llmnr_ipv4_tcp_fd; void* llmnr_ipv4_tcp_event_source; void* llmnr_ipv6_udp_fd; void* llmnr_ipv6_udp_event_source; void* llmnr_ipv4_udp_fd; void* llmnr_ipv4_udp_event_source; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 void* safe_close (void*) ; 
 void* sd_event_source_unref (void*) ; 

void manager_llmnr_stop(Manager *m) {
        assert(m);

        m->llmnr_ipv4_udp_event_source = sd_event_source_unref(m->llmnr_ipv4_udp_event_source);
        m->llmnr_ipv4_udp_fd = safe_close(m->llmnr_ipv4_udp_fd);

        m->llmnr_ipv6_udp_event_source = sd_event_source_unref(m->llmnr_ipv6_udp_event_source);
        m->llmnr_ipv6_udp_fd = safe_close(m->llmnr_ipv6_udp_fd);

        m->llmnr_ipv4_tcp_event_source = sd_event_source_unref(m->llmnr_ipv4_tcp_event_source);
        m->llmnr_ipv4_tcp_fd = safe_close(m->llmnr_ipv4_tcp_fd);

        m->llmnr_ipv6_tcp_event_source = sd_event_source_unref(m->llmnr_ipv6_tcp_event_source);
        m->llmnr_ipv6_tcp_fd = safe_close(m->llmnr_ipv6_tcp_fd);
}