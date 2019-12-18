#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ svg_device ;
struct TYPE_6__ {float linewidth; scalar_t__ start_cap; scalar_t__ dash_len; char* dash_phase; scalar_t__ linejoin; char* miterlimit; int /*<<< orphan*/ * dash_list; } ;
typedef  TYPE_2__ fz_stroke_state ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_LINECAP_ROUND ; 
 scalar_t__ FZ_LINECAP_SQUARE ; 
 scalar_t__ FZ_LINEJOIN_BEVEL ; 
 scalar_t__ FZ_LINEJOIN_MITER ; 
 scalar_t__ FZ_LINEJOIN_MITER_XPS ; 
 scalar_t__ FZ_LINEJOIN_ROUND ; 
 float fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
svg_dev_stroke_state(fz_context *ctx, svg_device *sdev, const fz_stroke_state *stroke_state, fz_matrix ctm)
{
	fz_output *out = sdev->out;
	float exp;

	exp = fz_matrix_expansion(ctm);
	if (exp == 0)
		exp = 1;
	exp = stroke_state->linewidth/exp;

	fz_write_printf(ctx, out, " stroke-width=\"%g\"", exp);
	fz_write_printf(ctx, out, " stroke-linecap=\"%s\"",
		(stroke_state->start_cap == FZ_LINECAP_SQUARE ? "square" :
			(stroke_state->start_cap == FZ_LINECAP_ROUND ? "round" : "butt")));
	if (stroke_state->dash_len != 0)
	{
		int i;
		fz_write_printf(ctx, out, " stroke-dasharray=");
		for (i = 0; i < stroke_state->dash_len; i++)
			fz_write_printf(ctx, out, "%c%g", (i == 0 ? '\"' : ','), stroke_state->dash_list[i]);
		fz_write_printf(ctx, out, "\"");
		if (stroke_state->dash_phase != 0)
			fz_write_printf(ctx, out, " stroke-dashoffset=\"%g\"", stroke_state->dash_phase);
	}
	if (stroke_state->linejoin == FZ_LINEJOIN_MITER || stroke_state->linejoin == FZ_LINEJOIN_MITER_XPS)
		fz_write_printf(ctx, out, " stroke-miterlimit=\"%g\"", stroke_state->miterlimit);
	fz_write_printf(ctx, out, " stroke-linejoin=\"%s\"",
		(stroke_state->linejoin == FZ_LINEJOIN_BEVEL ? "bevel" :
			(stroke_state->linejoin == FZ_LINEJOIN_ROUND ? "round" : "miter")));
}