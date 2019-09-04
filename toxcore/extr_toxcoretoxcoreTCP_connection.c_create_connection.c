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
struct TYPE_5__ {size_t connections_length; TYPE_2__* connections; } ;
typedef  TYPE_1__ TCP_Connections ;
typedef  int /*<<< orphan*/  TCP_Connection_to ;

/* Variables and functions */
 scalar_t__ TCP_CONN_NONE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc_tox_array (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_connection(TCP_Connections *tcp_c)
{
    uint32_t i;

    for (i = 0; i < tcp_c->connections_length; ++i) {
        if (tcp_c->connections[i].status == TCP_CONN_NONE)
            return i;
    }

    int id = -1;

    TCP_Connection_to *temp_pointer;

    if (realloc_tox_array(tcp_c->connections, sizeof(TCP_Connection_to), tcp_c->connections_length + 1,
                          temp_pointer) == 0) {
        id = tcp_c->connections_length;
        ++tcp_c->connections_length;
        memset(&(tcp_c->connections[id]), 0, sizeof(TCP_Connection_to));
    }

    return id;
}