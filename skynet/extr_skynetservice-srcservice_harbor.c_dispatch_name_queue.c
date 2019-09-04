#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct slave {int fd; scalar_t__ status; struct harbor_msg_queue* queue; } ;
struct skynet_context {int dummy; } ;
struct keyvalue {int value; struct harbor_msg_queue* queue; int /*<<< orphan*/  key; } ;
struct harbor_msg_queue {int dummy; } ;
struct TYPE_2__ {int destination; int /*<<< orphan*/  session; int /*<<< orphan*/  source; } ;
struct harbor_msg {int /*<<< orphan*/  buffer; TYPE_1__ header; int /*<<< orphan*/  size; } ;
struct harbor {int slave; struct slave* s; struct skynet_context* ctx; } ;

/* Variables and functions */
 int GLOBALNAME_LENGTH ; 
 int HANDLE_MASK ; 
 int HANDLE_REMOTE_SHIFT ; 
 int PTYPE_TAG_DONTCOPY ; 
 scalar_t__ STATUS_DOWN ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct harbor_msg* pop_queue (struct harbor_msg_queue*) ; 
 int /*<<< orphan*/  push_queue_msg (struct harbor_msg_queue*,struct harbor_msg*) ; 
 int /*<<< orphan*/  release_queue (struct harbor_msg_queue*) ; 
 int /*<<< orphan*/  send_remote (struct skynet_context*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  skynet_error (struct skynet_context*,char*,char*,int) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skynet_send (struct skynet_context*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dispatch_name_queue(struct harbor *h, struct keyvalue * node) {
	struct harbor_msg_queue * queue = node->queue;
	uint32_t handle = node->value;
	int harbor_id = handle >> HANDLE_REMOTE_SHIFT;
	struct skynet_context * context = h->ctx;
	struct slave *s = &h->s[harbor_id];
	int fd = s->fd;
	if (fd == 0) {
		if (s->status == STATUS_DOWN) {
			char tmp [GLOBALNAME_LENGTH+1];
			memcpy(tmp, node->key, GLOBALNAME_LENGTH);
			tmp[GLOBALNAME_LENGTH] = '\0';
			skynet_error(context, "Drop message to %s (in harbor %d)",tmp,harbor_id);
		} else {
			if (s->queue == NULL) {
				s->queue = node->queue;
				node->queue = NULL;
			} else {
				struct harbor_msg * m;
				while ((m = pop_queue(queue))!=NULL) {
					push_queue_msg(s->queue, m);
				}
			}
			if (harbor_id == (h->slave >> HANDLE_REMOTE_SHIFT)) {
				// the harbor_id is local
				struct harbor_msg * m;
				while ((m = pop_queue(s->queue)) != NULL) {
					int type = m->header.destination >> HANDLE_REMOTE_SHIFT;
					skynet_send(context, m->header.source, handle , type | PTYPE_TAG_DONTCOPY, m->header.session, m->buffer, m->size);
				}
				release_queue(s->queue);
				s->queue = NULL;
			}
		}
		return;
	}
	struct harbor_msg * m;
	while ((m = pop_queue(queue)) != NULL) {
		m->header.destination |= (handle & HANDLE_MASK);
		send_remote(context, fd, m->buffer, m->size, &m->header);
		skynet_free(m->buffer);
	}
}