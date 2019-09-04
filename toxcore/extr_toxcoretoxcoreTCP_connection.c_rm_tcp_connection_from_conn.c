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
struct TYPE_5__ {TYPE_1__* connections; } ;
struct TYPE_4__ {unsigned int tcp_connection; scalar_t__ connection_id; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ TCP_Connection_to ;

/* Variables and functions */
 unsigned int MAX_FRIEND_TCP_CONNECTIONS ; 
 int /*<<< orphan*/  TCP_CONNECTIONS_STATUS_NONE ; 

__attribute__((used)) static int rm_tcp_connection_from_conn(TCP_Connection_to *con_to, unsigned int tcp_connections_number)
{
    unsigned int i;

    for (i = 0; i < MAX_FRIEND_TCP_CONNECTIONS; ++i) {
        if (con_to->connections[i].tcp_connection == (tcp_connections_number + 1)) {
            con_to->connections[i].tcp_connection = 0;
            con_to->connections[i].status = TCP_CONNECTIONS_STATUS_NONE;
            con_to->connections[i].connection_id = 0;
            return i;
        }
    }

    return -1;
}