#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  font; } ;
struct TYPE_21__ {size_t hash; int /*<<< orphan*/  val; TYPE_5__ key; TYPE_4__* bucket_next; TYPE_3__* bucket_prev; TYPE_2__* lru_next; TYPE_1__* lru_prev; } ;
typedef  TYPE_6__ fz_glyph_cache_entry ;
struct TYPE_22__ {TYPE_4__** entry; int /*<<< orphan*/  total; TYPE_2__* lru_head; TYPE_1__* lru_tail; } ;
typedef  TYPE_7__ fz_glyph_cache ;
struct TYPE_23__ {TYPE_7__* glyph_cache; } ;
typedef  TYPE_8__ fz_context ;
struct TYPE_19__ {TYPE_3__* bucket_prev; } ;
struct TYPE_18__ {TYPE_4__* bucket_next; } ;
struct TYPE_17__ {TYPE_1__* lru_prev; } ;
struct TYPE_16__ {TYPE_2__* lru_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_font (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_glyph (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (TYPE_8__*,TYPE_6__*) ; 
 scalar_t__ fz_glyph_size (TYPE_8__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
drop_glyph_cache_entry(fz_context *ctx, fz_glyph_cache_entry *entry)
{
	fz_glyph_cache *cache = ctx->glyph_cache;

	if (entry->lru_next)
		entry->lru_next->lru_prev = entry->lru_prev;
	else
		cache->lru_tail = entry->lru_prev;
	if (entry->lru_prev)
		entry->lru_prev->lru_next = entry->lru_next;
	else
		cache->lru_head = entry->lru_next;
	cache->total -= fz_glyph_size(ctx, entry->val);
	if (entry->bucket_next)
		entry->bucket_next->bucket_prev = entry->bucket_prev;
	if (entry->bucket_prev)
		entry->bucket_prev->bucket_next = entry->bucket_next;
	else
		cache->entry[entry->hash] = entry->bucket_next;
	fz_drop_font(ctx, entry->key.font);
	fz_drop_glyph(ctx, entry->val);
	fz_free(ctx, entry);
}