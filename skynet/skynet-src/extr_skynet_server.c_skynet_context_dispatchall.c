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
struct skynet_message {int dummy; } ;
struct skynet_context {struct message_queue* queue; } ;
struct message_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispatch_message (struct skynet_context*,struct skynet_message*) ; 
 int /*<<< orphan*/  skynet_mq_pop (struct message_queue*,struct skynet_message*) ; 

void 
skynet_context_dispatchall(struct skynet_context * ctx) {
	// for skynet_error
	struct skynet_message msg;
	struct message_queue *q = ctx->queue;
	while (!skynet_mq_pop(q,&msg)) {
		dispatch_message(ctx, &msg);
	}
}