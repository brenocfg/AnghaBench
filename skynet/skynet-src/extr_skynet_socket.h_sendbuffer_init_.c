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
struct socket_sendbuffer {int id; size_t sz; int /*<<< orphan*/  type; void const* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKET_BUFFER_MEMORY ; 
 int /*<<< orphan*/  SOCKET_BUFFER_OBJECT ; 

__attribute__((used)) static inline void sendbuffer_init_(struct socket_sendbuffer *buf, int id, const void *buffer, int sz) {
	buf->id = id;
	buf->buffer = buffer;
	if (sz < 0) {
		buf->type = SOCKET_BUFFER_OBJECT;
	} else {
		buf->type = SOCKET_BUFFER_MEMORY;
	}
	buf->sz = (size_t)sz;
}