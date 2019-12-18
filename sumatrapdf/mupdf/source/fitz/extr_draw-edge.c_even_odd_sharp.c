#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_solid_color_painter_t ;
typedef  int /*<<< orphan*/  fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_irect ;
struct TYPE_5__ {int alen; TYPE_1__** active; } ;
typedef  TYPE_2__ fz_gel ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int x; } ;

/* Variables and functions */
 int /*<<< orphan*/  blit_sharp (int,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
even_odd_sharp(fz_context *ctx, fz_gel *gel, int y, const fz_irect *clip, fz_pixmap *dst, unsigned char *color, fz_solid_color_painter_t *fn, fz_overprint *eop)
{
	int even = 0;
	int x = 0;
	int i;
	for (i = 0; i < gel->alen; i++)
	{
		if (!even)
			x = gel->active[i]->x;
		else
			blit_sharp(x, gel->active[i]->x, y, clip, dst, color, fn, eop);
		even = !even;
	}
}