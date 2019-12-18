#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ListEntry; scalar_t__ BitmapGlyph; } ;
typedef  TYPE_1__* PFONT_CACHE_ENTRY ;
typedef  int /*<<< orphan*/  FT_Glyph ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_FREETYPE_LOCK_HELD () ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Done_Glyph (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_FONT_CACHE ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAG_FONT ; 
 scalar_t__ g_FontCacheNumEntries ; 

__attribute__((used)) static void
RemoveCachedEntry(PFONT_CACHE_ENTRY Entry)
{
    ASSERT_FREETYPE_LOCK_HELD();

    FT_Done_Glyph((FT_Glyph)Entry->BitmapGlyph);
    RemoveEntryList(&Entry->ListEntry);
    ExFreePoolWithTag(Entry, TAG_FONT);
    g_FontCacheNumEntries--;
    ASSERT(g_FontCacheNumEntries <= MAX_FONT_CACHE);
}