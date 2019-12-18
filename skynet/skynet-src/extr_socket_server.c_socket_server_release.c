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
struct socket_server {int /*<<< orphan*/  event_fd; int /*<<< orphan*/  recvctrl_fd; int /*<<< orphan*/  sendctrl_fd; struct socket* slot; } ;
struct socket_message {int dummy; } ;
struct socket_lock {int dummy; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/  dw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct socket_server*) ; 
 int MAX_SOCKET ; 
 scalar_t__ SOCKET_TYPE_RESERVE ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_close (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  socket_lock_init (struct socket*,struct socket_lock*) ; 
 int /*<<< orphan*/  sp_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spinlock_destroy (int /*<<< orphan*/ *) ; 

void 
socket_server_release(struct socket_server *ss) {
	int i;
	struct socket_message dummy;
	for (i=0;i<MAX_SOCKET;i++) {
		struct socket *s = &ss->slot[i];
		struct socket_lock l;
		socket_lock_init(s, &l);
		if (s->type != SOCKET_TYPE_RESERVE) {
			force_close(ss, s, &l, &dummy);
		}
		spinlock_destroy(&s->dw_lock);
	}
	close(ss->sendctrl_fd);
	close(ss->recvctrl_fd);
	sp_release(ss->event_fd);
	FREE(ss);
}