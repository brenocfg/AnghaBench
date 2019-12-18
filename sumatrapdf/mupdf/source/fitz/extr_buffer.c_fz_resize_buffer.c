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
struct TYPE_3__ {size_t cap; size_t len; int /*<<< orphan*/  data; scalar_t__ shared; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
fz_resize_buffer(fz_context *ctx, fz_buffer *buf, size_t size)
{
	if (buf->shared)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot resize a buffer with shared storage");
	buf->data = fz_realloc(ctx, buf->data, size);
	buf->cap = size;
	if (buf->len > buf->cap)
		buf->len = buf->cap;
}