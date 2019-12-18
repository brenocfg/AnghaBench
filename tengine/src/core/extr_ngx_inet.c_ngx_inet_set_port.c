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
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
#define  AF_INET6 129 
#define  AF_UNIX 128 
 void* htons (int /*<<< orphan*/ ) ; 

void
ngx_inet_set_port(struct sockaddr *sa, in_port_t port)
{
    struct sockaddr_in   *sin;
#if (NGX_HAVE_INET6)
    struct sockaddr_in6  *sin6;
#endif

    switch (sa->sa_family) {

#if (NGX_HAVE_INET6)
    case AF_INET6:
        sin6 = (struct sockaddr_in6 *) sa;
        sin6->sin6_port = htons(port);
        break;
#endif

#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_UNIX:
        break;
#endif

    default: /* AF_INET */
        sin = (struct sockaddr_in *) sa;
        sin->sin_port = htons(port);
        break;
    }
}