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
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_CMD_STROKE_PATH ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,float const*,int /*<<< orphan*/ *,float*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_bound_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_pack_color_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_list_stroke_path(fz_context *ctx, fz_device *dev, const fz_path *path, const fz_stroke_state *stroke,
	fz_matrix ctm, fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	fz_rect rect = fz_bound_path(ctx, path, stroke, ctm);
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_STROKE_PATH,
		fz_pack_color_params(color_params), /* flags */
		&rect,
		path, /* path */
		color,
		colorspace,
		&alpha, /* alpha */
		&ctm, /* ctm */
		stroke,
		NULL, /* private_data */
		0); /* private_data_len */
}