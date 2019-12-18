#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t num_listening_socks; struct TYPE_5__* accepted_connection_array; struct TYPE_5__* socks_listening; int /*<<< orphan*/  efd; int /*<<< orphan*/  accepted_key_list; scalar_t__ onion; } ;
typedef  TYPE_1__ TCP_Server ;

/* Variables and functions */
 int /*<<< orphan*/  bs_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_sock (TYPE_1__) ; 
 int /*<<< orphan*/  set_callback_handle_recv_1 (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kill_TCP_server(TCP_Server *TCP_server)
{
    uint32_t i;

    for (i = 0; i < TCP_server->num_listening_socks; ++i) {
        kill_sock(TCP_server->socks_listening[i]);
    }

    if (TCP_server->onion) {
        set_callback_handle_recv_1(TCP_server->onion, NULL, NULL);
    }

    bs_list_free(&TCP_server->accepted_key_list);

#ifdef TCP_SERVER_USE_EPOLL
    close(TCP_server->efd);
#endif

    free(TCP_server->socks_listening);
    free(TCP_server->accepted_connection_array);
    free(TCP_server);
}