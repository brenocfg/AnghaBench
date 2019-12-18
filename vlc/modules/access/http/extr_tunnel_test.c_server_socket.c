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
struct sockaddr_in6 {int sin6_len; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int) ; 

__attribute__((used)) static int server_socket(unsigned *port)
{
    int fd = socket(PF_INET6, SOCK_STREAM|SOCK_CLOEXEC, IPPROTO_TCP);
    if (fd == -1)
        return -1;

    struct sockaddr_in6 addr = {
        .sin6_family = AF_INET6,
#ifdef HAVE_SA_LEN
        .sin6_len = sizeof (addr),
#endif
        .sin6_addr = in6addr_loopback,
    };
    socklen_t addrlen = sizeof (addr);

    if (bind(fd, (struct sockaddr *)&addr, addrlen)
     || getsockname(fd, (struct sockaddr *)&addr, &addrlen))
    {
        vlc_close(fd);
        return -1;
    }

    *port = ntohs(addr.sin6_port);
    return fd;
}