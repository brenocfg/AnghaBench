#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_22__ {int left; } ;
struct TYPE_21__ {size_t iMoveItem; int iHotDivider; int uNumItem; int dwStyle; int xTrackOffset; void* bCaptured; int /*<<< orphan*/  hwndSelf; TYPE_2__* items; int /*<<< orphan*/  xOldTrack; void* bTracking; void* bPressed; void* bDragging; void* bRectsValid; } ;
struct TYPE_20__ {int iOrder; int cxy; TYPE_4__ rect; void* bDown; } ;
struct TYPE_19__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  TYPE_2__ HEADER_ITEM ;
typedef  TYPE_3__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDI_ORDER ; 
 int /*<<< orphan*/  HDI_WIDTH ; 
 int /*<<< orphan*/  HDN_ENDDRAG ; 
 int /*<<< orphan*/  HDN_ENDTRACKW ; 
 int /*<<< orphan*/  HDN_ITEMCHANGEDW ; 
 int /*<<< orphan*/  HDN_ITEMCHANGINGW ; 
 int /*<<< orphan*/  HDN_ITEMCLICKW ; 
 int HDS_DRAGDROP ; 
 int HDS_FULLDRAG ; 
 int /*<<< orphan*/  HEADER_ChangeItemOrder (TYPE_3__*,size_t,int) ; 
 int /*<<< orphan*/  HEADER_DrawTrackLine (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HEADER_IndexToOrder (TYPE_3__*,int) ; 
 int /*<<< orphan*/  HEADER_InternalHitTest (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  HEADER_IsDragDistance (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  HEADER_RefreshItem (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithHDItemT (TYPE_3__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithIntFieldT (TYPE_3__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HEADER_SendSimpleNotify (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_SetHotDivider (TYPE_3__*,void*,int) ; 
 int /*<<< orphan*/  HEADER_SetItemBounds (TYPE_3__*) ; 
 int /*<<< orphan*/  ImageList_DragShowNolock (void*) ; 
 int /*<<< orphan*/  ImageList_EndDrag () ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,TYPE_4__*,void*) ; 
 int /*<<< orphan*/  NM_RELEASEDCAPTURE ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t) ; 
 void* TRUE ; 

__attribute__((used)) static LRESULT
HEADER_LButtonUp (HEADER_INFO *infoPtr, INT x, INT y)
{
    POINT pt;
    UINT  flags;
    INT   nItem;
    HDC   hdc;

    pt.x = x;
    pt.y = y;
    HEADER_InternalHitTest (infoPtr, &pt, &flags, &nItem);

    if (infoPtr->bPressed) {

	infoPtr->items[infoPtr->iMoveItem].bDown = FALSE;

	if (infoPtr->bDragging)
	{
            HEADER_ITEM *lpItem = &infoPtr->items[infoPtr->iMoveItem];
            INT iNewOrder;
            
	    ImageList_DragShowNolock(FALSE);
	    ImageList_EndDrag();

            if (infoPtr->iHotDivider == -1)
                iNewOrder = -1;
            else if (infoPtr->iHotDivider == infoPtr->uNumItem)
                iNewOrder = infoPtr->uNumItem-1;
            else
	    {
                iNewOrder = HEADER_IndexToOrder(infoPtr, infoPtr->iHotDivider);
                if (iNewOrder > lpItem->iOrder)
                    iNewOrder--;
            }

            if (iNewOrder != -1 &&
                !HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ENDDRAG, infoPtr->iMoveItem, HDI_ORDER, iNewOrder))
            {
                HEADER_ChangeItemOrder(infoPtr, infoPtr->iMoveItem, iNewOrder);
		infoPtr->bRectsValid = FALSE;
		InvalidateRect(infoPtr->hwndSelf, NULL, FALSE);
	    }
	    else
		InvalidateRect(infoPtr->hwndSelf, &infoPtr->items[infoPtr->iMoveItem].rect, FALSE);

            infoPtr->bDragging = FALSE;
            HEADER_SetHotDivider(infoPtr, FALSE, -1);
	}
	else
	{
	    hdc = GetDC (infoPtr->hwndSelf);
	    HEADER_RefreshItem (infoPtr, infoPtr->iMoveItem);
	    ReleaseDC (infoPtr->hwndSelf, hdc);

	    if (!(infoPtr->dwStyle & HDS_DRAGDROP) || !HEADER_IsDragDistance(infoPtr, &pt))
		HEADER_SendNotifyWithHDItemT(infoPtr, HDN_ITEMCLICKW, infoPtr->iMoveItem, NULL);
	}

	TRACE("Released item %d.\n", infoPtr->iMoveItem);
	infoPtr->bPressed = FALSE;
    }
    else if (infoPtr->bTracking) {
        INT iNewWidth = pt.x - infoPtr->items[infoPtr->iMoveItem].rect.left + infoPtr->xTrackOffset;
        if (iNewWidth < 0)
	    iNewWidth = 0;
	TRACE("End tracking item %d.\n", infoPtr->iMoveItem);
	infoPtr->bTracking = FALSE;

        HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ENDTRACKW, infoPtr->iMoveItem, HDI_WIDTH, iNewWidth);

        if (!(infoPtr->dwStyle & HDS_FULLDRAG)) {
	    hdc = GetDC (infoPtr->hwndSelf);
	    HEADER_DrawTrackLine (infoPtr, hdc, infoPtr->xOldTrack);
            ReleaseDC (infoPtr->hwndSelf, hdc);
        }
          
        if (!HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ITEMCHANGINGW, infoPtr->iMoveItem, HDI_WIDTH, iNewWidth))
        {
            infoPtr->items[infoPtr->iMoveItem].cxy = iNewWidth;
            HEADER_SendNotifyWithIntFieldT(infoPtr, HDN_ITEMCHANGEDW, infoPtr->iMoveItem, HDI_WIDTH, iNewWidth);
        }

	HEADER_SetItemBounds (infoPtr);
	InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);
    }

    if (infoPtr->bCaptured) {
	infoPtr->bCaptured = FALSE;
	ReleaseCapture ();
	HEADER_SendSimpleNotify (infoPtr, NM_RELEASEDCAPTURE);
    }

    return 0;
}