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
union sockaddr_all {int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  u ;
struct socket_server {int /*<<< orphan*/ * buffer; } ;
struct socket_message {int ud; int /*<<< orphan*/ * data; int /*<<< orphan*/  id; int /*<<< orphan*/  opaque; } ;
struct socket {int /*<<< orphan*/  id; int /*<<< orphan*/  opaque; int /*<<< orphan*/  type; int /*<<< orphan*/  fd; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 int /*<<< orphan*/  PROTOCOL_TCP ; 
 int /*<<< orphan*/  SOCKET_TYPE_PACCEPT ; 
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ getname (union sockaddr_all*,int /*<<< orphan*/ *,int) ; 
 struct socket* new_fd (struct socket_server*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int reserve_id (struct socket_server*) ; 
 int /*<<< orphan*/  socket_keepalive (int) ; 
 int /*<<< orphan*/  sp_nonblocking (int) ; 
 int /*<<< orphan*/  stat_read (struct socket_server*,struct socket*,int) ; 
 int /*<<< orphan*/ * strerror (scalar_t__) ; 

__attribute__((used)) static int
report_accept(struct socket_server *ss, struct socket *s, struct socket_message *result) {
	union sockaddr_all u;
	socklen_t len = sizeof(u);
	int client_fd = accept(s->fd, &u.s, &len);
	if (client_fd < 0) {
		if (errno == EMFILE || errno == ENFILE) {
			result->opaque = s->opaque;
			result->id = s->id;
			result->ud = 0;
			result->data = strerror(errno);
			return -1;
		} else {
			return 0;
		}
	}
	int id = reserve_id(ss);
	if (id < 0) {
		close(client_fd);
		return 0;
	}
	socket_keepalive(client_fd);
	sp_nonblocking(client_fd);
	struct socket *ns = new_fd(ss, id, client_fd, PROTOCOL_TCP, s->opaque, false);
	if (ns == NULL) {
		close(client_fd);
		return 0;
	}
	// accept new one connection
	stat_read(ss,s,1);

	ns->type = SOCKET_TYPE_PACCEPT;
	result->opaque = s->opaque;
	result->id = s->id;
	result->ud = id;
	result->data = NULL;

	if (getname(&u, ss->buffer, sizeof(ss->buffer))) {
		result->data = ss->buffer;
	}

	return 1;
}