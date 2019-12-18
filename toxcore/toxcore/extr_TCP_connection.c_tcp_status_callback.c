#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {unsigned int custom_uint; int /*<<< orphan*/ * custom_object; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  sleep_count; int /*<<< orphan*/  lock_count; } ;
typedef  TYPE_1__ TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;
typedef  TYPE_2__ TCP_Connection_to ;
typedef  TYPE_3__ TCP_Client_Connection ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CONNECTIONS_STATUS_ONLINE ; 
 int /*<<< orphan*/  TCP_CONNECTIONS_STATUS_REGISTERED ; 
 scalar_t__ TCP_CONN_SLEEPING ; 
 TYPE_2__* get_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_tcp_connection (int /*<<< orphan*/ *,unsigned int) ; 
 int set_tcp_connection_status (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tcp_status_callback(void *object, uint32_t number, uint8_t connection_id, uint8_t status)
{
    TCP_Client_Connection *TCP_client_con = object;
    TCP_Connections *tcp_c = TCP_client_con->custom_object;

    unsigned int tcp_connections_number = TCP_client_con->custom_uint;
    TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);
    TCP_Connection_to *con_to = get_connection(tcp_c, number);

    if (!con_to || !tcp_con)
        return -1;

    if (status == 1) {
        if (set_tcp_connection_status(con_to, tcp_connections_number, TCP_CONNECTIONS_STATUS_REGISTERED, connection_id) == -1)
            return -1;

        --tcp_con->lock_count;

        if (con_to->status == TCP_CONN_SLEEPING) {
            --tcp_con->sleep_count;
        }
    } else if (status == 2) {
        if (set_tcp_connection_status(con_to, tcp_connections_number, TCP_CONNECTIONS_STATUS_ONLINE, connection_id) == -1)
            return -1;

        ++tcp_con->lock_count;

        if (con_to->status == TCP_CONN_SLEEPING) {
            ++tcp_con->sleep_count;
        }
    }

    return 0;
}