#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nItemHeight; scalar_t__ nMeasureItemHeight; int /*<<< orphan*/  hwndNotify; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_4__ {int itemID; scalar_t__ itemHeight; int /*<<< orphan*/  CtlID; scalar_t__ itemData; scalar_t__ itemWidth; int /*<<< orphan*/  CtlType; } ;
typedef  TYPE_1__ MEASUREITEMSTRUCT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ODT_LISTVIEW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MEASUREITEM ; 
 scalar_t__ max (scalar_t__,int) ; 

__attribute__((used)) static BOOL notify_measureitem(LISTVIEW_INFO *infoPtr)
{
    MEASUREITEMSTRUCT mis;
    mis.CtlType = ODT_LISTVIEW;
    mis.CtlID = GetWindowLongPtrW(infoPtr->hwndSelf, GWLP_ID);
    mis.itemID = -1;
    mis.itemWidth = 0;
    mis.itemData = 0;
    mis.itemHeight= infoPtr->nItemHeight;
    SendMessageW(infoPtr->hwndNotify, WM_MEASUREITEM, mis.CtlID, (LPARAM)&mis);
    if (infoPtr->nItemHeight != max(mis.itemHeight, 1))
    {
        infoPtr->nMeasureItemHeight = infoPtr->nItemHeight = max(mis.itemHeight, 1);
        return TRUE;
    }
    return FALSE;
}