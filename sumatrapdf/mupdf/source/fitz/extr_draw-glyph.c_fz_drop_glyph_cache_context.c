#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* glyph_cache; } ;
typedef  TYPE_1__ fz_context ;
struct TYPE_9__ {scalar_t__ refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_GLYPHCACHE ; 
 int /*<<< orphan*/  do_purge (TYPE_1__*) ; 
 int /*<<< orphan*/  fz_free (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
fz_drop_glyph_cache_context(fz_context *ctx)
{
	if (!ctx || !ctx->glyph_cache)
		return;

	fz_lock(ctx, FZ_LOCK_GLYPHCACHE);
	ctx->glyph_cache->refs--;
	if (ctx->glyph_cache->refs == 0)
	{
		do_purge(ctx);
		fz_free(ctx, ctx->glyph_cache);
		ctx->glyph_cache = NULL;
	}
	fz_unlock(ctx, FZ_LOCK_GLYPHCACHE);
}