#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svg_device ;
typedef  int /*<<< orphan*/  fz_rect ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * end_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * start_def (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  svg_dev_ctm (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_dev_path (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
svg_dev_clip_path(fz_context *ctx, fz_device *dev, const fz_path *path, int even_odd, fz_matrix ctm, fz_rect scissor)
{
	svg_device *sdev = (svg_device*)dev;
	fz_output *out;

	int num = sdev->id++;

	out = start_def(ctx, sdev);
	fz_write_printf(ctx, out, "<clipPath id=\"cp%d\">\n", num);
	fz_write_printf(ctx, out, "<path");
	svg_dev_ctm(ctx, sdev, ctm);
	svg_dev_path(ctx, sdev, path);
	if (even_odd)
		fz_write_printf(ctx, out, " fill-rule=\"evenodd\"");
	fz_write_printf(ctx, out, "/>\n</clipPath>\n");
	out = end_def(ctx, sdev);
	fz_write_printf(ctx, out, "<g clip-path=\"url(#cp%d)\">\n", num);
}