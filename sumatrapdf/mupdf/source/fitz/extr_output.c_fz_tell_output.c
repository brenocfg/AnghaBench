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
struct TYPE_3__ {int /*<<< orphan*/  state; scalar_t__ (* tell ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ bp; scalar_t__ wp; } ;
typedef  TYPE_1__ fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int64_t
fz_tell_output(fz_context *ctx, fz_output *out)
{
	if (out->tell == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot tell in untellable output stream\n");
	if (out->bp)
		return out->tell(ctx, out->state) + (out->wp - out->bp);
	return out->tell(ctx, out->state);
}