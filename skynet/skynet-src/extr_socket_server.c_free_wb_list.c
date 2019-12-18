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
struct write_buffer {struct write_buffer* next; } ;
struct wb_list {int /*<<< orphan*/ * tail; struct write_buffer* head; } ;
struct socket_server {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_buffer_free (struct socket_server*,struct write_buffer*) ; 

__attribute__((used)) static void
free_wb_list(struct socket_server *ss, struct wb_list *list) {
	struct write_buffer *wb = list->head;
	while (wb) {
		struct write_buffer *tmp = wb;
		wb = wb->next;
		write_buffer_free(ss, tmp);
	}
	list->head = NULL;
	list->tail = NULL;
}