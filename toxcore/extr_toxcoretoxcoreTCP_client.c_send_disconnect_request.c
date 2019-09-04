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
typedef  size_t uint8_t ;
struct TYPE_6__ {TYPE_1__* connections; } ;
struct TYPE_5__ {scalar_t__ number; scalar_t__ status; } ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 size_t NUM_CLIENT_CONNECTIONS ; 
 scalar_t__ NUM_RESERVED_PORTS ; 
 int send_disconnect_notification (TYPE_2__*,scalar_t__) ; 

int send_disconnect_request(TCP_Client_Connection *con, uint8_t con_id)
{
    if (con_id >= NUM_CLIENT_CONNECTIONS)
        return -1;

    con->connections[con_id].status = 0;
    con->connections[con_id].number = 0;
    return send_disconnect_notification(con, con_id + NUM_RESERVED_PORTS);
}