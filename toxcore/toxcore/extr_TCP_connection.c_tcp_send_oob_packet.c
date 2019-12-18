#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_CONNECTED ; 
 TYPE_1__* get_tcp_connection (int /*<<< orphan*/ *,unsigned int) ; 
 int send_oob_packet (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int tcp_send_oob_packet(TCP_Connections *tcp_c, unsigned int tcp_connections_number, const uint8_t *public_key,
                        const uint8_t *packet, uint16_t length)
{
    TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

    if (!tcp_con)
        return -1;

    if (tcp_con->status != TCP_CONN_CONNECTED)
        return -1;

    int ret = send_oob_packet(tcp_con->connection, public_key, packet, length);

    if (ret == 1)
        return 0;

    return -1;
}