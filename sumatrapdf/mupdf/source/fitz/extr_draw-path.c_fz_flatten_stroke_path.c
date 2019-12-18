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
typedef  int /*<<< orphan*/  fz_rasterizer ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int do_flatten_stroke (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,float,float,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_postindex_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_reset_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

int
fz_flatten_stroke_path(fz_context *ctx, fz_rasterizer *rast, const fz_path *path, const fz_stroke_state *stroke, fz_matrix ctm, float flatness, float linewidth, const fz_irect *scissor, fz_irect *bbox)
{
	if (fz_reset_rasterizer(ctx, rast, *scissor))
	{
		if (do_flatten_stroke(ctx, rast, path, stroke, ctm, flatness, linewidth, scissor, bbox))
			return 1;
		fz_postindex_rasterizer(ctx, rast);
		bbox = NULL;
	}

	return do_flatten_stroke(ctx, rast, path, stroke, ctm, flatness, linewidth, scissor, bbox);
}