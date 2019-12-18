#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  evicted; int /*<<< orphan*/  num_evictions; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ fz_glyph_cache ;
struct TYPE_7__ {TYPE_1__* glyph_cache; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_stderr (TYPE_2__*) ; 
 int /*<<< orphan*/  fz_write_printf (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
fz_dump_glyph_cache_stats(fz_context *ctx)
{
	fz_glyph_cache *cache = ctx->glyph_cache;
	fz_write_printf(ctx, fz_stderr(ctx), "Glyph Cache Size: %zu\n", cache->total);
#ifndef NDEBUG
	fz_write_printf(ctx, fz_stderr(ctx), "Glyph Cache Evictions: %d (%zu bytes)\n", cache->num_evictions, cache->evicted);
#endif
}