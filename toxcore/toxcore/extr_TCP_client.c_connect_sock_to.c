#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int /*<<< orphan*/  member_0; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_family; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sock_t ;
struct TYPE_9__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_10__ {scalar_t__ family; TYPE_2__ ip6; TYPE_1__ ip4; } ;
struct TYPE_12__ {int /*<<< orphan*/  port; TYPE_3__ ip; } ;
struct TYPE_11__ {scalar_t__ proxy_type; TYPE_5__ ip_port; } ;
typedef  TYPE_4__ TCP_Proxy_Info ;
typedef  TYPE_5__ IP_Port ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ TCP_PROXY_NONE ; 
 int /*<<< orphan*/  connect (int /*<<< orphan*/ ,struct sockaddr*,size_t) ; 

__attribute__((used)) static int connect_sock_to(sock_t sock, IP_Port ip_port, TCP_Proxy_Info *proxy_info)
{
    if (proxy_info->proxy_type != TCP_PROXY_NONE) {
        ip_port = proxy_info->ip_port;
    }

    struct sockaddr_storage addr = {0};

    size_t addrsize;

    if (ip_port.ip.family == AF_INET) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)&addr;

        addrsize = sizeof(struct sockaddr_in);
        addr4->sin_family = AF_INET;
        addr4->sin_addr = ip_port.ip.ip4.in_addr;
        addr4->sin_port = ip_port.port;
    } else if (ip_port.ip.family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&addr;

        addrsize = sizeof(struct sockaddr_in6);
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = ip_port.ip.ip6.in6_addr;
        addr6->sin6_port = ip_port.port;
    } else {
        return 0;
    }

    /* nonblocking socket, connect will never return success */
    connect(sock, (struct sockaddr *)&addr, addrsize);
    return 1;
}