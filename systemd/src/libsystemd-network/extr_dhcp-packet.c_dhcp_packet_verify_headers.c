#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__ check; int /*<<< orphan*/  dest; } ;
struct TYPE_6__ {scalar_t__ version; int ihl; scalar_t__ protocol; scalar_t__ ttl; int /*<<< orphan*/  check; } ;
struct TYPE_8__ {TYPE_2__ udp; TYPE_1__ ip; } ;
typedef  TYPE_3__ DHCPPacket ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IPVERSION ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ dhcp_packet_checksum (int /*<<< orphan*/ *,int) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,...) ; 

int dhcp_packet_verify_headers(DHCPPacket *packet, size_t len, bool checksum, uint16_t port) {
        size_t hdrlen;

        assert(packet);

        /* IP */

        if (packet->ip.version != IPVERSION)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: not IPv4");

        if (packet->ip.ihl < 5)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: IPv4 IHL (%u words) invalid",
                                       packet->ip.ihl);

        hdrlen = packet->ip.ihl * 4;
        if (hdrlen < 20)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: IPv4 IHL (%zu bytes) "
                                       "smaller than minimum (20 bytes)",
                                       hdrlen);

        if (len < hdrlen)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: packet (%zu bytes) "
                                       "smaller than expected (%zu) by IP header",
                                       len, hdrlen);

        /* UDP */

        if (packet->ip.protocol != IPPROTO_UDP)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: not UDP");

        if (len < hdrlen + be16toh(packet->udp.len))
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: packet (%zu bytes) "
                                       "smaller than expected (%zu) by UDP header",
                                       len, hdrlen + be16toh(packet->udp.len));

        if (be16toh(packet->udp.dest) != port)
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: to port %u, which "
                                       "is not the DHCP client port (%u)",
                                       be16toh(packet->udp.dest), port);

        /* checksums - computing these is relatively expensive, so only do it
           if all the other checks have passed
         */

        if (dhcp_packet_checksum((uint8_t*)&packet->ip, hdrlen))
                return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "ignoring packet: invalid IP checksum");

        if (checksum && packet->udp.check) {
                packet->ip.check = packet->udp.len;
                packet->ip.ttl = 0;

                if (dhcp_packet_checksum((uint8_t*)&packet->ip.ttl,
                                  be16toh(packet->udp.len) + 12))
                        return log_debug_errno(SYNTHETIC_ERRNO(EINVAL),
                                               "ignoring packet: invalid UDP checksum");
        }

        return 0;
}