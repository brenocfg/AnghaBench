#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_8__ {size_t* uint32; scalar_t__* uint64; } ;
struct TYPE_9__ {TYPE_1__ ip6; } ;
struct TYPE_12__ {TYPE_2__ ip; } ;
struct TYPE_11__ {scalar_t__ identifier; } ;
struct TYPE_10__ {size_t size_accepted_connections; TYPE_4__* accepted_connection_array; } ;
typedef  TYPE_3__ TCP_Server ;
typedef  TYPE_4__ TCP_Secure_Connection ;
typedef  TYPE_5__ IP_Port ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_PACKET_ONION_RESPONSE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int write_packet_TCP_secure_connection (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_onion_recv_1(void *object, IP_Port dest, const uint8_t *data, uint16_t length)
{
    TCP_Server *TCP_server = object;
    uint32_t index = dest.ip.ip6.uint32[0];

    if (index >= TCP_server->size_accepted_connections)
        return 1;

    TCP_Secure_Connection *con = &TCP_server->accepted_connection_array[index];

    if (con->identifier != dest.ip.ip6.uint64[1])
        return 1;

    uint8_t packet[1 + length];
    memcpy(packet + 1, data, length);
    packet[0] = TCP_PACKET_ONION_RESPONSE;

    if (write_packet_TCP_secure_connection(con, packet, sizeof(packet), 0) != 1)
        return 1;

    return 0;
}