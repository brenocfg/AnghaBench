#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ left; scalar_t__ right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_28__ {int /*<<< orphan*/  hdr; TYPE_6__ rc; void* hdc; int /*<<< orphan*/  dwDrawStage; } ;
struct TYPE_33__ {TYPE_3__ nmcd; } ;
struct TYPE_32__ {TYPE_6__ rcPaint; } ;
struct TYPE_30__ {int fsState; TYPE_6__ rect; } ;
struct TYPE_27__ {int iButton; int dwFlags; } ;
struct TYPE_29__ {scalar_t__ himlInt; size_t cimlDef; size_t nNumButtons; int dwExStyle; int /*<<< orphan*/  clrInsertMark; TYPE_2__ tbim; TYPE_5__* buttons; int /*<<< orphan*/  hwndSelf; TYPE_1__** himlDef; scalar_t__ nNumBitmaps; int /*<<< orphan*/  bDoRedraw; } ;
struct TYPE_26__ {int /*<<< orphan*/  himl; } ;
typedef  TYPE_4__ TOOLBAR_INFO ;
typedef  TYPE_5__ TBUTTON_INFO ;
typedef  TYPE_6__ RECT ;
typedef  TYPE_7__ PAINTSTRUCT ;
typedef  TYPE_8__ NMTBCUSTOMDRAW ;
typedef  size_t INT ;
typedef  void* HDC ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDDS_POSTPAINT ; 
 int /*<<< orphan*/  CDDS_PREPAINT ; 
 int CDRF_NOTIFYPOSTPAINT ; 
 int /*<<< orphan*/  COMCTL32_DrawInsertMark (void*,TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int EqualRect (TYPE_6__*,TYPE_6__*) ; 
 int FALSE ; 
 scalar_t__ GETDEFIMAGELIST (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ INSERTMARK_WIDTH ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ ) ; 
 int IntersectRect (TYPE_6__*,TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 
 int /*<<< orphan*/  RectVisible (void*,TYPE_6__*) ; 
 int TBIMHT_AFTER ; 
 int TBSTATE_HIDDEN ; 
 int TBSTYLE_EX_HIDECLIPPEDBUTTONS ; 
 int /*<<< orphan*/  TOOLBAR_CheckImageListIconSize (TYPE_4__*) ; 
 int /*<<< orphan*/  TOOLBAR_DrawButton (TYPE_4__*,TYPE_5__*,void*,int) ; 
 int /*<<< orphan*/  TOOLBAR_DumpToolbar (TYPE_4__*,int) ; 
 int TOOLBAR_SendNotify (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_8__*,int) ; 

__attribute__((used)) static void
TOOLBAR_Refresh (TOOLBAR_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps)
{
    TBUTTON_INFO *btnPtr;
    INT i;
    RECT rcTemp, rcClient;
    NMTBCUSTOMDRAW tbcd;
    DWORD ntfret;
    DWORD dwBaseCustDraw;

    /* the app has told us not to redraw the toolbar */
    if (!infoPtr->bDoRedraw)
        return;

    /* if imagelist belongs to the app, it can be changed
       by the app after setting it */
    if (GETDEFIMAGELIST(infoPtr, 0) != infoPtr->himlInt)
    {
        infoPtr->nNumBitmaps = 0;
        for (i = 0; i < infoPtr->cimlDef; i++)
            infoPtr->nNumBitmaps += ImageList_GetImageCount(infoPtr->himlDef[i]->himl);
    }

    TOOLBAR_DumpToolbar (infoPtr, __LINE__);

    /* change the imagelist icon size if we manage the list and it is necessary */
    TOOLBAR_CheckImageListIconSize(infoPtr);

    /* Send initial notify */
    ZeroMemory (&tbcd, sizeof(NMTBCUSTOMDRAW));
    tbcd.nmcd.dwDrawStage = CDDS_PREPAINT;
    tbcd.nmcd.hdc = hdc;
    tbcd.nmcd.rc = ps->rcPaint;
    ntfret = TOOLBAR_SendNotify(&tbcd.nmcd.hdr, infoPtr, NM_CUSTOMDRAW);
    dwBaseCustDraw = ntfret & 0xffff;

    GetClientRect(infoPtr->hwndSelf, &rcClient);

    /* redraw necessary buttons */
    btnPtr = infoPtr->buttons;
    for (i = 0; i < infoPtr->nNumButtons; i++, btnPtr++)
    {
        BOOL bDraw;
        if (!RectVisible(hdc, &btnPtr->rect))
            continue;
        if (infoPtr->dwExStyle & TBSTYLE_EX_HIDECLIPPEDBUTTONS)
        {
            IntersectRect(&rcTemp, &rcClient, &btnPtr->rect);
            bDraw = EqualRect(&rcTemp, &btnPtr->rect);
        }
        else
            bDraw = TRUE;
        bDraw &= IntersectRect(&rcTemp, &(ps->rcPaint), &(btnPtr->rect));
        bDraw = (btnPtr->fsState & TBSTATE_HIDDEN) ? FALSE : bDraw;
        if (bDraw)
            TOOLBAR_DrawButton(infoPtr, btnPtr, hdc, dwBaseCustDraw);
    }

    /* draw insert mark if required */
    if (infoPtr->tbim.iButton != -1)
    {
        RECT rcButton = infoPtr->buttons[infoPtr->tbim.iButton].rect;
        RECT rcInsertMark;
        rcInsertMark.top = rcButton.top;
        rcInsertMark.bottom = rcButton.bottom;
        if (infoPtr->tbim.dwFlags & TBIMHT_AFTER)
            rcInsertMark.left = rcInsertMark.right = rcButton.right;
        else
            rcInsertMark.left = rcInsertMark.right = rcButton.left - INSERTMARK_WIDTH;
        COMCTL32_DrawInsertMark(hdc, &rcInsertMark, infoPtr->clrInsertMark, FALSE);
    }

    if (dwBaseCustDraw & CDRF_NOTIFYPOSTPAINT)
    {
	ZeroMemory (&tbcd, sizeof(NMTBCUSTOMDRAW));
	tbcd.nmcd.dwDrawStage = CDDS_POSTPAINT;
	tbcd.nmcd.hdc = hdc;
	tbcd.nmcd.rc = ps->rcPaint;
	TOOLBAR_SendNotify(&tbcd.nmcd.hdr, infoPtr, NM_CUSTOMDRAW);
    }
}