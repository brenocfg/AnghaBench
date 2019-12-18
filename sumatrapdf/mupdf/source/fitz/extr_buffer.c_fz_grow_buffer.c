#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int cap; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_resize_buffer (int /*<<< orphan*/ *,TYPE_1__*,size_t) ; 

void
fz_grow_buffer(fz_context *ctx, fz_buffer *buf)
{
	size_t newsize = (buf->cap * 3) / 2;
	if (newsize == 0)
		newsize = 256;
	fz_resize_buffer(ctx, buf, newsize);
}