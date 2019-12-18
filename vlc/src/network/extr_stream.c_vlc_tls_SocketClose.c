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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_Close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_tls_SocketClose(vlc_tls_t *tls)
{
    vlc_tls_socket_t *sock = (struct vlc_tls_socket *)tls;

    net_Close(sock->fd);
    free(tls);
}