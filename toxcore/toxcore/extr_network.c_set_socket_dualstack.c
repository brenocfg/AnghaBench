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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sock_t ;
typedef  int /*<<< orphan*/  ipv6only ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

int set_socket_dualstack(sock_t sock)
{
    int ipv6only = 0;
    socklen_t optsize = sizeof(ipv6only);
    int res = getsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&ipv6only, &optsize);

    if ((res == 0) && (ipv6only == 0))
        return 1;

    ipv6only = 0;
    return (setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (void *)&ipv6only, sizeof(ipv6only)) == 0);
}