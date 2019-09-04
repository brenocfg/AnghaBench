#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {size_t tcp_connections_length; TYPE_2__* tcp_connections; } ;
typedef  int /*<<< orphan*/  TCP_con ;
typedef  TYPE_1__ TCP_Connections ;

/* Variables and functions */
 scalar_t__ TCP_CONN_NONE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc_tox_array (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_tcp_connection(TCP_Connections *tcp_c)
{
    uint32_t i;

    for (i = 0; i < tcp_c->tcp_connections_length; ++i) {
        if (tcp_c->tcp_connections[i].status == TCP_CONN_NONE)
            return i;
    }

    int id = -1;

    TCP_con *temp_pointer;

    if (realloc_tox_array(tcp_c->tcp_connections, sizeof(TCP_con), tcp_c->tcp_connections_length + 1, temp_pointer) == 0) {
        id = tcp_c->tcp_connections_length;
        ++tcp_c->tcp_connections_length;
        memset(&(tcp_c->tcp_connections[id]), 0, sizeof(TCP_con));
    }

    return id;
}