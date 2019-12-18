#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_1__* connections; int /*<<< orphan*/  data_callback_object; int /*<<< orphan*/  (* data_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const*,int) ;int /*<<< orphan*/  onion_callback_object; int /*<<< orphan*/  (* onion_callback ) (int /*<<< orphan*/ ,int const*,int) ;int /*<<< orphan*/  oob_data_callback_object; int /*<<< orphan*/  (* oob_data_callback ) (int /*<<< orphan*/ ,int const*,int const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ping_id; int /*<<< orphan*/  ping_response_id; int /*<<< orphan*/  status_callback_object; int /*<<< orphan*/  (* status_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  response_callback_object; int /*<<< orphan*/  (* response_callback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int status; int /*<<< orphan*/  number; int /*<<< orphan*/ * public_key; } ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 int const NUM_RESERVED_PORTS ; 
#define  TCP_PACKET_CONNECTION_NOTIFICATION 134 
#define  TCP_PACKET_DISCONNECT_NOTIFICATION 133 
#define  TCP_PACKET_ONION_RESPONSE 132 
#define  TCP_PACKET_OOB_RECV 131 
#define  TCP_PACKET_PING 130 
#define  TCP_PACKET_PONG 129 
#define  TCP_PACKET_ROUTING_RESPONSE 128 
 int crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  send_ping_response (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int const*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const*,int) ; 

__attribute__((used)) static int handle_TCP_packet(TCP_Client_Connection *conn, const uint8_t *data, uint16_t length)
{
    if (length <= 1)
        return -1;

    switch (data[0]) {
        case TCP_PACKET_ROUTING_RESPONSE: {
            if (length != 1 + 1 + crypto_box_PUBLICKEYBYTES)
                return -1;

            if (data[1] < NUM_RESERVED_PORTS)
                return 0;

            uint8_t con_id = data[1] - NUM_RESERVED_PORTS;

            if (conn->connections[con_id].status != 0)
                return 0;

            conn->connections[con_id].status = 1;
            conn->connections[con_id].number = ~0;
            memcpy(conn->connections[con_id].public_key, data + 2, crypto_box_PUBLICKEYBYTES);

            if (conn->response_callback)
                conn->response_callback(conn->response_callback_object, con_id, conn->connections[con_id].public_key);

            return 0;
        }

        case TCP_PACKET_CONNECTION_NOTIFICATION: {
            if (length != 1 + 1)
                return -1;

            if (data[1] < NUM_RESERVED_PORTS)
                return -1;

            uint8_t con_id = data[1] - NUM_RESERVED_PORTS;

            if (conn->connections[con_id].status != 1)
                return 0;

            conn->connections[con_id].status = 2;

            if (conn->status_callback)
                conn->status_callback(conn->status_callback_object, conn->connections[con_id].number, con_id,
                                      conn->connections[con_id].status);

            return 0;
        }

        case TCP_PACKET_DISCONNECT_NOTIFICATION: {
            if (length != 1 + 1)
                return -1;

            if (data[1] < NUM_RESERVED_PORTS)
                return -1;

            uint8_t con_id = data[1] - NUM_RESERVED_PORTS;

            if (conn->connections[con_id].status == 0)
                return 0;

            if (conn->connections[con_id].status != 2)
                return 0;

            conn->connections[con_id].status = 1;

            if (conn->status_callback)
                conn->status_callback(conn->status_callback_object, conn->connections[con_id].number, con_id,
                                      conn->connections[con_id].status);

            return 0;
        }

        case TCP_PACKET_PING: {
            if (length != 1 + sizeof(uint64_t))
                return -1;

            uint64_t ping_id;
            memcpy(&ping_id, data + 1, sizeof(uint64_t));
            conn->ping_response_id = ping_id;
            send_ping_response(conn);
            return 0;
        }

        case TCP_PACKET_PONG: {
            if (length != 1 + sizeof(uint64_t))
                return -1;

            uint64_t ping_id;
            memcpy(&ping_id, data + 1, sizeof(uint64_t));

            if (ping_id) {
                if (ping_id == conn->ping_id) {
                    conn->ping_id = 0;
                }

                return 0;
            } else {
                return -1;
            }
        }

        case TCP_PACKET_OOB_RECV: {
            if (length <= 1 + crypto_box_PUBLICKEYBYTES)
                return -1;

            if (conn->oob_data_callback)
                conn->oob_data_callback(conn->oob_data_callback_object, data + 1, data + 1 + crypto_box_PUBLICKEYBYTES,
                                        length - (1 + crypto_box_PUBLICKEYBYTES));

            return 0;
        }

        case TCP_PACKET_ONION_RESPONSE: {
            conn->onion_callback(conn->onion_callback_object, data + 1, length - 1);
            return 0;
        }

        default: {
            if (data[0] < NUM_RESERVED_PORTS)
                return -1;

            uint8_t con_id = data[0] - NUM_RESERVED_PORTS;

            if (conn->data_callback)
                conn->data_callback(conn->data_callback_object, conn->connections[con_id].number, con_id, data + 1, length - 1);
        }
    }

    return 0;
}