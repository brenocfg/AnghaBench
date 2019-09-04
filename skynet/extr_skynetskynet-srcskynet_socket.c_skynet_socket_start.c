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
 int /*<<< orphan*/  socket_server_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void 
skynet_socket_start(struct skynet_context *ctx, int id) {
	uint32_t source = skynet_context_handle(ctx);
	socket_server_start(SOCKET_SERVER, source, id);
}