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
typedef  int /*<<< orphan*/  val ;

/* Variables and functions */
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int socketpair (int,int,int,int*) ; 
 int /*<<< orphan*/  vlc_socket_setup (int,int) ; 

int vlc_socketpair(int pf, int type, int proto, int fds[2], bool nonblock)
{
#ifdef SOCK_CLOEXEC
    if (nonblock)
        type |= SOCK_NONBLOCK;

    int ret = socketpair(pf, type | SOCK_CLOEXEC, proto, fds);
# ifdef SO_NOSIGPIPE
    if (ret == 0)
    {
        const int val = 1;

        setsockopt(fds[0], SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof (val));
        setsockopt(fds[1], SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof (val));
    }
# endif
#else
    int ret = socketpair(pf, type, proto, fds);
    if (ret == 0)
    {
        vlc_socket_setup(fds[0], nonblock);
        vlc_socket_setup(fds[1], nonblock);
    }
#endif
    return ret;
}