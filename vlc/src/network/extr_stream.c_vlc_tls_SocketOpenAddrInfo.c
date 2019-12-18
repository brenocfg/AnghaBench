#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_tls_t ;
struct addrinfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ vlc_tls_Connect (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_tls_SessionDelete (TYPE_1__*) ; 
 TYPE_1__* vlc_tls_SocketAddrInfo (struct addrinfo const*) ; 
 int /*<<< orphan*/  vlc_tls_socket_fastopen_ops ; 

vlc_tls_t *vlc_tls_SocketOpenAddrInfo(const struct addrinfo *restrict info,
                                      bool defer_connect)
{
    vlc_tls_t *sock = vlc_tls_SocketAddrInfo(info);
    if (sock == NULL)
        return NULL;

    if (defer_connect)
    {   /* The socket is not connected yet.
         * The connection will be triggered on the first send. */
        sock->ops = &vlc_tls_socket_fastopen_ops;
    }
    else
    {
        if (vlc_tls_Connect(sock))
        {
            vlc_tls_SessionDelete(sock);
            sock = NULL;
        }
    }
    return sock;
}