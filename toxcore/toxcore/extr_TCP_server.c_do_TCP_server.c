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
typedef  int /*<<< orphan*/  TCP_Server ;

/* Variables and functions */
 int /*<<< orphan*/  do_TCP_accept_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_TCP_confirmed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_TCP_epoll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_TCP_incomming (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_TCP_unconfirmed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_time_update () ; 

void do_TCP_server(TCP_Server *TCP_server)
{
    unix_time_update();

#ifdef TCP_SERVER_USE_EPOLL
    do_TCP_epoll(TCP_server);

#else
    do_TCP_accept_new(TCP_server);
    do_TCP_incomming(TCP_server);
    do_TCP_unconfirmed(TCP_server);
#endif

    do_TCP_confirmed(TCP_server);
}