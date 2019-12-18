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
typedef  int /*<<< orphan*/  fz_rasterizer ;
struct TYPE_4__ {scalar_t__ mask; scalar_t__ dest; scalar_t__ shape; scalar_t__ group_alpha; } ;
typedef  TYPE_1__ fz_draw_state ;
struct TYPE_5__ {int top; int /*<<< orphan*/  cache_y; int /*<<< orphan*/  cache_x; TYPE_1__* stack; TYPE_1__* init_stack; int /*<<< orphan*/  proof_cs; int /*<<< orphan*/  default_cs; int /*<<< orphan*/ * rast; } ;
typedef  TYPE_2__ fz_draw_device ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_default_colorspaces (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fz_drop_rasterizer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_drop_scale_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
fz_draw_drop_device(fz_context *ctx, fz_device *devp)
{
	fz_draw_device *dev = (fz_draw_device*)devp;
	fz_rasterizer *rast = dev->rast;

	fz_drop_default_colorspaces(ctx, dev->default_cs);
	fz_drop_colorspace(ctx, dev->proof_cs);

	/* pop and free the stacks */
	for (; dev->top > 0; dev->top--)
	{
		fz_draw_state *state = &dev->stack[dev->top - 1];
		if (state[1].mask != state[0].mask)
			fz_drop_pixmap(ctx, state[1].mask);
		if (state[1].dest != state[0].dest)
			fz_drop_pixmap(ctx, state[1].dest);
		if (state[1].shape != state[0].shape)
			fz_drop_pixmap(ctx, state[1].shape);
		if (state[1].group_alpha != state[0].group_alpha)
			fz_drop_pixmap(ctx, state[1].group_alpha);
	}

	/* We never free the dest/mask/shape at level 0, as:
	 * 1) dest is passed in and ownership remains with the caller.
	 * 2) shape and mask are NULL at level 0.
	 */

	if (dev->stack != &dev->init_stack[0])
		fz_free(ctx, dev->stack);
	fz_drop_scale_cache(ctx, dev->cache_x);
	fz_drop_scale_cache(ctx, dev->cache_y);
	fz_drop_rasterizer(ctx, rast);
}