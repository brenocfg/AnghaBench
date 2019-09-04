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
struct socket_server {int /*<<< orphan*/  event_fd; } ;
struct socket_message {int /*<<< orphan*/  opaque; int /*<<< orphan*/ * data; scalar_t__ ud; int /*<<< orphan*/  id; } ;
struct socket_lock {int dummy; } ;
struct socket {scalar_t__ type; int /*<<< orphan*/ * dw_buffer; int /*<<< orphan*/  dw_size; int /*<<< orphan*/  fd; int /*<<< orphan*/  low; int /*<<< orphan*/  high; int /*<<< orphan*/  opaque; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ SOCKET_TYPE_BIND ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 scalar_t__ SOCKET_TYPE_PACCEPT ; 
 scalar_t__ SOCKET_TYPE_PLISTEN ; 
 scalar_t__ SOCKET_TYPE_RESERVE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_buffer (struct socket_server*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_wb_list (struct socket_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  socket_lock (struct socket_lock*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket_lock*) ; 
 int /*<<< orphan*/  sp_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
force_close(struct socket_server *ss, struct socket *s, struct socket_lock *l, struct socket_message *result) {
	result->id = s->id;
	result->ud = 0;
	result->data = NULL;
	result->opaque = s->opaque;
	if (s->type == SOCKET_TYPE_INVALID) {
		return;
	}
	assert(s->type != SOCKET_TYPE_RESERVE);
	free_wb_list(ss,&s->high);
	free_wb_list(ss,&s->low);
	if (s->type != SOCKET_TYPE_PACCEPT && s->type != SOCKET_TYPE_PLISTEN) {
		sp_del(ss->event_fd, s->fd);
	}
	socket_lock(l);
	if (s->type != SOCKET_TYPE_BIND) {
		if (close(s->fd) < 0) {
			perror("close socket:");
		}
	}
	s->type = SOCKET_TYPE_INVALID;
	if (s->dw_buffer) {
		free_buffer(ss, s->dw_buffer, s->dw_size);
		s->dw_buffer = NULL;
	}
	socket_unlock(l);
}