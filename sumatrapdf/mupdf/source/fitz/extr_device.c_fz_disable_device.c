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
struct TYPE_3__ {int /*<<< orphan*/ * end_layer; int /*<<< orphan*/ * begin_layer; int /*<<< orphan*/ * set_default_colorspaces; int /*<<< orphan*/ * render_flags; int /*<<< orphan*/ * end_tile; int /*<<< orphan*/ * begin_tile; int /*<<< orphan*/ * end_group; int /*<<< orphan*/ * begin_group; int /*<<< orphan*/ * end_mask; int /*<<< orphan*/ * begin_mask; int /*<<< orphan*/ * pop_clip; int /*<<< orphan*/ * clip_image_mask; int /*<<< orphan*/ * fill_image_mask; int /*<<< orphan*/ * fill_image; int /*<<< orphan*/ * fill_shade; int /*<<< orphan*/ * ignore_text; int /*<<< orphan*/ * clip_stroke_text; int /*<<< orphan*/ * clip_text; int /*<<< orphan*/ * stroke_text; int /*<<< orphan*/ * fill_text; int /*<<< orphan*/ * clip_stroke_path; int /*<<< orphan*/ * clip_path; int /*<<< orphan*/ * stroke_path; int /*<<< orphan*/ * fill_path; int /*<<< orphan*/ * close_device; } ;
typedef  TYPE_1__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void
fz_disable_device(fz_context *ctx, fz_device *dev)
{
	dev->close_device = NULL;
	dev->fill_path = NULL;
	dev->stroke_path = NULL;
	dev->clip_path = NULL;
	dev->clip_stroke_path = NULL;
	dev->fill_text = NULL;
	dev->stroke_text = NULL;
	dev->clip_text = NULL;
	dev->clip_stroke_text = NULL;
	dev->ignore_text = NULL;
	dev->fill_shade = NULL;
	dev->fill_image = NULL;
	dev->fill_image_mask = NULL;
	dev->clip_image_mask = NULL;
	dev->pop_clip = NULL;
	dev->begin_mask = NULL;
	dev->end_mask = NULL;
	dev->begin_group = NULL;
	dev->end_group = NULL;
	dev->begin_tile = NULL;
	dev->end_tile = NULL;
	dev->render_flags = NULL;
	dev->set_default_colorspaces = NULL;
	dev->begin_layer = NULL;
	dev->end_layer = NULL;
}