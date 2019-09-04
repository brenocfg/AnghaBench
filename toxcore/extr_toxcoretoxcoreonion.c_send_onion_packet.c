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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_4__ {int /*<<< orphan*/  ip_port1; } ;
typedef  TYPE_1__ Onion_Path ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int ONION_MAX_PACKET_SIZE ; 
 int create_onion_packet (int /*<<< orphan*/ *,int,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int sendpacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int send_onion_packet(Networking_Core *net, const Onion_Path *path, IP_Port dest, const uint8_t *data, uint16_t length)
{
    uint8_t packet[ONION_MAX_PACKET_SIZE];
    int len = create_onion_packet(packet, sizeof(packet), path, dest, data, length);

    if (len == -1)
        return -1;

    if (sendpacket(net, path->ip_port1, packet, len) != len)
        return -1;

    return 0;
}