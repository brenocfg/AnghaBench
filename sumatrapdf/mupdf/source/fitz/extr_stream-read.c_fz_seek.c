#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ eof; int /*<<< orphan*/  (* seek ) (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int) ;scalar_t__ avail; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ EOF ; 
 scalar_t__ fz_read_byte (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ fz_tell (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int) ; 

void
fz_seek(fz_context *ctx, fz_stream *stm, int64_t offset, int whence)
{
	stm->avail = 0; /* Reset bit reading */
	if (stm->seek)
	{
		if (whence == 1)
		{
			offset += fz_tell(ctx, stm);
			whence = 0;
		}
		stm->seek(ctx, stm, offset, whence);
		stm->eof = 0;
	}
	else if (whence != 2)
	{
		if (whence == 0)
			offset -= fz_tell(ctx, stm);
		if (offset < 0)
			fz_warn(ctx, "cannot seek backwards");
		/* dog slow, but rare enough */
		while (offset-- > 0)
		{
			if (fz_read_byte(ctx, stm) == EOF)
			{
				fz_warn(ctx, "seek failed");
				break;
			}
		}
	}
	else
		fz_warn(ctx, "cannot seek");
}