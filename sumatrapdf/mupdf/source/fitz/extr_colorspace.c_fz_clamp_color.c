#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int high; } ;
struct TYPE_6__ {TYPE_1__ indexed; } ;
struct TYPE_7__ {scalar_t__ type; int n; TYPE_2__ u; } ;
typedef  TYPE_3__ fz_colorspace ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_INDEXED ; 
 scalar_t__ FZ_COLORSPACE_LAB ; 
 float fz_clamp (float const,int,int) ; 

void
fz_clamp_color(fz_context *ctx, fz_colorspace *cs, const float *in, float *out)
{
	if (cs->type == FZ_COLORSPACE_LAB)
	{
		out[0] = fz_clamp(in[0], 0, 100);
		out[1] = fz_clamp(in[1], -128, 127);
		out[2] = fz_clamp(in[2], -128, 127);
	}
	else if (cs->type == FZ_COLORSPACE_INDEXED)
	{
		out[0] = fz_clamp(in[0], 0, cs->u.indexed.high) / 255.0f;
	}
	else
	{
		int i, n = cs->n;
		for (i = 0; i < n; ++i)
			out[i] = fz_clamp(in[i], 0, 1);
	}
}