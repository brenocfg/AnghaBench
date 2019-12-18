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
struct write_buffer {int /*<<< orphan*/ * next; scalar_t__ sz; } ;
struct wb_list {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; } ;
struct socket_server {int dummy; } ;
struct socket {int /*<<< orphan*/  wb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_buffer_free (struct socket_server*,struct write_buffer*) ; 

__attribute__((used)) static void
drop_udp(struct socket_server *ss, struct socket *s, struct wb_list *list, struct write_buffer *tmp) {
	s->wb_size -= tmp->sz;
	list->head = tmp->next;
	if (list->head == NULL)
		list->tail = NULL;
	write_buffer_free(ss,tmp);
}