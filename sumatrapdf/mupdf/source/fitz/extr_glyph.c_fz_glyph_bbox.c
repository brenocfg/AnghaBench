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
struct TYPE_5__ {scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_6__ {scalar_t__ h; scalar_t__ y; scalar_t__ w; scalar_t__ x; } ;
typedef  TYPE_2__ fz_glyph ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

fz_irect
fz_glyph_bbox(fz_context *ctx, fz_glyph *glyph)
{
	fz_irect bbox;
	bbox.x0 = glyph->x;
	bbox.y0 = glyph->y;
	bbox.x1 = glyph->x + glyph->w;
	bbox.y1 = glyph->y + glyph->h;
	return bbox;
}