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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_sockaddr_info(stream_t *p_access, struct sockaddr *x)
{
    if (x->sa_family == AF_INET)
    {
        struct sockaddr_in *xin = (void*)x;
        msg_Info(p_access, "Peer IP:Port %s:%d", inet_ntoa(xin->sin_addr), ntohs(xin->sin_port));
    }
    else if (x->sa_family == AF_INET6)
    {
        struct sockaddr_in6 *xin6 = (void*)x;
        char str[INET6_ADDRSTRLEN];
        inet_ntop(xin6->sin6_family, &xin6->sin6_addr, str, sizeof(struct in6_addr));
        msg_Info(p_access, "Peer IP:Port %s:%d", str, ntohs(xin6->sin6_port));
    }
}