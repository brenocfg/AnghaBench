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
struct socket_sendbuffer {int type; size_t sz; void const* buffer; } ;

/* Variables and functions */
 void* MALLOC (size_t) ; 
#define  SOCKET_BUFFER_MEMORY 130 
#define  SOCKET_BUFFER_OBJECT 129 
#define  SOCKET_BUFFER_RAWPOINTER 128 
 size_t USEROBJECT ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static const void *
clone_buffer(struct socket_sendbuffer *buf, size_t *sz) {
	switch (buf->type) {
	case SOCKET_BUFFER_MEMORY:
		*sz = buf->sz;
		return buf->buffer;
	case SOCKET_BUFFER_OBJECT:
		*sz = USEROBJECT;
		return buf->buffer;
	case SOCKET_BUFFER_RAWPOINTER:
		// It's a raw pointer, we need make a copy
		*sz = buf->sz;
		void * tmp = MALLOC(*sz);
		memcpy(tmp, buf->buffer, *sz);
		return tmp;
	}
	// never get here
	*sz = 0;
	return NULL;
}