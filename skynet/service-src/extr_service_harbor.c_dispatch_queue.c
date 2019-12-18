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
struct slave {int fd; struct harbor_msg_queue* queue; } ;
struct harbor_msg_queue {int dummy; } ;
struct harbor_msg {int /*<<< orphan*/  buffer; int /*<<< orphan*/  header; int /*<<< orphan*/  size; } ;
struct harbor {int /*<<< orphan*/  ctx; struct slave* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct harbor_msg* pop_queue (struct harbor_msg_queue*) ; 
 int /*<<< orphan*/  release_queue (struct harbor_msg_queue*) ; 
 int /*<<< orphan*/  send_remote (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dispatch_queue(struct harbor *h, int id) {
	struct slave *s = &h->s[id];
	int fd = s->fd;
	assert(fd != 0);

	struct harbor_msg_queue *queue = s->queue;
	if (queue == NULL)
		return;

	struct harbor_msg * m;
	while ((m = pop_queue(queue)) != NULL) {
		send_remote(h->ctx, fd, m->buffer, m->size, &m->header);
		skynet_free(m->buffer);
	}
	release_queue(queue);
	s->queue = NULL;
}