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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {TYPE_1__* connections; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 size_t NUM_CLIENT_CONNECTIONS ; 

int set_tcp_connection_number(TCP_Client_Connection *con, uint8_t con_id, uint32_t number)
{
    if (con_id >= NUM_CLIENT_CONNECTIONS)
        return -1;

    if (con->connections[con_id].status == 0)
        return -1;

    con->connections[con_id].number = number;
    return 0;
}