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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  packet ;
typedef  int /*<<< orphan*/  Networking_Core ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int /*<<< orphan*/  NET_PACKET_ONION_RECV_3 ; 
 scalar_t__ ONION_RESPONSE_MAX_DATA_SIZE ; 
 int RETURN_3 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ sendpacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int send_onion_response(Networking_Core *net, IP_Port dest, const uint8_t *data, uint16_t length, const uint8_t *ret)
{
    if (length > ONION_RESPONSE_MAX_DATA_SIZE || length == 0)
        return -1;

    uint8_t packet[1 + RETURN_3 + length];
    packet[0] = NET_PACKET_ONION_RECV_3;
    memcpy(packet + 1, ret, RETURN_3);
    memcpy(packet + 1 + RETURN_3, data, length);

    if ((uint32_t)sendpacket(net, dest, packet, sizeof(packet)) != sizeof(packet))
        return -1;

    return 0;
}