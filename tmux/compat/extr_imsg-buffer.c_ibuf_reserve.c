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
struct ibuf {scalar_t__ wpos; scalar_t__ size; void* buf; } ;

/* Variables and functions */
 int ibuf_realloc (struct ibuf*,size_t) ; 

void *
ibuf_reserve(struct ibuf *buf, size_t len)
{
	void	*b;

	if (buf->wpos + len > buf->size)
		if (ibuf_realloc(buf, len) == -1)
			return (NULL);

	b = buf->buf + buf->wpos;
	buf->wpos += len;
	return (b);
}