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
struct write_buffer {char* ptr; struct write_buffer* next; int /*<<< orphan*/  buffer; int /*<<< orphan*/  sz; int /*<<< orphan*/  userobject; } ;
struct wb_list {struct write_buffer* tail; struct write_buffer* head; } ;
struct socket_server {int dummy; } ;
struct send_object {int /*<<< orphan*/  sz; scalar_t__ buffer; } ;
struct request_send {int /*<<< orphan*/  buffer; int /*<<< orphan*/  sz; } ;

/* Variables and functions */
 struct write_buffer* MALLOC (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_object_init (struct socket_server*,struct send_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct write_buffer *
append_sendbuffer_(struct socket_server *ss, struct wb_list *s, struct request_send * request, int size) {
	struct write_buffer * buf = MALLOC(size);
	struct send_object so;
	buf->userobject = send_object_init(ss, &so, request->buffer, request->sz);
	buf->ptr = (char*)so.buffer;
	buf->sz = so.sz;
	buf->buffer = request->buffer;
	buf->next = NULL;
	if (s->head == NULL) {
		s->head = s->tail = buf;
	} else {
		assert(s->tail != NULL);
		assert(s->tail->next == NULL);
		s->tail->next = buf;
		s->tail = buf;
	}
	return buf;
}