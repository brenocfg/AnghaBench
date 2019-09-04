#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ status; } ;
struct TYPE_6__ {int connections_length; TYPE_3__* connections; } ;
typedef  TYPE_1__ TCP_Connections ;
typedef  int /*<<< orphan*/  TCP_Connection_to ;

/* Variables and functions */
 scalar_t__ TCP_CONN_NONE ; 
 scalar_t__ connections_number_not_valid (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  realloc_tox_array (TYPE_3__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wipe_connection(TCP_Connections *tcp_c, int connections_number)
{
    if (connections_number_not_valid(tcp_c, connections_number))
        return -1;

    uint32_t i;
    memset(&(tcp_c->connections[connections_number]), 0 , sizeof(TCP_Connection_to));

    for (i = tcp_c->connections_length; i != 0; --i) {
        if (tcp_c->connections[i - 1].status != TCP_CONN_NONE)
            break;
    }

    if (tcp_c->connections_length != i) {
        tcp_c->connections_length = i;
        TCP_Connection_to *temp_pointer;
        realloc_tox_array(tcp_c->connections, sizeof(TCP_Connection_to), tcp_c->connections_length, temp_pointer);
    }

    return 0;
}