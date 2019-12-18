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
struct slave {int /*<<< orphan*/ * queue; scalar_t__ fd; int /*<<< orphan*/  status; } ;
struct harbor {int /*<<< orphan*/  ctx; struct slave* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_DOWN ; 
 int /*<<< orphan*/  release_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skynet_socket_close (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
close_harbor(struct harbor *h, int id) {
	struct slave *s = &h->s[id];
	s->status = STATUS_DOWN;
	if (s->fd) {
		skynet_socket_close(h->ctx, s->fd);
	}
	if (s->queue) {
		release_queue(s->queue);
		s->queue = NULL;
	}
}