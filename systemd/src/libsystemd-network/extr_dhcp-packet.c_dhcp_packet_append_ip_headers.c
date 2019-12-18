#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  void* be32_t ;
struct TYPE_6__ {int ihl; int tos; void* check; scalar_t__ ttl; void* daddr; void* saddr; int /*<<< orphan*/  protocol; void* tot_len; int /*<<< orphan*/  version; } ;
struct TYPE_5__ {void* check; void* len; void* dest; void* source; } ;
struct TYPE_7__ {TYPE_2__ ip; TYPE_1__ udp; } ;
typedef  TYPE_3__ DHCPPacket ;

/* Variables and functions */
 int DHCP_IP_SIZE ; 
 scalar_t__ IPDEFTTL ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int IPTOS_CLASS_CS6 ; 
 int /*<<< orphan*/  IPVERSION ; 
 void* dhcp_packet_checksum (int /*<<< orphan*/ *,int) ; 
 void* htobe16 (int) ; 

void dhcp_packet_append_ip_headers(DHCPPacket *packet, be32_t source_addr,
                                   uint16_t source_port, be32_t destination_addr,
                                   uint16_t destination_port, uint16_t len, int ip_service_type) {
        packet->ip.version = IPVERSION;
        packet->ip.ihl = DHCP_IP_SIZE / 4;
        packet->ip.tot_len = htobe16(len);

        if (ip_service_type >= 0)
                packet->ip.tos = ip_service_type;
        else
                packet->ip.tos = IPTOS_CLASS_CS6;

        packet->ip.protocol = IPPROTO_UDP;
        packet->ip.saddr = source_addr;
        packet->ip.daddr = destination_addr;

        packet->udp.source = htobe16(source_port);
        packet->udp.dest = htobe16(destination_port);

        packet->udp.len = htobe16(len - DHCP_IP_SIZE);

        packet->ip.check = packet->udp.len;
        packet->udp.check = dhcp_packet_checksum((uint8_t*)&packet->ip.ttl, len - 8);

        packet->ip.ttl = IPDEFTTL;
        packet->ip.check = 0;
        packet->ip.check = dhcp_packet_checksum((uint8_t*)&packet->ip, DHCP_IP_SIZE);
}