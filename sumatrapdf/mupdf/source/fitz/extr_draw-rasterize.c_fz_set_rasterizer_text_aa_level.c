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
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int text_bits; } ;
typedef  TYPE_1__ fz_aa_context ;

/* Variables and functions */
 int fz_aa_bits ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,...) ; 

void
fz_set_rasterizer_text_aa_level(fz_context *ctx, fz_aa_context *aa, int level)
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
	if (level > 8)
		aa->text_bits = 0;
	else if (level > 6)
		aa->text_bits = 8;
	else if (level > 4)
		aa->text_bits = 6;
	else if (level > 2)
		aa->text_bits = 4;
	else if (level > 0)
		aa->text_bits = 2;
	else
		aa->text_bits = 0;
#endif
}