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
struct vlc_tls_socket {int fd; } ;
typedef  struct vlc_tls_socket vlc_tls_socket_t ;

/* Variables and functions */

__attribute__((used)) static int vlc_tls_SocketGetFD(vlc_tls_t *tls, short *restrict events)
{
    vlc_tls_socket_t *sock = (struct vlc_tls_socket *)tls;

    (void) events;
    return sock->fd;
}