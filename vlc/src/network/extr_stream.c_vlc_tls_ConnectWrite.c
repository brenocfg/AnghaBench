#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_tls_t ;
struct TYPE_8__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  peerlen; int /*<<< orphan*/  peer; } ;
typedef  TYPE_2__ vlc_tls_socket_t ;
struct msghdr {unsigned int msg_iovlen; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/  msg_name; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EOPNOTSUPP ; 
 int MSG_FASTOPEN ; 
 int MSG_NOSIGNAL ; 
 scalar_t__ errno ; 
 scalar_t__ sendmsg (int /*<<< orphan*/ ,struct msghdr const*,int) ; 
 scalar_t__ vlc_tls_Connect (TYPE_1__*) ; 
 scalar_t__ vlc_tls_SocketWrite (TYPE_1__*,struct iovec const*,unsigned int) ; 
 scalar_t__ vlc_tls_WaitConnect (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_tls_socket_ops ; 

__attribute__((used)) static ssize_t vlc_tls_ConnectWrite(vlc_tls_t *tls,
                                    const struct iovec *iov,unsigned count)
{
    /* Next time, write directly. Do not retry to connect. */
    tls->ops = &vlc_tls_socket_ops;

#ifdef MSG_FASTOPEN
    vlc_tls_socket_t *sock = (vlc_tls_socket_t *)tls;
    const struct msghdr msg =
    {
        .msg_name = sock->peer,
        .msg_namelen = sock->peerlen,
        .msg_iov = (struct iovec *)iov,
        .msg_iovlen = count,
    };
    ssize_t ret;

    ret = sendmsg(sock->fd, &msg, MSG_NOSIGNAL|MSG_FASTOPEN);
    if (ret >= 0)
    {   /* Fast open in progress */
        return ret;
    }

    if (errno == EINPROGRESS)
    {
        if (vlc_tls_WaitConnect(tls))
            return -1;
    }
    else
    if (errno != EOPNOTSUPP)
        return -1;
    /* Fast open not supported or disabled... fallback to normal mode */
#endif

    if (vlc_tls_Connect(tls))
        return -1;

    return vlc_tls_SocketWrite(tls, iov, count);
}