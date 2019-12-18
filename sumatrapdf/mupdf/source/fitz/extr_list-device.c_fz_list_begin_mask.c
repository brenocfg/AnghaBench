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
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_CMD_BEGIN_MASK ; 
 int /*<<< orphan*/  fz_append_display_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fz_pack_color_params (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_list_begin_mask(fz_context *ctx, fz_device *dev, fz_rect rect, int luminosity, fz_colorspace *colorspace, const float *color, fz_color_params color_params)
{
	fz_append_display_node(
		ctx,
		dev,
		FZ_CMD_BEGIN_MASK,
		(!!luminosity) | fz_pack_color_params(color_params), /* flags */
		&rect,
		NULL, /* path */
		color,
		colorspace,
		NULL, /* alpha */
		NULL, /* ctm */
		NULL, /* stroke */
		NULL, /* private_data */
		0); /* private_data_len */
}