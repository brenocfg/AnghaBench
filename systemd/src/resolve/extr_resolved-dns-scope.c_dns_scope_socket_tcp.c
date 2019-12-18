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
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
typedef  union in_addr_union {int dummy; } in_addr_union ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  DnsServer ;
typedef  int /*<<< orphan*/  DnsScope ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int dns_scope_socket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,union in_addr_union const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union sockaddr_union*) ; 

int dns_scope_socket_tcp(DnsScope *s, int family, const union in_addr_union *address, DnsServer *server, uint16_t port, union sockaddr_union *ret_socket_address) {
        /* If ret_socket_address is not NULL, the caller is responsible
         * for calling connect() or sendmsg(). This is required by TCP
         * Fast Open, to be able to send the initial SYN packet along
         * with the first data packet. */
        return dns_scope_socket(s, SOCK_STREAM, family, address, server, port, ret_socket_address);
}