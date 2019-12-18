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
struct TYPE_8__ {scalar_t__ Face; } ;
struct TYPE_7__ {struct TYPE_7__* Flink; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  TYPE_2__* PFONT_CACHE_ENTRY ;
typedef  scalar_t__ FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_FREETYPE_LOCK_HELD () ; 
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FONT_CACHE_ENTRY ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RemoveCachedEntry (TYPE_2__*) ; 
 TYPE_1__ g_FontCacheListHead ; 

__attribute__((used)) static void
RemoveCacheEntries(FT_Face Face)
{
    PLIST_ENTRY CurrentEntry, NextEntry;
    PFONT_CACHE_ENTRY FontEntry;

    ASSERT_FREETYPE_LOCK_HELD();

    for (CurrentEntry = g_FontCacheListHead.Flink;
         CurrentEntry != &g_FontCacheListHead;
         CurrentEntry = NextEntry)
    {
        FontEntry = CONTAINING_RECORD(CurrentEntry, FONT_CACHE_ENTRY, ListEntry);
        NextEntry = CurrentEntry->Flink;

        if (FontEntry->Face == Face)
        {
            RemoveCachedEntry(FontEntry);
        }
    }
}