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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_11__ {scalar_t__ status; int /*<<< orphan*/  kill_at; int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ TCP_Client_Connection ;

/* Variables and functions */
 scalar_t__ TCP_CLIENT_CONFIRMED ; 
 scalar_t__ TCP_CLIENT_CONNECTING ; 
 scalar_t__ TCP_CLIENT_DISCONNECTED ; 
 scalar_t__ TCP_CLIENT_PROXY_HTTP_CONNECTING ; 
 scalar_t__ TCP_CLIENT_PROXY_SOCKS5_CONNECTING ; 
 scalar_t__ TCP_CLIENT_PROXY_SOCKS5_UNCONFIRMED ; 
 scalar_t__ TCP_CLIENT_UNCONFIRMED ; 
 int TCP_SERVER_HANDSHAKE_SIZE ; 
 int /*<<< orphan*/  do_confirmed_TCP (TYPE_1__*) ; 
 int /*<<< orphan*/  generate_handshake (TYPE_1__*) ; 
 scalar_t__ handle_handshake (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int proxy_http_read_connection_response (TYPE_1__*) ; 
 int /*<<< orphan*/  proxy_socks5_generate_connection_request (TYPE_1__*) ; 
 int proxy_socks5_read_connection_response (TYPE_1__*) ; 
 int read_TCP_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ send_pending_data (TYPE_1__*) ; 
 int socks5_read_handshake_response (TYPE_1__*) ; 
 int /*<<< orphan*/  unix_time () ; 
 int /*<<< orphan*/  unix_time_update () ; 

void do_TCP_connection(TCP_Client_Connection *TCP_connection)
{
    unix_time_update();

    if (TCP_connection->status == TCP_CLIENT_DISCONNECTED) {
        return;
    }

    if (TCP_connection->status == TCP_CLIENT_PROXY_HTTP_CONNECTING) {
        if (send_pending_data(TCP_connection) == 0) {
            int ret = proxy_http_read_connection_response(TCP_connection);

            if (ret == -1) {
                TCP_connection->kill_at = 0;
                TCP_connection->status = TCP_CLIENT_DISCONNECTED;
            }

            if (ret == 1) {
                generate_handshake(TCP_connection);
                TCP_connection->status = TCP_CLIENT_CONNECTING;
            }
        }
    }

    if (TCP_connection->status == TCP_CLIENT_PROXY_SOCKS5_CONNECTING) {
        if (send_pending_data(TCP_connection) == 0) {
            int ret = socks5_read_handshake_response(TCP_connection);

            if (ret == -1) {
                TCP_connection->kill_at = 0;
                TCP_connection->status = TCP_CLIENT_DISCONNECTED;
            }

            if (ret == 1) {
                proxy_socks5_generate_connection_request(TCP_connection);
                TCP_connection->status = TCP_CLIENT_PROXY_SOCKS5_UNCONFIRMED;
            }
        }
    }

    if (TCP_connection->status == TCP_CLIENT_PROXY_SOCKS5_UNCONFIRMED) {
        if (send_pending_data(TCP_connection) == 0) {
            int ret = proxy_socks5_read_connection_response(TCP_connection);

            if (ret == -1) {
                TCP_connection->kill_at = 0;
                TCP_connection->status = TCP_CLIENT_DISCONNECTED;
            }

            if (ret == 1) {
                generate_handshake(TCP_connection);
                TCP_connection->status = TCP_CLIENT_CONNECTING;
            }
        }
    }

    if (TCP_connection->status == TCP_CLIENT_CONNECTING) {
        if (send_pending_data(TCP_connection) == 0) {
            TCP_connection->status = TCP_CLIENT_UNCONFIRMED;
        }
    }

    if (TCP_connection->status == TCP_CLIENT_UNCONFIRMED) {
        uint8_t data[TCP_SERVER_HANDSHAKE_SIZE];
        int len = read_TCP_packet(TCP_connection->sock, data, sizeof(data));

        if (sizeof(data) == len) {
            if (handle_handshake(TCP_connection, data) == 0) {
                TCP_connection->kill_at = ~0;
                TCP_connection->status = TCP_CLIENT_CONFIRMED;
            } else {
                TCP_connection->kill_at = 0;
                TCP_connection->status = TCP_CLIENT_DISCONNECTED;
            }
        }
    }

    if (TCP_connection->status == TCP_CLIENT_CONFIRMED) {
        do_confirmed_TCP(TCP_connection);
    }

    if (TCP_connection->kill_at <= unix_time()) {
        TCP_connection->status = TCP_CLIENT_DISCONNECTED;
    }
}