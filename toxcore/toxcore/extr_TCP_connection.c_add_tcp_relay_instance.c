#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ family; } ;
struct TYPE_12__ {TYPE_1__ ip; } ;
struct TYPE_11__ {int /*<<< orphan*/  proxy_info; int /*<<< orphan*/  self_secret_key; int /*<<< orphan*/  self_public_key; TYPE_2__* tcp_connections; } ;
struct TYPE_10__ {int /*<<< orphan*/  status; int /*<<< orphan*/  connection; } ;
typedef  TYPE_2__ TCP_con ;
typedef  TYPE_3__ TCP_Connections ;
typedef  TYPE_4__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  TCP_CONN_VALID ; 
 scalar_t__ TCP_INET ; 
 scalar_t__ TCP_INET6 ; 
 int create_tcp_connection (TYPE_3__*) ; 
 int /*<<< orphan*/  new_TCP_connection (TYPE_4__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_tcp_relay_instance(TCP_Connections *tcp_c, IP_Port ip_port, const uint8_t *relay_pk)
{
    if (ip_port.ip.family == TCP_INET) {
        ip_port.ip.family = AF_INET;
    } else if (ip_port.ip.family == TCP_INET6) {
        ip_port.ip.family = AF_INET6;
    }

    if (ip_port.ip.family != AF_INET && ip_port.ip.family != AF_INET6)
        return -1;

    int tcp_connections_number = create_tcp_connection(tcp_c);

    if (tcp_connections_number == -1)
        return -1;

    TCP_con *tcp_con = &tcp_c->tcp_connections[tcp_connections_number];


    tcp_con->connection = new_TCP_connection(ip_port, relay_pk, tcp_c->self_public_key, tcp_c->self_secret_key,
                          &tcp_c->proxy_info);

    if (!tcp_con->connection)
        return -1;

    tcp_con->status = TCP_CONN_VALID;

    return tcp_connections_number;
}