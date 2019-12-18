#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {unsigned int tcp_connections_length; TYPE_1__* tcp_connections; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  connection; } ;
typedef  TYPE_2__ TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_CONNECTED ; 
 int send_onion_request (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int tcp_send_onion_request(TCP_Connections *tcp_c, unsigned int tcp_connections_number, const uint8_t *data,
                           uint16_t length)
{
    if (tcp_connections_number >= tcp_c->tcp_connections_length) {
        return -1;
    }

    if (tcp_c->tcp_connections[tcp_connections_number].status == TCP_CONN_CONNECTED) {
        int ret = send_onion_request(tcp_c->tcp_connections[tcp_connections_number].connection, data, length);

        if (ret == 1)
            return 0;
    }

    return -1;
}