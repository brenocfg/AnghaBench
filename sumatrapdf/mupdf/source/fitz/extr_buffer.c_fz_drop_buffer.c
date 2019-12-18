#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {struct TYPE_5__* data; int /*<<< orphan*/  shared; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 scalar_t__ fz_drop_imp (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_buffer(fz_context *ctx, fz_buffer *buf)
{
	if (fz_drop_imp(ctx, buf, &buf->refs))
	{
		if (!buf->shared)
			fz_free(ctx, buf->data);
		fz_free(ctx, buf);
	}
}