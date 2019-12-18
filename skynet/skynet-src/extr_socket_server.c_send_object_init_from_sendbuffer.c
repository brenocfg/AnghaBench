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
struct socket_server {int dummy; } ;
struct socket_sendbuffer {int type; int /*<<< orphan*/  sz; scalar_t__ buffer; } ;
struct send_object {int /*<<< orphan*/ * free_func; int /*<<< orphan*/  sz; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
#define  SOCKET_BUFFER_MEMORY 130 
#define  SOCKET_BUFFER_OBJECT 129 
#define  SOCKET_BUFFER_RAWPOINTER 128 
 int /*<<< orphan*/  USEROBJECT ; 
 int /*<<< orphan*/ * dummy_free ; 
 int /*<<< orphan*/  send_object_init (struct socket_server*,struct send_object*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
send_object_init_from_sendbuffer(struct socket_server *ss, struct send_object *so, struct socket_sendbuffer *buf) {
	switch (buf->type) {
	case SOCKET_BUFFER_MEMORY:
		send_object_init(ss, so, (void *)buf->buffer, buf->sz);
		break;
	case SOCKET_BUFFER_OBJECT:
		send_object_init(ss, so, (void *)buf->buffer, USEROBJECT);
		break;
	case SOCKET_BUFFER_RAWPOINTER:
		so->buffer = (void *)buf->buffer;
		so->sz = buf->sz;
		so->free_func = dummy_free;
		break;
	default:
		// never get here
		so->buffer = NULL;
		so->sz = 0;
		so->free_func = NULL;
		break;
	}
}