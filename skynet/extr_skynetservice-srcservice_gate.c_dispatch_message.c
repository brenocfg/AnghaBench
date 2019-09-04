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
struct skynet_context {int dummy; } ;
struct gate {int /*<<< orphan*/  mp; struct skynet_context* ctx; int /*<<< orphan*/  header_size; } ;
struct connection {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _forward (struct gate*,struct connection*,int) ; 
 int /*<<< orphan*/  databuffer_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  databuffer_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 
 int databuffer_readheader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  databuffer_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*) ; 
 int /*<<< orphan*/  skynet_socket_close (struct skynet_context*,int) ; 

__attribute__((used)) static void
dispatch_message(struct gate *g, struct connection *c, int id, void * data, int sz) {
	databuffer_push(&c->buffer,&g->mp, data, sz);
	for (;;) {
		int size = databuffer_readheader(&c->buffer, &g->mp, g->header_size);
		if (size < 0) {
			return;
		} else if (size > 0) {
			if (size >= 0x1000000) {
				struct skynet_context * ctx = g->ctx;
				databuffer_clear(&c->buffer,&g->mp);
				skynet_socket_close(ctx, id);
				skynet_error(ctx, "Recv socket message > 16M");
				return;
			} else {
				_forward(g, c, size);
				databuffer_reset(&c->buffer);
			}
		}
	}
}