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
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct vlc_tls_socket {int /*<<< orphan*/  fd; } ;
typedef  struct vlc_tls_socket vlc_tls_socket_t ;
struct msghdr {unsigned int msg_iovlen; struct iovec* msg_iov; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t vlc_tls_SocketRead(vlc_tls_t *tls, struct iovec *iov,
                                  unsigned count)
{
    vlc_tls_socket_t *sock = (struct vlc_tls_socket *)tls;
    struct msghdr msg =
    {
        .msg_iov = iov,
        .msg_iovlen = count,
    };

    return recvmsg(sock->fd, &msg, 0);
}