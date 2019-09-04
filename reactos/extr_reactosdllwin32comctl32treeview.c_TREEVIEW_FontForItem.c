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
struct TYPE_6__ {int dwStyle; int /*<<< orphan*/  hFont; int /*<<< orphan*/  hBoldFont; int /*<<< orphan*/  hUnderlineFont; int /*<<< orphan*/  hBoldUnderlineFont; TYPE_1__ const* hotItem; } ;
struct TYPE_5__ {int state; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  TYPE_2__ TREEVIEW_INFO ;
typedef  int /*<<< orphan*/  HFONT ;

/* Variables and functions */
 int TVIS_BOLD ; 
 int TVS_TRACKSELECT ; 

__attribute__((used)) static inline HFONT
TREEVIEW_FontForItem(const TREEVIEW_INFO *infoPtr, const TREEVIEW_ITEM *item)
{
    if ((infoPtr->dwStyle & TVS_TRACKSELECT) && (item == infoPtr->hotItem))
        return item->state & TVIS_BOLD ? infoPtr->hBoldUnderlineFont : infoPtr->hUnderlineFont;
    if (item->state & TVIS_BOLD)
        return infoPtr->hBoldFont;
    return infoPtr->hFont;
}