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
struct TYPE_4__ {scalar_t__ status; scalar_t__ tcp_connection; } ;
typedef  TYPE_2__ TCP_Connection_to ;

/* Variables and functions */
 unsigned int MAX_FRIEND_TCP_CONNECTIONS ; 
 scalar_t__ TCP_CONNECTIONS_STATUS_ONLINE ; 

__attribute__((used)) static unsigned int online_tcp_connection_from_conn(TCP_Connection_to *con_to)
{
    unsigned int i, count = 0;

    for (i = 0; i < MAX_FRIEND_TCP_CONNECTIONS; ++i) {
        if (con_to->connections[i].tcp_connection) {
            if (con_to->connections[i].status == TCP_CONNECTIONS_STATUS_ONLINE) {
                ++count;
            }
        }
    }

    return count;
}