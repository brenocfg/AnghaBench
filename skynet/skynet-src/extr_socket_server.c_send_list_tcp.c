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
struct write_buffer {scalar_t__ sz; struct write_buffer* next; int /*<<< orphan*/  ptr; } ;
struct wb_list {int /*<<< orphan*/ * tail; struct write_buffer* head; } ;
struct socket_server {int dummy; } ;
struct socket_message {int dummy; } ;
struct socket_lock {int dummy; } ;
struct socket {int /*<<< orphan*/  wb_size; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
#define  AGAIN_WOULDBLOCK 129 
#define  EINTR 128 
 int SOCKET_CLOSE ; 
 int errno ; 
 int /*<<< orphan*/  force_close (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  stat_write (struct socket_server*,struct socket*,int) ; 
 scalar_t__ write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_buffer_free (struct socket_server*,struct write_buffer*) ; 

__attribute__((used)) static int
send_list_tcp(struct socket_server *ss, struct socket *s, struct wb_list *list, struct socket_lock *l, struct socket_message *result) {
	while (list->head) {
		struct write_buffer * tmp = list->head;
		for (;;) {
			ssize_t sz = write(s->fd, tmp->ptr, tmp->sz);
			if (sz < 0) {
				switch(errno) {
				case EINTR:
					continue;
				case AGAIN_WOULDBLOCK:
					return -1;
				}
				force_close(ss,s,l,result);
				return SOCKET_CLOSE;
			}
			stat_write(ss,s,(int)sz);
			s->wb_size -= sz;
			if (sz != tmp->sz) {
				tmp->ptr += sz;
				tmp->sz -= sz;
				return -1;
			}
			break;
		}
		list->head = tmp->next;
		write_buffer_free(ss,tmp);
	}
	list->tail = NULL;

	return -1;
}