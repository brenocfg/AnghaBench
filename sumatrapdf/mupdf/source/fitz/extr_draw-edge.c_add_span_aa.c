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
struct TYPE_3__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ fz_gel ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_rasterizer_aa_hscale (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
add_span_aa(fz_context *ctx, fz_gel *gel, int *list, int x0, int x1, int xofs, int h)
{
	int x0pix, x0sub;
	int x1pix, x1sub;
	const int hscale = fz_rasterizer_aa_hscale(&gel->super);

	if (x0 == x1)
		return;

	/* x between 0 and width of bbox */
	x0 -= xofs;
	x1 -= xofs;

	/* The cast to unsigned below helps the compiler produce faster
	 * code on ARMs as the multiply by reciprocal trick it uses does not
	 * need to correct for signedness. */
	x0pix = ((unsigned int)x0) / hscale;
	x0sub = ((unsigned int)x0) % hscale;
	x1pix = ((unsigned int)x1) / hscale;
	x1sub = ((unsigned int)x1) % hscale;

	if (x0pix == x1pix)
	{
		list[x0pix] += h*(x1sub - x0sub);
		list[x0pix+1] += h*(x0sub - x1sub);
	}

	else
	{
		list[x0pix] += h*(hscale - x0sub);
		list[x0pix+1] += h*x0sub;
		list[x1pix] += h*(x1sub - hscale);
		list[x1pix+1] += h*-x1sub;
	}
}