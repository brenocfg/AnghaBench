#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* colorspace; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_10__ {int /*<<< orphan*/  lab; int /*<<< orphan*/  cmyk; int /*<<< orphan*/  bgr; int /*<<< orphan*/  rgb; int /*<<< orphan*/  gray; int /*<<< orphan*/  ctx_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_colorspace (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_icc_context (TYPE_1__*) ; 
 scalar_t__ fz_drop_imp (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_free (TYPE_1__*,TYPE_3__*) ; 

void fz_drop_colorspace_context(fz_context *ctx)
{
	if (fz_drop_imp(ctx, ctx->colorspace, &ctx->colorspace->ctx_refs))
	{
		fz_drop_colorspace(ctx, ctx->colorspace->gray);
		fz_drop_colorspace(ctx, ctx->colorspace->rgb);
		fz_drop_colorspace(ctx, ctx->colorspace->bgr);
		fz_drop_colorspace(ctx, ctx->colorspace->cmyk);
		fz_drop_colorspace(ctx, ctx->colorspace->lab);
#if FZ_ENABLE_ICC
		fz_drop_icc_context(ctx);
#endif
		fz_free(ctx, ctx->colorspace);
		ctx->colorspace = NULL;
	}
}