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
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_SLEEPING ; 
 TYPE_1__* get_tcp_connection (int /*<<< orphan*/ *,int) ; 
 int send_routing_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_tcp_relay_routing_request(TCP_Connections *tcp_c, int tcp_connections_number, uint8_t *public_key)
{
    TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

    if (!tcp_con)
        return -1;

    if (tcp_con->status == TCP_CONN_SLEEPING)
        return -1;

    if (send_routing_request(tcp_con->connection, public_key) != 1)
        return -1;

    return 0;
}