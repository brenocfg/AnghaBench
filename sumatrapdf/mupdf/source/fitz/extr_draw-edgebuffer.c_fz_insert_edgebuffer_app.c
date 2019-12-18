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
typedef  int /*<<< orphan*/  fz_rasterizer ;
struct TYPE_5__ {float x0; float x1; float y0; float y1; } ;
struct TYPE_6__ {TYPE_1__ bbox; } ;
struct TYPE_7__ {TYPE_2__ super; } ;
typedef  TYPE_3__ fz_edgebuffer ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fixed ;

/* Variables and functions */
 int /*<<< orphan*/  float2fixed (float) ; 
 int /*<<< orphan*/  mark_line_app (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fz_insert_edgebuffer_app(fz_context *ctx, fz_rasterizer *ras, float fsx, float fsy, float fex, float fey, int rev)
{
	fz_edgebuffer *eb = (fz_edgebuffer *)ras;
	fixed sx = float2fixed(fsx);
	fixed sy = float2fixed(fsy);
	fixed ex = float2fixed(fex);
	fixed ey = float2fixed(fey);

	if (fsx < fex)
	{
		if (fsx < eb->super.bbox.x0) eb->super.bbox.x0 = fsx;
		if (fex > eb->super.bbox.x1) eb->super.bbox.x1 = fex;
	}
	else
	{
		if (fsx > eb->super.bbox.x1) eb->super.bbox.x1 = fsx;
		if (fex < eb->super.bbox.x0) eb->super.bbox.x0 = fex;
	}
	if (fsy < fey)
	{
		if (fsy < eb->super.bbox.y0) eb->super.bbox.y0 = fsy;
		if (fey > eb->super.bbox.y1) eb->super.bbox.y1 = fey;
	}
	else
	{
		if (fey < eb->super.bbox.y0) eb->super.bbox.y0 = fey;
		if (fsy > eb->super.bbox.y1) eb->super.bbox.y1 = fsy;
	}

	mark_line_app(ctx, eb, sx, sy, ex, ey, rev);
}