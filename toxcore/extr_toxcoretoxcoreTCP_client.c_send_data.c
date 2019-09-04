#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  packet ;
struct TYPE_8__ {TYPE_1__* connections; } ;
struct TYPE_7__ {int status; } ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 size_t NUM_CLIENT_CONNECTIONS ; 
 size_t NUM_RESERVED_PORTS ; 
 int /*<<< orphan*/  memcpy (size_t*,size_t const*,int /*<<< orphan*/ ) ; 
 scalar_t__ send_ping_request (TYPE_2__*) ; 
 scalar_t__ send_ping_response (TYPE_2__*) ; 
 int write_packet_TCP_secure_connection (TYPE_2__*,size_t*,int,int /*<<< orphan*/ ) ; 

int send_data(TCP_Client_Connection *con, uint8_t con_id, const uint8_t *data, uint16_t length)
{
    if (con_id >= NUM_CLIENT_CONNECTIONS)
        return -1;

    if (con->connections[con_id].status != 2)
        return -1;

    if (send_ping_response(con) == 0 || send_ping_request(con) == 0)
        return 0;

    uint8_t packet[1 + length];
    packet[0] = con_id + NUM_RESERVED_PORTS;
    memcpy(packet + 1, data, length);
    return write_packet_TCP_secure_connection(con, packet, sizeof(packet), 0);
}