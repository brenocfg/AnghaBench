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
struct skynet_monitor {int dummy; } ;
struct skynet_message {int /*<<< orphan*/  data; int /*<<< orphan*/  source; } ;
struct skynet_context {struct message_queue* queue; int /*<<< orphan*/ * cb; } ;
struct message_queue {int dummy; } ;
struct drop_t {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dispatch_message (struct skynet_context*,struct skynet_message*) ; 
 int /*<<< orphan*/  drop_message ; 
 int /*<<< orphan*/  skynet_context_release (struct skynet_context*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 
 struct message_queue* skynet_globalmq_pop () ; 
 int /*<<< orphan*/  skynet_globalmq_push (struct message_queue*) ; 
 struct skynet_context* skynet_handle_grab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_monitor_trigger (struct skynet_monitor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_mq_handle (struct message_queue*) ; 
 int skynet_mq_length (struct message_queue*) ; 
 int skynet_mq_overload (struct message_queue*) ; 
 scalar_t__ skynet_mq_pop (struct message_queue*,struct skynet_message*) ; 
 int /*<<< orphan*/  skynet_mq_release (struct message_queue*,int /*<<< orphan*/ ,struct drop_t*) ; 

struct message_queue * 
skynet_context_message_dispatch(struct skynet_monitor *sm, struct message_queue *q, int weight) {
	if (q == NULL) {
		q = skynet_globalmq_pop();
		if (q==NULL)
			return NULL;
	}

	uint32_t handle = skynet_mq_handle(q);

	struct skynet_context * ctx = skynet_handle_grab(handle);
	if (ctx == NULL) {
		struct drop_t d = { handle };
		skynet_mq_release(q, drop_message, &d);
		return skynet_globalmq_pop();
	}

	int i,n=1;
	struct skynet_message msg;

	for (i=0;i<n;i++) {
		if (skynet_mq_pop(q,&msg)) {
			skynet_context_release(ctx);
			return skynet_globalmq_pop();
		} else if (i==0 && weight >= 0) {
			n = skynet_mq_length(q);
			n >>= weight;
		}
		int overload = skynet_mq_overload(q);
		if (overload) {
			skynet_error(ctx, "May overload, message queue length = %d", overload);
		}

		skynet_monitor_trigger(sm, msg.source , handle);

		if (ctx->cb == NULL) {
			skynet_free(msg.data);
		} else {
			dispatch_message(ctx, &msg);
		}

		skynet_monitor_trigger(sm, 0,0);
	}

	assert(q == ctx->queue);
	struct message_queue *nq = skynet_globalmq_pop();
	if (nq) {
		// If global mq is not empty , push q back, and return next queue (nq)
		// Else (global mq is empty or block, don't push q back, and return q again (for next dispatch)
		skynet_globalmq_push(q);
		q = nq;
	} 
	skynet_context_release(ctx);

	return q;
}