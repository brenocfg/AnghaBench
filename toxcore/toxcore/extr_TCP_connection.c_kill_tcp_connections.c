#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int tcp_connections_length; struct TYPE_4__* connections; struct TYPE_4__* tcp_connections; int /*<<< orphan*/  connection; } ;
typedef  TYPE_1__ TCP_Connections ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_TCP_connection (int /*<<< orphan*/ ) ; 

void kill_tcp_connections(TCP_Connections *tcp_c)
{
    unsigned int i;

    for (i = 0; i < tcp_c->tcp_connections_length; ++i) {
        kill_TCP_connection(tcp_c->tcp_connections[i].connection);
    }

    free(tcp_c->tcp_connections);
    free(tcp_c->connections);
    free(tcp_c);
}