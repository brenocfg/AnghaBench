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
struct skynet_message {int dummy; } ;
struct skynet_context {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_context_release (struct skynet_context*) ; 
 struct skynet_context* skynet_handle_grab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_mq_push (int /*<<< orphan*/ ,struct skynet_message*) ; 

int
skynet_context_push(uint32_t handle, struct skynet_message *message) {
	struct skynet_context * ctx = skynet_handle_grab(handle);
	if (ctx == NULL) {
		return -1;
	}
	skynet_mq_push(ctx->queue, message);
	skynet_context_release(ctx);

	return 0;
}