#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {TYPE_1__ sa; } ;
struct TYPE_8__ {TYPE_2__ sockaddr; } ;
typedef  TYPE_3__ SocketAddress ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  log_warning (char*) ; 
 int socket_address_parse (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 

int socket_address_parse_and_warn(SocketAddress *a, const char *s) {
        SocketAddress b;
        int r;

        /* Similar to socket_address_parse() but warns for IPv6 sockets when we don't support them. */

        r = socket_address_parse(&b, s);
        if (r < 0)
                return r;

        if (!socket_ipv6_is_supported() && b.sockaddr.sa.sa_family == AF_INET6) {
                log_warning("Binding to IPv6 address not available since kernel does not support IPv6.");
                return -EAFNOSUPPORT;
        }

        *a = b;
        return 0;
}