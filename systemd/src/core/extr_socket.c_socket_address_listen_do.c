#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  socket_mode; int /*<<< orphan*/  directory_mode; int /*<<< orphan*/  transparent; int /*<<< orphan*/  free_bind; int /*<<< orphan*/  reuse_port; int /*<<< orphan*/  bind_to_device; int /*<<< orphan*/  bind_ipv6_only; int /*<<< orphan*/  backlog; } ;
typedef  TYPE_1__ SocketAddress ;
typedef  TYPE_1__ const Socket ;

/* Variables and functions */
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int socket_address_listen (TYPE_1__ const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int socket_address_listen_do(
                Socket *s,
                const SocketAddress *address,
                const char *label) {

        assert(s);
        assert(address);

        return socket_address_listen(
                        address,
                        SOCK_CLOEXEC|SOCK_NONBLOCK,
                        s->backlog,
                        s->bind_ipv6_only,
                        s->bind_to_device,
                        s->reuse_port,
                        s->free_bind,
                        s->transparent,
                        s->directory_mode,
                        s->socket_mode,
                        label);
}