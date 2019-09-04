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
struct socket_udp_address {int dummy; } ;
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_SERVER ; 
 int socket_server_udp_send (int /*<<< orphan*/ ,int,struct socket_udp_address const*,void const*,int) ; 

int 
skynet_socket_udp_send(struct skynet_context *ctx, int id, const char * address, const void *buffer, int sz) {
	return socket_server_udp_send(SOCKET_SERVER, id, (const struct socket_udp_address *)address, buffer, sz);
}