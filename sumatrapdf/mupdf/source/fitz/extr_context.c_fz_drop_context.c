#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  user; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_14__ {scalar_t__ top; scalar_t__ stack; } ;
struct TYPE_16__ {TYPE_2__ alloc; TYPE_1__ error; } ;
typedef  TYPE_3__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fz_drop_colorspace_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_document_handler_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_font_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_glyph_cache_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_store_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_style_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_drop_tuning_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_flush_warnings (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

void
fz_drop_context(fz_context *ctx)
{
	if (!ctx)
		return;

	/* Other finalisation calls go here (in reverse order) */
	fz_drop_document_handler_context(ctx);
	fz_drop_glyph_cache_context(ctx);
	fz_drop_store_context(ctx);
	fz_drop_style_context(ctx);
	fz_drop_tuning_context(ctx);
	fz_drop_colorspace_context(ctx);
	fz_drop_font_context(ctx);

	fz_flush_warnings(ctx);

	assert(ctx->error.top == ctx->error.stack);

	/* Free the context itself */
	ctx->alloc.free(ctx->alloc.user, ctx);
}