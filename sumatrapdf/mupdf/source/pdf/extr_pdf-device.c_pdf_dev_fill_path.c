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
typedef  int /*<<< orphan*/  pdf_device ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ gstate ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;

/* Variables and functions */
 TYPE_1__* CURRENT_GSTATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_dev_alpha (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_ctm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dev_end_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dev_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
pdf_dev_fill_path(fz_context *ctx, fz_device *dev, const fz_path *path, int even_odd, fz_matrix ctm,
	fz_colorspace *colorspace, const float *color, float alpha, fz_color_params color_params)
{
	pdf_device *pdev = (pdf_device*)dev;
	gstate *gs = CURRENT_GSTATE(pdev);

	pdf_dev_end_text(ctx, pdev);
	pdf_dev_alpha(ctx, pdev, alpha, 0);
	pdf_dev_color(ctx, pdev, colorspace, color, 0, color_params);
	pdf_dev_ctm(ctx, pdev, ctm);
	pdf_dev_path(ctx, pdev, path);
	fz_append_string(ctx, gs->buf, (even_odd ? "f*\n" : "f\n"));
}