#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_6__ {int tcp_connections_length; TYPE_4__* tcp_connections; } ;
typedef  int /*<<< orphan*/  TCP_con ;
typedef  TYPE_1__ TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_NONE ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc_tox_array (TYPE_4__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_connections_number_not_valid (TYPE_1__*,int) ; 

__attribute__((used)) static int wipe_tcp_connection(TCP_Connections *tcp_c, int tcp_connections_number)
{
    if (tcp_connections_number_not_valid(tcp_c, tcp_connections_number))
        return -1;

    uint32_t i;
    memset(&(tcp_c->tcp_connections[tcp_connections_number]), 0 , sizeof(TCP_con));

    for (i = tcp_c->tcp_connections_length; i != 0; --i) {
        if (tcp_c->tcp_connections[i - 1].status != TCP_CONN_NONE)
            break;
    }

    if (tcp_c->tcp_connections_length != i) {
        tcp_c->tcp_connections_length = i;
        TCP_con *temp_pointer;
        realloc_tox_array(tcp_c->tcp_connections, sizeof(TCP_con), tcp_c->tcp_connections_length, temp_pointer);
    }

    return 0;
}