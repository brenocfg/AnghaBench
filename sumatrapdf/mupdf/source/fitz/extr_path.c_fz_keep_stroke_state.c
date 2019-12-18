#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int refs; } ;
typedef  TYPE_1__ fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_clone_stroke_state (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_keep_imp (int /*<<< orphan*/ *,TYPE_1__*,int*) ; 

fz_stroke_state *
fz_keep_stroke_state(fz_context *ctx, const fz_stroke_state *strokec)
{
	fz_stroke_state *stroke = (fz_stroke_state *)strokec; /* Explicit cast away of const */

	if (!stroke)
		return NULL;

	/* -2 is the magic number we use when we have stroke states stored on the stack */
	if (stroke->refs == -2)
		return fz_clone_stroke_state(ctx, stroke);

	return fz_keep_imp(ctx, stroke, &stroke->refs);
}