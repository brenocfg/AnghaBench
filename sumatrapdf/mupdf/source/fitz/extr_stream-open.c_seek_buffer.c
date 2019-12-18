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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ pos; scalar_t__ wp; scalar_t__ rp; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void seek_buffer(fz_context *ctx, fz_stream *stm, int64_t offset, int whence)
{
	int64_t pos = stm->pos - (stm->wp - stm->rp);
	/* Convert to absolute pos */
	if (whence == 1)
	{
		offset += pos; /* Was relative to current pos */
	}
	else if (whence == 2)
	{
		offset += stm->pos; /* Was relative to end */
	}

	if (offset < 0)
		offset = 0;
	if (offset > stm->pos)
		offset = stm->pos;
	stm->rp += (int)(offset - pos);
}