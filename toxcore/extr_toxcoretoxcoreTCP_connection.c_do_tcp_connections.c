#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TCP_Connections ;

/* Variables and functions */
 int /*<<< orphan*/  do_tcp_conns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_nonused_tcp (int /*<<< orphan*/ *) ; 

void do_tcp_connections(TCP_Connections *tcp_c)
{
    do_tcp_conns(tcp_c);
    kill_nonused_tcp(tcp_c);
}