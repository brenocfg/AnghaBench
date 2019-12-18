#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct write_buffer {char* ptr; int sz; struct write_buffer* next; void* buffer; int /*<<< orphan*/  userobject; } ;
struct socket_server {int dummy; } ;
struct socket_message {int dummy; } ;
struct socket_lock {int dummy; } ;
struct TYPE_2__ {struct write_buffer* head; struct write_buffer* tail; } ;
struct socket {int dw_offset; int /*<<< orphan*/ * dw_buffer; TYPE_1__ high; int /*<<< orphan*/  wb_size; int /*<<< orphan*/  dw_size; } ;
struct send_object {int sz; scalar_t__ buffer; } ;

/* Variables and functions */
 struct write_buffer* MALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZEOF_TCPBUFFER ; 
 int send_buffer_ (struct socket_server*,struct socket*,struct socket_lock*,struct socket_message*) ; 
 int /*<<< orphan*/  send_object_init (struct socket_server*,struct send_object*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_trylock (struct socket_lock*) ; 
 int /*<<< orphan*/  socket_unlock (struct socket_lock*) ; 

__attribute__((used)) static int
send_buffer(struct socket_server *ss, struct socket *s, struct socket_lock *l, struct socket_message *result) {
	if (!socket_trylock(l))
		return -1;	// blocked by direct write, send later.
	if (s->dw_buffer) {
		// add direct write buffer before high.head
		struct write_buffer * buf = MALLOC(SIZEOF_TCPBUFFER);
		struct send_object so;
		buf->userobject = send_object_init(ss, &so, (void *)s->dw_buffer, s->dw_size);
		buf->ptr = (char*)so.buffer+s->dw_offset;
		buf->sz = so.sz - s->dw_offset;
		buf->buffer = (void *)s->dw_buffer;
		s->wb_size+=buf->sz;
		if (s->high.head == NULL) {
			s->high.head = s->high.tail = buf;
			buf->next = NULL;
		} else {
			buf->next = s->high.head;
			s->high.head = buf;
		}
		s->dw_buffer = NULL;
	}
	int r = send_buffer_(ss,s,l,result);
	socket_unlock(l);

	return r;
}