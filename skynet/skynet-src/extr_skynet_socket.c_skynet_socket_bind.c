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
typedef  int /*<<< orphan*/  uint32_t ;
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_SERVER ; 
 int /*<<< orphan*/  skynet_context_handle (struct skynet_context*) ; 
 int socket_server_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int 
skynet_socket_bind(struct skynet_context *ctx, int fd) {
	uint32_t source = skynet_context_handle(ctx);
	return socket_server_bind(SOCKET_SERVER, source, fd);
}