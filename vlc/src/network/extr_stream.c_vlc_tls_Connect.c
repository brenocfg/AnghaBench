#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tls_t ;
struct TYPE_2__ {int /*<<< orphan*/  peerlen; int /*<<< orphan*/  peer; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ vlc_tls_socket_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 scalar_t__ WSAEWOULDBLOCK ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int vlc_tls_WaitConnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t vlc_tls_Connect(vlc_tls_t *tls)
{
    const vlc_tls_socket_t *sock = (vlc_tls_socket_t *)tls;

    if (connect(sock->fd, sock->peer, sock->peerlen) == 0)
        return 0;
#ifndef _WIN32
    if (errno != EINPROGRESS)
        return -1;
#else
    if (WSAGetLastError() != WSAEWOULDBLOCK)
        return -1;
#endif
    return vlc_tls_WaitConnect(tls);
}