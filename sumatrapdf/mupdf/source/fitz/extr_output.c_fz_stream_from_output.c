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
typedef  int /*<<< orphan*/  fz_stream ;
struct TYPE_4__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * (* as_stream ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_flush_output (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

fz_stream *
fz_stream_from_output(fz_context *ctx, fz_output *out)
{
	if (out->as_stream == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "Cannot derive input stream from output stream");
	fz_flush_output(ctx, out);
	return out->as_stream(ctx, out->state);
}