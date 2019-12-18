#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {size_t len; unsigned char* data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */

size_t
fz_buffer_extract(fz_context *ctx, fz_buffer *buf, unsigned char **datap)
{
	size_t len = buf ? buf->len : 0;
	*datap = (buf ? buf->data : NULL);

	if (buf)
	{
		buf->data = NULL;
		buf->len = 0;
	}
	return len;
}