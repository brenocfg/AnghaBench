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
 int socket (int,int,int) ; 
 int /*<<< orphan*/  vlc_socket_setup (int,int) ; 

int vlc_socket (int pf, int type, int proto, bool nonblock)
{
    int fd = socket(pf, type, proto);
    if (fd != -1)
        vlc_socket_setup(fd, nonblock);
    return fd;
}