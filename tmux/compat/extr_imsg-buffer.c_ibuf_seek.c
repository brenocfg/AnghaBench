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
struct ibuf {size_t wpos; void* buf; } ;

/* Variables and functions */

void *
ibuf_seek(struct ibuf *buf, size_t pos, size_t len)
{
	/* only allowed to seek in already written parts */
	if (pos + len > buf->wpos)
		return (NULL);

	return (buf->buf + pos);
}