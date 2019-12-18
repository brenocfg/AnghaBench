#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_new_stroke_state_with_dash_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

fz_stroke_state *
fz_new_stroke_state(fz_context *ctx)
{
	return fz_new_stroke_state_with_dash_len(ctx, 0);
}