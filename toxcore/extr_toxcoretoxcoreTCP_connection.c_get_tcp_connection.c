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
struct TYPE_4__ {int /*<<< orphan*/ * tcp_connections; } ;
typedef  int /*<<< orphan*/  TCP_con ;
typedef  TYPE_1__ TCP_Connections ;

/* Variables and functions */
 scalar_t__ tcp_connections_number_not_valid (TYPE_1__ const*,int) ; 

__attribute__((used)) static TCP_con *get_tcp_connection(const TCP_Connections *tcp_c, int tcp_connections_number)
{
    if (tcp_connections_number_not_valid(tcp_c, tcp_connections_number))
        return 0;

    return &tcp_c->tcp_connections[tcp_connections_number];
}