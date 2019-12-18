#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_10__ {int /*<<< orphan*/  uint32; } ;
struct TYPE_11__ {scalar_t__ family; TYPE_1__ ip4; } ;
struct TYPE_14__ {TYPE_2__ ip; } ;
struct TYPE_13__ {int /*<<< orphan*/  c; int /*<<< orphan*/  net; } ;
struct TYPE_12__ {TYPE_5__ ip_port1; } ;
typedef  TYPE_3__ Onion_Path ;
typedef  TYPE_4__ Onion_Client ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int ONION_MAX_PACKET_SIZE ; 
 scalar_t__ TCP_FAMILY ; 
 int create_onion_packet (int /*<<< orphan*/ *,int,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int create_onion_packet_tcp (int /*<<< orphan*/ *,int,TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int send_tcp_onion_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int sendpacket (int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int send_onion_packet_tcp_udp(const Onion_Client *onion_c, const Onion_Path *path, IP_Port dest,
                                     const uint8_t *data, uint16_t length)
{
    if (path->ip_port1.ip.family == AF_INET || path->ip_port1.ip.family == AF_INET6) {
        uint8_t packet[ONION_MAX_PACKET_SIZE];
        int len = create_onion_packet(packet, sizeof(packet), path, dest, data, length);

        if (len == -1)
            return -1;

        if (sendpacket(onion_c->net, path->ip_port1, packet, len) != len)
            return -1;

        return 0;
    } else if (path->ip_port1.ip.family == TCP_FAMILY) {
        uint8_t packet[ONION_MAX_PACKET_SIZE];
        int len = create_onion_packet_tcp(packet, sizeof(packet), path, dest, data, length);

        if (len == -1)
            return -1;

        return send_tcp_onion_request(onion_c->c, path->ip_port1.ip.ip4.uint32, packet, len);
    } else {
        return -1;
    }
}