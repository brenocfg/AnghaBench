#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p; int /*<<< orphan*/ * ops; } ;
typedef  TYPE_1__ vlc_tls_t ;
struct TYPE_6__ {int fd; int /*<<< orphan*/  peer; scalar_t__ peerlen; TYPE_1__ tls; } ;
typedef  TYPE_2__ vlc_tls_socket_t ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 TYPE_2__* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct sockaddr const*,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tls_socket_ops ; 

__attribute__((used)) static vlc_tls_t *vlc_tls_SocketAlloc(int fd,
                                      const struct sockaddr *restrict peer,
                                      socklen_t peerlen)
{
    vlc_tls_socket_t *sock = malloc(sizeof (*sock) + peerlen);
    if (unlikely(sock == NULL))
        return NULL;

    vlc_tls_t *tls = &sock->tls;

    tls->ops = &vlc_tls_socket_ops;
    tls->p = NULL;

    sock->fd = fd;
    sock->peerlen = peerlen;
    if (peerlen > 0)
        memcpy(sock->peer, peer, peerlen);
    return tls;
}