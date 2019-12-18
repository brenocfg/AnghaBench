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
struct TYPE_8__ {int tcp_connections_length; } ;
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  connected_time; int /*<<< orphan*/  lock_count; int /*<<< orphan*/  onion; } ;
typedef  TYPE_1__ TCP_con ;
typedef  TYPE_2__ TCP_Connections ;

/* Variables and functions */
 unsigned int RECOMMENDED_FRIEND_TCP_CONNECTIONS ; 
 int /*<<< orphan*/  TCP_CONNECTION_ANNOUNCE_TIMEOUT ; 
 scalar_t__ TCP_CONN_CONNECTED ; 
 TYPE_1__* get_tcp_connection (TYPE_2__*,unsigned int) ; 
 scalar_t__ is_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_tcp_relay_connection (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void kill_nonused_tcp(TCP_Connections *tcp_c)
{
    if (tcp_c->tcp_connections_length == 0)
        return;

    unsigned int i, num_online = 0, num_kill = 0, to_kill[tcp_c->tcp_connections_length];

    for (i = 0; i < tcp_c->tcp_connections_length; ++i) {
        TCP_con *tcp_con = get_tcp_connection(tcp_c, i);

        if (tcp_con) {
            if (tcp_con->status == TCP_CONN_CONNECTED) {
                if (!tcp_con->onion && !tcp_con->lock_count && is_timeout(tcp_con->connected_time, TCP_CONNECTION_ANNOUNCE_TIMEOUT)) {
                    to_kill[num_kill] = i;
                    ++num_kill;
                }

                ++num_online;
            }
        }
    }

    if (num_online <= RECOMMENDED_FRIEND_TCP_CONNECTIONS) {
        return;
    } else {
        unsigned int n = num_online - RECOMMENDED_FRIEND_TCP_CONNECTIONS;

        if (n < num_kill)
            num_kill = n;
    }

    for (i = 0; i < num_kill; ++i) {
        kill_tcp_relay_connection(tcp_c, to_kill[i]);
    }
}