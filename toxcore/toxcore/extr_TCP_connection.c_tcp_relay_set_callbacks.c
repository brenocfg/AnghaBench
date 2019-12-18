#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int custom_uint; int /*<<< orphan*/ * custom_object; } ;
struct TYPE_13__ {TYPE_2__* connection; } ;
typedef  TYPE_1__ TCP_con ;
typedef  int /*<<< orphan*/  TCP_Connections ;
typedef  TYPE_2__ TCP_Client_Connection ;

/* Variables and functions */
 TYPE_1__* get_tcp_connection (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  onion_response_handler (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oob_data_handler (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  routing_data_handler (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  routing_response_handler (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  routing_status_handler (TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tcp_data_callback ; 
 int /*<<< orphan*/  tcp_onion_callback ; 
 int /*<<< orphan*/  tcp_oob_callback ; 
 int /*<<< orphan*/  tcp_response_callback ; 
 int /*<<< orphan*/  tcp_status_callback ; 

__attribute__((used)) static int tcp_relay_set_callbacks(TCP_Connections *tcp_c, int tcp_connections_number)
{
    TCP_con *tcp_con = get_tcp_connection(tcp_c, tcp_connections_number);

    if (!tcp_con)
        return -1;

    TCP_Client_Connection *con = tcp_con->connection;

    con->custom_object = tcp_c;
    con->custom_uint = tcp_connections_number;
    onion_response_handler(con, &tcp_onion_callback, tcp_c);
    routing_response_handler(con, &tcp_response_callback, con);
    routing_status_handler(con, &tcp_status_callback, con);
    routing_data_handler(con, &tcp_data_callback, con);
    oob_data_handler(con, &tcp_oob_callback, con);

    return 0;
}