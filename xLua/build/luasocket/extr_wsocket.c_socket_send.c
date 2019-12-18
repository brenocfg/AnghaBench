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
typedef  int /*<<< orphan*/  p_timeout ;
typedef  scalar_t__* p_socket ;

/* Variables and functions */
 int IO_CLOSED ; 
 int IO_DONE ; 
 scalar_t__ SOCKET_INVALID ; 
 int /*<<< orphan*/  WAITFD_W ; 
 int WSAEWOULDBLOCK ; 
 int WSAGetLastError () ; 
 int send (scalar_t__,char const*,int,int /*<<< orphan*/ ) ; 
 int socket_waitfd (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int socket_send(p_socket ps, const char *data, size_t count, 
        size_t *sent, p_timeout tm)
{
    int err;
    *sent = 0;
    /* avoid making system calls on closed sockets */
    if (*ps == SOCKET_INVALID) return IO_CLOSED;
    /* loop until we send something or we give up on error */
    for ( ;; ) {
        /* try to send something */
        int put = send(*ps, data, (int) count, 0);
        /* if we sent something, we are done */
        if (put > 0) {
            *sent = put;
            return IO_DONE;
        }
        /* deal with failure */
        err = WSAGetLastError(); 
        /* we can only proceed if there was no serious error */
        if (err != WSAEWOULDBLOCK) return err;
        /* avoid busy wait */
        if ((err = socket_waitfd(ps, WAITFD_W, tm)) != IO_DONE) return err;
    } 
}