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
typedef  int uint32_t ;
struct slave {scalar_t__ fd; scalar_t__ status; int /*<<< orphan*/ * queue; } ;
struct skynet_context {int dummy; } ;
struct remote_message_header {int source; int destination; int session; } ;
struct harbor {int id; struct slave* s; struct skynet_context* ctx; } ;

/* Variables and functions */
 int HANDLE_MASK ; 
 int HANDLE_REMOTE_SHIFT ; 
 int PTYPE_ERROR ; 
 int PTYPE_TAG_DONTCOPY ; 
 scalar_t__ STATUS_DOWN ; 
 scalar_t__ STATUS_HANDSHAKE ; 
 int /*<<< orphan*/ * new_queue () ; 
 int /*<<< orphan*/  push_queue (int /*<<< orphan*/ *,void*,size_t,struct remote_message_header*) ; 
 int /*<<< orphan*/  send_remote (struct skynet_context*,scalar_t__,char const*,size_t,struct remote_message_header*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  skynet_send (struct skynet_context*,int,int,int,int,void*,size_t) ; 

__attribute__((used)) static int
remote_send_handle(struct harbor *h, uint32_t source, uint32_t destination, int type, int session, const char * msg, size_t sz) {
	int harbor_id = destination >> HANDLE_REMOTE_SHIFT;
	struct skynet_context * context = h->ctx;
	if (harbor_id == h->id) {
		// local message
		skynet_send(context, source, destination , type | PTYPE_TAG_DONTCOPY, session, (void *)msg, sz);
		return 1;
	}

	struct slave * s = &h->s[harbor_id];
	if (s->fd == 0 || s->status == STATUS_HANDSHAKE) {
		if (s->status == STATUS_DOWN) {
			// throw an error return to source
			// report the destination is dead
			skynet_send(context, destination, source, PTYPE_ERROR, 0 , NULL, 0);
			skynet_error(context, "Drop message to harbor %d from %x to %x (session = %d, msgsz = %d)",harbor_id, source, destination,session,(int)sz);
		} else {
			if (s->queue == NULL) {
				s->queue = new_queue();
			}
			struct remote_message_header header;
			header.source = source;
			header.destination = (type << HANDLE_REMOTE_SHIFT) | (destination & HANDLE_MASK);
			header.session = (uint32_t)session;
			push_queue(s->queue, (void *)msg, sz, &header);
			return 1;
		}
	} else {
		struct remote_message_header cookie;
		cookie.source = source;
		cookie.destination = (destination & HANDLE_MASK) | ((uint32_t)type << HANDLE_REMOTE_SHIFT);
		cookie.session = (uint32_t)session;
		send_remote(context, s->fd, msg,sz,&cookie);
	}

	return 0;
}