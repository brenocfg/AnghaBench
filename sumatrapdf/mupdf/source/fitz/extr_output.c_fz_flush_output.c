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
struct TYPE_3__ {scalar_t__ wp; scalar_t__ bp; int /*<<< orphan*/  state; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;
typedef  TYPE_1__ fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
fz_flush_output(fz_context *ctx, fz_output *out)
{
	if (out->wp > out->bp)
	{
		out->write(ctx, out->state, out->bp, out->wp - out->bp);
		out->wp = out->bp;
	}
}