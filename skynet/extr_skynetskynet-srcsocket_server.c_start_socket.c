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
struct socket_server {int /*<<< orphan*/  event_fd; struct socket* slot; } ;
struct socket_message {int id; char* data; scalar_t__ ud; int /*<<< orphan*/  opaque; } ;
struct socket_lock {int dummy; } ;
struct socket {scalar_t__ type; int id; int /*<<< orphan*/  opaque; int /*<<< orphan*/  fd; } ;
struct request_start {int id; int /*<<< orphan*/  opaque; } ;

/* Variables and functions */
 size_t HASH_ID (int) ; 
 int SOCKET_ERR ; 
 int SOCKET_OPEN ; 
 scalar_t__ SOCKET_TYPE_CONNECTED ; 
 scalar_t__ SOCKET_TYPE_INVALID ; 
 scalar_t__ SOCKET_TYPE_LISTEN ; 
 scalar_t__ SOCKET_TYPE_PACCEPT ; 
 scalar_t__ SOCKET_TYPE_PLISTEN ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  force_close (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  socket_lock_init (struct socket*,struct socket_lock*) ; 
 scalar_t__ sp_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
start_socket(struct socket_server *ss, struct request_start *request, struct socket_message *result) {
	int id = request->id;
	result->id = id;
	result->opaque = request->opaque;
	result->ud = 0;
	result->data = NULL;
	struct socket *s = &ss->slot[HASH_ID(id)];
	if (s->type == SOCKET_TYPE_INVALID || s->id !=id) {
		result->data = "invalid socket";
		return SOCKET_ERR;
	}
	struct socket_lock l;
	socket_lock_init(s, &l);
	if (s->type == SOCKET_TYPE_PACCEPT || s->type == SOCKET_TYPE_PLISTEN) {
		if (sp_add(ss->event_fd, s->fd, s)) {
			force_close(ss, s, &l, result);
			result->data = strerror(errno);
			return SOCKET_ERR;
		}
		s->type = (s->type == SOCKET_TYPE_PACCEPT) ? SOCKET_TYPE_CONNECTED : SOCKET_TYPE_LISTEN;
		s->opaque = request->opaque;
		result->data = "start";
		return SOCKET_OPEN;
	} else if (s->type == SOCKET_TYPE_CONNECTED) {
		// todo: maybe we should send a message SOCKET_TRANSFER to s->opaque
		s->opaque = request->opaque;
		result->data = "transfer";
		return SOCKET_OPEN;
	}
	// if s->type == SOCKET_TYPE_HALFCLOSE , SOCKET_CLOSE message will send later
	return -1;
}