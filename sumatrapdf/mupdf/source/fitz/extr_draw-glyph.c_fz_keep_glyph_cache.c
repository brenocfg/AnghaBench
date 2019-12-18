#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ fz_glyph_cache ;
struct TYPE_8__ {TYPE_1__* glyph_cache; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_LOCK_GLYPHCACHE ; 
 int /*<<< orphan*/  fz_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 

fz_glyph_cache *
fz_keep_glyph_cache(fz_context *ctx)
{
	fz_lock(ctx, FZ_LOCK_GLYPHCACHE);
	ctx->glyph_cache->refs++;
	fz_unlock(ctx, FZ_LOCK_GLYPHCACHE);
	return ctx->glyph_cache;
}