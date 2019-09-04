#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  response ;
struct TYPE_14__ {size_t* uint32; int /*<<< orphan*/ * uint64; } ;
struct TYPE_15__ {TYPE_1__ ip6; int /*<<< orphan*/  family; } ;
struct TYPE_19__ {TYPE_2__ ip; int /*<<< orphan*/  port; } ;
struct TYPE_18__ {int ping_id; TYPE_3__* connections; int /*<<< orphan*/  identifier; } ;
struct TYPE_17__ {TYPE_5__* accepted_connection_array; int /*<<< orphan*/  onion; } ;
struct TYPE_16__ {int status; size_t index; int const other_id; } ;
typedef  TYPE_4__ TCP_Server ;
typedef  TYPE_5__ TCP_Secure_Connection ;
typedef  TYPE_6__ IP_Port ;

/* Variables and functions */
 int NUM_CLIENT_CONNECTIONS ; 
 int const NUM_RESERVED_PORTS ; 
 int ONION_SEND_BASE ; 
 int /*<<< orphan*/  TCP_ONION_FAMILY ; 
#define  TCP_PACKET_CONNECTION_NOTIFICATION 135 
#define  TCP_PACKET_DISCONNECT_NOTIFICATION 134 
#define  TCP_PACKET_ONION_REQUEST 133 
#define  TCP_PACKET_ONION_RESPONSE 132 
#define  TCP_PACKET_OOB_SEND 131 
#define  TCP_PACKET_PING 130 
#define  TCP_PACKET_PONG 129 
#define  TCP_PACKET_ROUTING_REQUEST 128 
 int /*<<< orphan*/  crypto_box_NONCEBYTES ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int handle_TCP_oob_send (TYPE_4__*,size_t,int const*,int const*,scalar_t__) ; 
 int handle_TCP_routing_req (TYPE_4__*,size_t,int const*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,scalar_t__) ; 
 int /*<<< orphan*/  onion_send_1 (int /*<<< orphan*/ ,int const*,scalar_t__,TYPE_6__,int const*) ; 
 int rm_connection_index (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int write_packet_TCP_secure_connection (TYPE_5__*,int*,scalar_t__,int) ; 

__attribute__((used)) static int handle_TCP_packet(TCP_Server *TCP_server, uint32_t con_id, const uint8_t *data, uint16_t length)
{
    if (length == 0)
        return -1;

    TCP_Secure_Connection *con = &TCP_server->accepted_connection_array[con_id];

    switch (data[0]) {
        case TCP_PACKET_ROUTING_REQUEST: {
            if (length != 1 + crypto_box_PUBLICKEYBYTES)
                return -1;

            return handle_TCP_routing_req(TCP_server, con_id, data + 1);
        }

        case TCP_PACKET_CONNECTION_NOTIFICATION: {
            if (length != 2)
                return -1;

            break;
        }

        case TCP_PACKET_DISCONNECT_NOTIFICATION: {
            if (length != 2)
                return -1;

            return rm_connection_index(TCP_server, con, data[1] - NUM_RESERVED_PORTS);
        }

        case TCP_PACKET_PING: {
            if (length != 1 + sizeof(uint64_t))
                return -1;

            uint8_t response[1 + sizeof(uint64_t)];
            response[0] = TCP_PACKET_PONG;
            memcpy(response + 1, data + 1, sizeof(uint64_t));
            write_packet_TCP_secure_connection(con, response, sizeof(response), 1);
            return 0;
        }

        case TCP_PACKET_PONG: {
            if (length != 1 + sizeof(uint64_t))
                return -1;

            uint64_t ping_id;
            memcpy(&ping_id, data + 1, sizeof(uint64_t));

            if (ping_id) {
                if (ping_id == con->ping_id) {
                    con->ping_id = 0;
                }

                return 0;
            } else {
                return -1;
            }
        }

        case TCP_PACKET_OOB_SEND: {
            if (length <= 1 + crypto_box_PUBLICKEYBYTES)
                return -1;

            return handle_TCP_oob_send(TCP_server, con_id, data + 1, data + 1 + crypto_box_PUBLICKEYBYTES,
                                       length - (1 + crypto_box_PUBLICKEYBYTES));
        }

        case TCP_PACKET_ONION_REQUEST: {
            if (TCP_server->onion) {
                if (length <= 1 + crypto_box_NONCEBYTES + ONION_SEND_BASE * 2)
                    return -1;

                IP_Port source;
                source.port = 0;  // dummy initialise
                source.ip.family = TCP_ONION_FAMILY;
                source.ip.ip6.uint32[0] = con_id;
                source.ip.ip6.uint32[1] = 0;
                source.ip.ip6.uint64[1] = con->identifier;
                onion_send_1(TCP_server->onion, data + 1 + crypto_box_NONCEBYTES, length - (1 + crypto_box_NONCEBYTES), source,
                             data + 1);
            }

            return 0;
        }

        case TCP_PACKET_ONION_RESPONSE: {
            return -1;
        }

        default: {
            if (data[0] < NUM_RESERVED_PORTS)
                return -1;

            uint8_t c_id = data[0] - NUM_RESERVED_PORTS;

            if (c_id >= NUM_CLIENT_CONNECTIONS)
                return -1;

            if (con->connections[c_id].status == 0)
                return -1;

            if (con->connections[c_id].status != 2)
                return 0;

            uint32_t index = con->connections[c_id].index;
            uint8_t other_c_id = con->connections[c_id].other_id + NUM_RESERVED_PORTS;
            uint8_t new_data[length];
            memcpy(new_data, data, length);
            new_data[0] = other_c_id;
            int ret = write_packet_TCP_secure_connection(&TCP_server->accepted_connection_array[index], new_data, length, 0);

            if (ret == -1)
                return -1;

            return 0;
        }
    }

    return 0;
}