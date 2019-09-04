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
struct buffer {char* data; int size; } ;

/* Variables and functions */
 char* memchr (char*,int,int) ; 

char *
io_memchr(struct buffer *buf, char *data, int c)
{
	char *pos;

	if (!buf || data < buf->data || buf->data + buf->size <= data)
		return NULL;

	pos = memchr(data, c, buf->size - (data - buf->data));
	return pos ? pos + 1 : NULL;
}