#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_15__ {scalar_t__ uView; int /*<<< orphan*/  hwndSelf; scalar_t__ nItemHeight; scalar_t__ nItemCount; TYPE_1__ rcList; } ;
struct TYPE_14__ {scalar_t__ top; scalar_t__ bottom; } ;
struct TYPE_13__ {int cbSize; int fMask; scalar_t__ nMax; scalar_t__ nPage; } ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LISTVIEW_GetViewRect (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  LISTVIEW_UpdateSize (TYPE_4__*) ; 
 scalar_t__ LV_VIEW_DETAILS ; 
 scalar_t__ LV_VIEW_LIST ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_PAGE ; 
 int SIF_RANGE ; 
 scalar_t__ SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  debugscrollinfo (TYPE_2__*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT LISTVIEW_UpdateVScroll(LISTVIEW_INFO *infoPtr)
{
    SCROLLINFO vertInfo;
    INT dy;

    ZeroMemory(&vertInfo, sizeof(SCROLLINFO));
    vertInfo.cbSize = sizeof(SCROLLINFO);
    vertInfo.nPage = infoPtr->rcList.bottom - infoPtr->rcList.top;

    if (infoPtr->uView == LV_VIEW_DETAILS)
    {
	vertInfo.nMax = infoPtr->nItemCount;
	
	/* scroll by at least one page */
	if(vertInfo.nPage < infoPtr->nItemHeight)
	  vertInfo.nPage = infoPtr->nItemHeight;

        if (infoPtr->nItemHeight > 0)
            vertInfo.nPage /= infoPtr->nItemHeight;
    }
    else if (infoPtr->uView != LV_VIEW_LIST) /* LV_VIEW_ICON, or LV_VIEW_SMALLICON */
    {
	RECT rcView;

	if (LISTVIEW_GetViewRect(infoPtr, &rcView)) vertInfo.nMax = rcView.bottom - rcView.top;
    }

    vertInfo.fMask = SIF_RANGE | SIF_PAGE;
    vertInfo.nMax = max(vertInfo.nMax - 1, 0);
    dy = GetScrollPos(infoPtr->hwndSelf, SB_VERT);
    dy -= SetScrollInfo(infoPtr->hwndSelf, SB_VERT, &vertInfo, TRUE);
    TRACE("vertInfo=%s\n", debugscrollinfo(&vertInfo));

    LISTVIEW_UpdateSize(infoPtr);
    return dy;
}