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
typedef  size_t uint32_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sock_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_4__ {size_t num_listening_socks; int /*<<< orphan*/ * socks_listening; } ;
typedef  TYPE_1__ TCP_Server ;

/* Variables and functions */
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,struct sockaddr*,unsigned int*) ; 
 int accept_connection (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_TCP_accept_new(TCP_Server *TCP_server)
{
    uint32_t i;

    for (i = 0; i < TCP_server->num_listening_socks; ++i) {
        struct sockaddr_storage addr;
        unsigned int addrlen = sizeof(addr);
        sock_t sock;

        do {
            sock = accept(TCP_server->socks_listening[i], (struct sockaddr *)&addr, &addrlen);
        } while (accept_connection(TCP_server, sock) != -1);
    }
}