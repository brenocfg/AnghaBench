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
typedef  int /*<<< orphan*/  TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;
typedef  int /*<<< orphan*/  TCP_Connection_to ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ RECOMMENDED_FRIEND_TCP_CONNECTIONS ; 
 int add_tcp_connection_to_conn (int /*<<< orphan*/ *,int) ; 
 int add_tcp_number_relay_connection (int /*<<< orphan*/ *,int,int) ; 
 int add_tcp_relay_instance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int find_tcp_connection_relay (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_connection (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_tcp_connection (int /*<<< orphan*/ *,int) ; 
 scalar_t__ online_tcp_connection_from_conn (int /*<<< orphan*/ *) ; 

int add_tcp_relay_connection(TCP_Connections *tcp_c, int connections_number, IP_Port ip_port, const uint8_t *relay_pk)
{
    TCP_Connection_to *con_to = get_connection(tcp_c, connections_number);

    if (!con_to)
        return -1;

    int tcp_connections_number = find_tcp_connection_relay(tcp_c, relay_pk);

    if (tcp_connections_number != -1) {
        return add_tcp_number_relay_connection(tcp_c, connections_number, tcp_connections_number);
    } else {
        if (online_tcp_connection_from_conn(con_to) >= RECOMMENDED_FRIEND_TCP_CONNECTIONS) {
            return -1;
        }

        int tcp_connections_number = add_tcp_relay_instance(tcp_c, ip_port, relay_pk);

        TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

        if (!tcp_con)
            return -1;

        if (add_tcp_connection_to_conn(con_to, tcp_connections_number) == -1) {
            return -1;
        }

        return 0;
    }
}