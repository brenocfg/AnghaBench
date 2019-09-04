#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_4__ {int /*<<< orphan*/ ** glyphs; } ;
struct TYPE_3__ {TYPE_2__** page; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  scalar_t__ SCRIPT_CACHE ;
typedef  int DWORD ;
typedef  TYPE_2__ CacheGlyphPage ;

/* Variables and functions */
 int GLYPH_BLOCK_MASK ; 
 int GLYPH_BLOCK_SHIFT ; 

__attribute__((used)) static inline WORD get_cache_glyph(SCRIPT_CACHE *psc, DWORD c)
{
    CacheGlyphPage *page = ((ScriptCache *)*psc)->page[c / 0x10000];
    WORD *block;

    if (!page) return 0;
    block = page->glyphs[(c % 0x10000) >> GLYPH_BLOCK_SHIFT];
    if (!block) return 0;
    return block[(c % 0x10000) & GLYPH_BLOCK_MASK];
}