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
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (void*) ;} ;
struct socket_server {TYPE_1__ soi; } ;
struct socket_sendbuffer {int type; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (void*) ; 
#define  SOCKET_BUFFER_MEMORY 130 
#define  SOCKET_BUFFER_OBJECT 129 
#define  SOCKET_BUFFER_RAWPOINTER 128 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
free_buffer(struct socket_server *ss, struct socket_sendbuffer *buf) {
	void *buffer = (void *)buf->buffer;
	switch (buf->type) {
	case SOCKET_BUFFER_MEMORY:
		FREE((void *)buffer);
		break;
	case SOCKET_BUFFER_OBJECT:
		ss->soi.free(buffer);
		break;
	case SOCKET_BUFFER_RAWPOINTER:
		break;
	}
}