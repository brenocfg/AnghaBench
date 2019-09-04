#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status; TYPE_1__* connections; } ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  sleep_count; int /*<<< orphan*/  lock_count; int /*<<< orphan*/  connection; } ;
struct TYPE_6__ {int tcp_connection; scalar_t__ status; int /*<<< orphan*/  connection_id; } ;
typedef  TYPE_2__ TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;
typedef  TYPE_3__ TCP_Connection_to ;

/* Variables and functions */
 unsigned int MAX_FRIEND_TCP_CONNECTIONS ; 
 scalar_t__ TCP_CONNECTIONS_STATUS_ONLINE ; 
 scalar_t__ TCP_CONN_CONNECTED ; 
 scalar_t__ TCP_CONN_SLEEPING ; 
 TYPE_3__* get_connection (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* get_tcp_connection (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  send_disconnect_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wipe_connection (int /*<<< orphan*/ *,int) ; 

int kill_tcp_connection_to(TCP_Connections *tcp_c, int connections_number)
{
    TCP_Connection_to *con_to = get_connection(tcp_c, connections_number);

    if (!con_to)
        return -1;

    unsigned int i;

    for (i = 0; i < MAX_FRIEND_TCP_CONNECTIONS; ++i) {
        if (con_to->connections[i].tcp_connection) {
            unsigned int tcp_connections_number = con_to->connections[i].tcp_connection - 1;
            TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

            if (!tcp_con)
                continue;

            if (tcp_con->status == TCP_CONN_CONNECTED) {
                send_disconnect_request(tcp_con->connection, con_to->connections[i].connection_id);
            }

            if (con_to->connections[i].status == TCP_CONNECTIONS_STATUS_ONLINE) {
                --tcp_con->lock_count;

                if (con_to->status == TCP_CONN_SLEEPING) {
                    --tcp_con->sleep_count;
                }
            }
        }
    }

    return wipe_connection(tcp_c, connections_number);
}