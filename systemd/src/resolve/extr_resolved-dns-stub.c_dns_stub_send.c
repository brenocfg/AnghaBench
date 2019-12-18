#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  destination; int /*<<< orphan*/  sender_port; int /*<<< orphan*/  sender; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ Manager ;
typedef  int /*<<< orphan*/  DnsStream ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_stream_write_packet (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int log_debug_errno (int,char*) ; 
 int manager_dns_stub_udp_fd (TYPE_1__*) ; 
 int manager_send (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int dns_stub_send(Manager *m, DnsStream *s, DnsPacket *p, DnsPacket *reply) {
        int r;

        assert(m);
        assert(p);
        assert(reply);

        if (s)
                r = dns_stream_write_packet(s, reply);
        else {
                int fd;

                fd = manager_dns_stub_udp_fd(m);
                if (fd < 0)
                        return log_debug_errno(fd, "Failed to get reply socket: %m");

                /* Note that it is essential here that we explicitly choose the source IP address for this packet. This
                 * is because otherwise the kernel will choose it automatically based on the routing table and will
                 * thus pick 127.0.0.1 rather than 127.0.0.53. */

                r = manager_send(m, fd, LOOPBACK_IFINDEX, p->family, &p->sender, p->sender_port, &p->destination, reply);
        }
        if (r < 0)
                return log_debug_errno(r, "Failed to send reply packet: %m");

        return 0;
}