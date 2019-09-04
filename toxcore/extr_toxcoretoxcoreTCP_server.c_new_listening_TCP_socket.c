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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_MAX_BACKLOG ; 
 scalar_t__ bind_to_port (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_sock (int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_socket_dualstack (int /*<<< orphan*/ ) ; 
 int set_socket_nonblock (int /*<<< orphan*/ ) ; 
 int set_socket_reuseaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sock_t new_listening_TCP_socket(int family, uint16_t port)
{
    sock_t sock = socket(family, SOCK_STREAM, IPPROTO_TCP);

    if (!sock_valid(sock)) {
        return ~0;
    }

    int ok = set_socket_nonblock(sock);

    if (ok && family == AF_INET6) {
        ok = set_socket_dualstack(sock);
    }

    if (ok) {
        ok = set_socket_reuseaddr(sock);
    }

    ok = ok && bind_to_port(sock, family, port) && (listen(sock, TCP_MAX_BACKLOG) == 0);

    if (!ok) {
        kill_sock(sock);
        return ~0;
    }

    return sock;
}