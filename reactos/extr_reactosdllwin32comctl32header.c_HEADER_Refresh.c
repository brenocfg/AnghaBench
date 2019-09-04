#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_18__ {scalar_t__ uNumItem; int iHotItem; int dwStyle; int iHotDivider; scalar_t__ bDragging; TYPE_1__* items; scalar_t__ hFont; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  bRectsValid; } ;
struct TYPE_17__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_16__ {TYPE_2__ rect; } ;
typedef  TYPE_2__ RECT ;
typedef  int LRESULT ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/ * HTHEME ;
typedef  scalar_t__ HFONT ;
typedef  TYPE_3__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int BF_BOTTOM ; 
 int BF_LEFT ; 
 int BF_MIDDLE ; 
 int BF_SOFT ; 
 int BF_TOP ; 
 int /*<<< orphan*/  CDDS_POSTPAINT ; 
 int /*<<< orphan*/  CDDS_PREPAINT ; 
 int CDRF_NOTIFYPOSTPAINT ; 
 int /*<<< orphan*/  COLOR_3DFACE ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EDGE_ETCHED ; 
 int /*<<< orphan*/  EDGE_RAISED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetWindowTheme (int /*<<< orphan*/ ) ; 
 int HDS_BUTTONS ; 
 int HDS_FLAT ; 
 int /*<<< orphan*/  HEADER_DrawHotDivider (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_DrawItem (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 
 int HEADER_OrderToIndex (TYPE_3__*,scalar_t__) ; 
 int HEADER_SendCtrlCustomDraw (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  HEADER_SetItemBounds (TYPE_3__*) ; 
 int /*<<< orphan*/  HIS_NORMAL ; 
 int /*<<< orphan*/  HP_HEADERITEM ; 
 int /*<<< orphan*/  ImageList_DragShowNolock (int /*<<< orphan*/ ) ; 
 scalar_t__ RectVisible (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SYSTEM_FONT ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void
HEADER_Refresh (HEADER_INFO *infoPtr, HDC hdc)
{
    HFONT hFont, hOldFont;
    RECT rect, rcRest;
    HBRUSH hbrBk;
    UINT i;
    INT x;
    LRESULT lCDFlags;
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);

    if (!infoPtr->bRectsValid)
        HEADER_SetItemBounds(infoPtr);

    /* get rect for the bar, adjusted for the border */
    GetClientRect (infoPtr->hwndSelf, &rect);
    lCDFlags = HEADER_SendCtrlCustomDraw(infoPtr, CDDS_PREPAINT, hdc, &rect);
    
    if (infoPtr->bDragging)
	ImageList_DragShowNolock(FALSE);

    hFont = infoPtr->hFont ? infoPtr->hFont : GetStockObject (SYSTEM_FONT);
    hOldFont = SelectObject (hdc, hFont);

    /* draw Background */
    if (infoPtr->uNumItem == 0 && theme == NULL) {
        hbrBk = GetSysColorBrush(COLOR_3DFACE);
        FillRect(hdc, &rect, hbrBk);
    }

    x = rect.left;
    for (i = 0; x <= rect.right && i < infoPtr->uNumItem; i++) {
        int idx = HEADER_OrderToIndex(infoPtr,i);
        if (RectVisible(hdc, &infoPtr->items[idx].rect))
            HEADER_DrawItem(infoPtr, hdc, idx, infoPtr->iHotItem == idx, lCDFlags);
        x = infoPtr->items[idx].rect.right;
    }

    rcRest = rect;
    rcRest.left = x;
    if ((x <= rect.right) && RectVisible(hdc, &rcRest) && (infoPtr->uNumItem > 0)) {
        if (theme != NULL) {
            DrawThemeBackground(theme, hdc, HP_HEADERITEM, HIS_NORMAL, &rcRest, NULL);
        }
        else if (infoPtr->dwStyle & HDS_FLAT) {
            hbrBk = GetSysColorBrush(COLOR_3DFACE);
            FillRect(hdc, &rcRest, hbrBk);
        }
        else
        {
            if (infoPtr->dwStyle & HDS_BUTTONS)
                DrawEdge (hdc, &rcRest, EDGE_RAISED, BF_TOP|BF_LEFT|BF_BOTTOM|BF_SOFT|BF_MIDDLE);
            else
                DrawEdge (hdc, &rcRest, EDGE_ETCHED, BF_BOTTOM|BF_MIDDLE);
        }
    }

    if (infoPtr->iHotDivider != -1)
        HEADER_DrawHotDivider(infoPtr, hdc);

    if (infoPtr->bDragging)
	ImageList_DragShowNolock(TRUE);
    SelectObject (hdc, hOldFont);
    
    if (lCDFlags & CDRF_NOTIFYPOSTPAINT)
        HEADER_SendCtrlCustomDraw(infoPtr, CDDS_POSTPAINT, hdc, &rect);
}