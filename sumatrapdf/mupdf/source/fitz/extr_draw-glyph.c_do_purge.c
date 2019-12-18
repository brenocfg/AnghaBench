#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ total; scalar_t__* entry; } ;
typedef  TYPE_1__ fz_glyph_cache ;
struct TYPE_6__ {TYPE_1__* glyph_cache; } ;
typedef  TYPE_2__ fz_context ;

/* Variables and functions */
 int GLYPH_HASH_LEN ; 
 int /*<<< orphan*/  drop_glyph_cache_entry (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void
do_purge(fz_context *ctx)
{
	fz_glyph_cache *cache = ctx->glyph_cache;
	int i;

	for (i = 0; i < GLYPH_HASH_LEN; i++)
	{
		while (cache->entry[i])
			drop_glyph_cache_entry(ctx, cache->entry[i]);
	}

	cache->total = 0;
}