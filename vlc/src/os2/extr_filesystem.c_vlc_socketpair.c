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

/* Variables and functions */
 scalar_t__ socketpair (int,int,int,int*) ; 
 int /*<<< orphan*/  vlc_socket_setup (int,int) ; 

int vlc_socketpair(int pf, int type, int proto, int fds[2], bool nonblock)
{
    if (socketpair(pf, type, proto, fds))
        return -1;

    vlc_socket_setup(fds[0], nonblock);
    vlc_socket_setup(fds[1], nonblock);
    return 0;
}