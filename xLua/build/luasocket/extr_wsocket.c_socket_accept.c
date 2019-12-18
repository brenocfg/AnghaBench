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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  p_timeout ;
typedef  scalar_t__* p_socket ;
typedef  int /*<<< orphan*/  SA ;

/* Variables and functions */
 int IO_CLOSED ; 
 int IO_DONE ; 
 scalar_t__ SOCKET_INVALID ; 
 int /*<<< orphan*/  WAITFD_R ; 
 int WSAECONNABORTED ; 
 int WSAEWOULDBLOCK ; 
 int WSAGetLastError () ; 
 scalar_t__ accept (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int socket_waitfd (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int socket_accept(p_socket ps, p_socket pa, SA *addr, socklen_t *len, 
        p_timeout tm) {
    if (*ps == SOCKET_INVALID) return IO_CLOSED;
    for ( ;; ) {
        int err;
        /* try to get client socket */
        if ((*pa = accept(*ps, addr, len)) != SOCKET_INVALID) return IO_DONE;
        /* find out why we failed */
        err = WSAGetLastError(); 
        /* if we failed because there was no connectoin, keep trying */
        if (err != WSAEWOULDBLOCK && err != WSAECONNABORTED) return err;
        /* call select to avoid busy wait */
        if ((err = socket_waitfd(ps, WAITFD_R, tm)) != IO_DONE) return err;
    } 
}