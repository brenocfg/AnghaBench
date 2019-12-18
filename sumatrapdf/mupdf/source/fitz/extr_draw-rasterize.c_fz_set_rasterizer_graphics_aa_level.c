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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int hscale; int vscale; int bits; int scale; } ;
typedef  TYPE_1__ fz_aa_context ;

/* Variables and functions */
 int fz_aa_bits ; 
 int /*<<< orphan*/  fz_set_rasterizer_text_aa_level (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,...) ; 

void
fz_set_rasterizer_graphics_aa_level(fz_context *ctx, fz_aa_context *aa, int level)
{
#ifdef AA_BITS
	if (level != fz_aa_bits)
	{
		if (fz_aa_bits == 10)
			fz_warn(ctx, "Only the Any-part-of-a-pixel rasterizer was compiled in");
		else if (fz_aa_bits == 9)
			fz_warn(ctx, "Only the Centre-of-a-pixel rasterizer was compiled in");
		else
			fz_warn(ctx, "Only the %d bit anti-aliasing rasterizer was compiled in", fz_aa_bits);
	}
#else
	if (level == 9 || level == 10)
	{
		aa->hscale = 1;
		aa->vscale = 1;
		aa->bits = level;
	}
	else if (level > 6)
	{
		aa->hscale = 17;
		aa->vscale = 15;
		aa->bits = 8;
	}
	else if (level > 4)
	{
		aa->hscale = 8;
		aa->vscale = 8;
		aa->bits = 6;
	}
	else if (level > 2)
	{
		aa->hscale = 5;
		aa->vscale = 3;
		aa->bits = 4;
	}
	else if (level > 0)
	{
		aa->hscale = 2;
		aa->vscale = 2;
		aa->bits = 2;
	}
	else
	{
		aa->hscale = 1;
		aa->vscale = 1;
		aa->bits = 0;
	}
	aa->scale = 0xFF00 / (aa->hscale * aa->vscale);
	fz_set_rasterizer_text_aa_level(ctx, aa, level);
#endif
}