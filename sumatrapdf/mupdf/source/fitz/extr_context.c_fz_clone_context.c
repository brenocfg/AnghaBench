#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  user; TYPE_3__* (* malloc ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_19__ {scalar_t__ lock; scalar_t__ unlock; } ;
struct TYPE_20__ {TYPE_1__ alloc; TYPE_2__ locks; } ;
typedef  TYPE_3__ fz_context ;
struct TYPE_21__ {scalar_t__ lock; scalar_t__ unlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_init_error_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_colorspace_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_document_handler_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_font_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_glyph_cache (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_store_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_style_context (TYPE_3__*) ; 
 int /*<<< orphan*/  fz_keep_tuning_context (TYPE_3__*) ; 
 TYPE_7__ fz_locks_default ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 TYPE_3__* stub1 (int /*<<< orphan*/ ,int) ; 

fz_context *
fz_clone_context(fz_context *ctx)
{
	fz_context *new_ctx;

	/* We cannot safely clone the context without having locking/
	 * unlocking functions. */
	if (ctx == NULL || (ctx->locks.lock == fz_locks_default.lock && ctx->locks.unlock == fz_locks_default.unlock))
		return NULL;

	new_ctx = ctx->alloc.malloc(ctx->alloc.user, sizeof(fz_context));
	if (!new_ctx)
		return NULL;

	/* First copy old context, including pointers to shared contexts */
	memcpy(new_ctx, ctx, sizeof (fz_context));

	/* Reset error context to initial state. */
	fz_init_error_context(new_ctx);

	/* Then keep lock checking happy by keeping shared contexts with new context */
	fz_keep_document_handler_context(new_ctx);
	fz_keep_style_context(new_ctx);
	fz_keep_tuning_context(new_ctx);
	fz_keep_font_context(new_ctx);
	fz_keep_colorspace_context(new_ctx);
	fz_keep_store_context(new_ctx);
	fz_keep_glyph_cache(new_ctx);

	return new_ctx;
}