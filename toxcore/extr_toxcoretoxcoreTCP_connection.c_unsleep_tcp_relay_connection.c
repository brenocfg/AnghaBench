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
struct TYPE_8__ {int /*<<< orphan*/  proxy_info; int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  self_public_key; } ;
struct TYPE_7__ {scalar_t__ status; scalar_t__ unsleep; scalar_t__ connected_time; scalar_t__ sleep_count; scalar_t__ lock_count; int /*<<< orphan*/  connection; int /*<<< orphan*/  relay_pk; int /*<<< orphan*/  ip_port; } ;
typedef  TYPE_1__ TCP_con ;
typedef  TYPE_2__ TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_SLEEPING ; 
 scalar_t__ TCP_CONN_VALID ; 
 TYPE_1__* get_tcp_connection (TYPE_2__*,int) ; 
 int /*<<< orphan*/  kill_tcp_relay_connection (TYPE_2__*,int) ; 
 int /*<<< orphan*/  new_TCP_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unsleep_tcp_relay_connection(TCP_Connections *tcp_c, int tcp_connections_number)
{
    TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

    if (!tcp_con)
        return -1;

    if (tcp_con->status != TCP_CONN_SLEEPING)
        return -1;

    tcp_con->connection = new_TCP_connection(tcp_con->ip_port, tcp_con->relay_pk, tcp_c->self_public_key,
                          tcp_c->self_secret_key, &tcp_c->proxy_info);

    if (!tcp_con->connection) {
        kill_tcp_relay_connection(tcp_c, tcp_connections_number);
        return -1;
    }

    tcp_con->lock_count = 0;
    tcp_con->sleep_count = 0;
    tcp_con->connected_time = 0;
    tcp_con->status = TCP_CONN_VALID;
    tcp_con->unsleep = 0;
    return 0;
}