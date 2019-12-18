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
typedef  int /*<<< orphan*/  uint64_t ;
struct socket_server {int recvctrl_fd; int sendctrl_fd; int checkctrl; int /*<<< orphan*/  rfds; int /*<<< orphan*/  soi; scalar_t__ event_index; scalar_t__ event_n; scalar_t__ alloc_id; struct socket* slot; int /*<<< orphan*/  event_fd; int /*<<< orphan*/  time; } ;
struct socket {int /*<<< orphan*/  dw_lock; int /*<<< orphan*/  low; int /*<<< orphan*/  high; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  poll_fd ;

/* Variables and functions */
 int FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 struct socket_server* MALLOC (int) ; 
 int MAX_SOCKET ; 
 int /*<<< orphan*/  SOCKET_TYPE_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_wb_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ sp_add (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp_create () ; 
 scalar_t__ sp_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

struct socket_server * 
socket_server_create(uint64_t time) {
	int i;
	int fd[2];
	poll_fd efd = sp_create();
	if (sp_invalid(efd)) {
		fprintf(stderr, "socket-server: create event pool failed.\n");
		return NULL;
	}
	if (pipe(fd)) {
		sp_release(efd);
		fprintf(stderr, "socket-server: create socket pair failed.\n");
		return NULL;
	}
	if (sp_add(efd, fd[0], NULL)) {
		// add recvctrl_fd to event poll
		fprintf(stderr, "socket-server: can't add server fd to event pool.\n");
		close(fd[0]);
		close(fd[1]);
		sp_release(efd);
		return NULL;
	}

	struct socket_server *ss = MALLOC(sizeof(*ss));
	ss->time = time;
	ss->event_fd = efd;
	ss->recvctrl_fd = fd[0];
	ss->sendctrl_fd = fd[1];
	ss->checkctrl = 1;

	for (i=0;i<MAX_SOCKET;i++) {
		struct socket *s = &ss->slot[i];
		s->type = SOCKET_TYPE_INVALID;
		clear_wb_list(&s->high);
		clear_wb_list(&s->low);
		spinlock_init(&s->dw_lock);
	}
	ss->alloc_id = 0;
	ss->event_n = 0;
	ss->event_index = 0;
	memset(&ss->soi, 0, sizeof(ss->soi));
	FD_ZERO(&ss->rfds);
	assert(ss->recvctrl_fd < FD_SETSIZE);

	return ss;
}