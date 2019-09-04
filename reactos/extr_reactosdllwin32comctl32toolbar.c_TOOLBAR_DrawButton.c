#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
struct TYPE_48__ {int /*<<< orphan*/  clrBtnText; int /*<<< orphan*/  clr3dShadow; int /*<<< orphan*/  clrBtnHighlight; int /*<<< orphan*/  clrHighlight; int /*<<< orphan*/  clrBtnFace; int /*<<< orphan*/  clrHighlightText; } ;
struct TYPE_46__ {int left; int right; int top; int bottom; } ;
struct TYPE_43__ {int uItemState; int /*<<< orphan*/  hdr; int /*<<< orphan*/  dwDrawStage; TYPE_6__ rc; void* hdc; int /*<<< orphan*/  lItemlParam; int /*<<< orphan*/  dwItemSpec; } ;
struct TYPE_42__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_47__ {int nStringBkMode; TYPE_3__ nmcd; scalar_t__ clrHighlightHotTrack; TYPE_2__ rcText; scalar_t__ hpenLines; scalar_t__ hbrLines; int /*<<< orphan*/  hbrMonoDither; int /*<<< orphan*/  nHLStringBkMode; int /*<<< orphan*/  clrMark; int /*<<< orphan*/  clrBtnHighlight; int /*<<< orphan*/  clrBtnFace; int /*<<< orphan*/  clrTextHighlight; int /*<<< orphan*/  clrText; } ;
struct TYPE_45__ {int fsStyle; int fsState; scalar_t__ bDropDownPressed; TYPE_6__ rect; int /*<<< orphan*/  dwData; int /*<<< orphan*/  idCommand; int /*<<< orphan*/  iBitmap; } ;
struct TYPE_41__ {int cx; int cy; } ;
struct TYPE_44__ {int dwStyle; scalar_t__ nMaxTextRows; int dwExStyle; int iListGap; int nBitmapWidth; int /*<<< orphan*/  hwndSelf; TYPE_1__ szPadding; int /*<<< orphan*/  nBitmapHeight; } ;
typedef  TYPE_4__ TOOLBAR_INFO ;
typedef  TYPE_5__ TBUTTON_INFO ;
typedef  TYPE_6__ RECT ;
typedef  TYPE_7__ NMTBCUSTOMDRAW ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int INT ;
typedef  scalar_t__ HTHEME ;
typedef  void* HDC ;
typedef  int DWORD ;
typedef  scalar_t__ COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 int ARROW_HEIGHT ; 
 int BTNS_SEP ; 
 int BTNS_SHOWTEXT ; 
 int BTNS_WHOLEDROPDOWN ; 
 int CCS_VERT ; 
 int /*<<< orphan*/  CDDS_ITEMPOSTPAINT ; 
 int /*<<< orphan*/  CDDS_ITEMPREPAINT ; 
 int CDIS_CHECKED ; 
 int CDIS_DISABLED ; 
 int CDIS_HOT ; 
 int CDIS_INDETERMINATE ; 
 int CDIS_SELECTED ; 
 int CDRF_NOTIFYITEMDRAW ; 
 int CDRF_NOTIFYPOSTPAINT ; 
 int CDRF_SKIPDEFAULT ; 
 int /*<<< orphan*/  COMCTL32_hPattern55AABrush ; 
 scalar_t__ DDARROW_WIDTH ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,void*,int,int,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETO_OPAQUE ; 
 int /*<<< orphan*/  ExtTextOutW (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GETDEFIMAGELIST (TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 scalar_t__ ImageList_GetImageCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  NM_CUSTOMDRAW ; 
 int /*<<< orphan*/  OPAQUE ; 
 int /*<<< orphan*/  OffsetRect (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 scalar_t__ SetBkColor (void*,scalar_t__) ; 
 int SetBkMode (void*,int) ; 
 int TBCDRF_HILITEHOTTRACK ; 
 int TBCDRF_NOOFFSET ; 
 int TBSTATE_CHECKED ; 
 int TBSTATE_PRESSED ; 
 int TBSTYLE_EX_MIXEDBUTTONS ; 
 int TBSTYLE_FLAT ; 
 int TBSTYLE_LIST ; 
 int /*<<< orphan*/  TOOLBAR_DrawArrow (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLBAR_DrawFlatHorizontalSeparator (TYPE_6__*,void*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  TOOLBAR_DrawFlatSeparator (TYPE_6__*,void*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  TOOLBAR_DrawFrame (TYPE_4__ const*,TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  TOOLBAR_DrawImage (TYPE_4__ const*,TYPE_5__*,int,int,TYPE_7__*,int) ; 
 int /*<<< orphan*/  TOOLBAR_DrawPattern (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  TOOLBAR_DrawSepDDArrow (TYPE_4__ const*,TYPE_7__*,TYPE_6__*,scalar_t__,int) ; 
 int /*<<< orphan*/  TOOLBAR_DrawString (TYPE_4__ const*,TYPE_6__*,int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/ * TOOLBAR_GetText (TYPE_4__ const*,TYPE_5__*) ; 
 int TOOLBAR_SendNotify (int /*<<< orphan*/ *,TYPE_4__ const*,int /*<<< orphan*/ ) ; 
 int TOOLBAR_TranslateState (TYPE_5__*) ; 
 int TP_BUTTON ; 
 int TP_DROPDOWNBUTTON ; 
 int TP_SEPARATOR ; 
 int TP_SEPARATORVERT ; 
 int TP_SPLITBUTTON ; 
 int TP_SPLITBUTTONDROPDOWN ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int TRANSPARENT ; 
 int TS_DISABLED ; 
 int TS_HOT ; 
 int TS_HOTCHECKED ; 
 int TS_NORMAL ; 
 int TS_PRESSED ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_7__*,int) ; 
 int button_has_ddarrow (TYPE_4__ const*,TYPE_5__*) ; 
 TYPE_8__ comctl32_color ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int max (int,scalar_t__) ; 

__attribute__((used)) static void
TOOLBAR_DrawButton (const TOOLBAR_INFO *infoPtr, TBUTTON_INFO *btnPtr, HDC hdc, DWORD dwBaseCustDraw)
{
    DWORD dwStyle = infoPtr->dwStyle;
    BOOL hasDropDownArrow = button_has_ddarrow( infoPtr, btnPtr );
    BOOL drawSepDropDownArrow = hasDropDownArrow && 
                                (~btnPtr->fsStyle & BTNS_WHOLEDROPDOWN);
    RECT rc, rcArrow, rcBitmap, rcText;
    LPWSTR lpText = NULL;
    NMTBCUSTOMDRAW tbcd;
    DWORD ntfret;
    INT offset;
    INT oldBkMode;
    DWORD dwItemCustDraw;
    DWORD dwItemCDFlag;
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);

    rc = btnPtr->rect;
    rcArrow = rc;

    /* separator - doesn't send NM_CUSTOMDRAW */
    if (btnPtr->fsStyle & BTNS_SEP) {
        if (theme)
        {
            DrawThemeBackground (theme, hdc, 
                (dwStyle & CCS_VERT) ? TP_SEPARATORVERT : TP_SEPARATOR, 0, 
                &rc, NULL);
        }
        else
        /* with the FLAT style, iBitmap is the width and has already */
        /* been taken into consideration in calculating the width    */
        /* so now we need to draw the vertical separator             */
        /* empirical tests show that iBitmap can/will be non-zero    */
        /* when drawing the vertical bar...      */
        if ((dwStyle & TBSTYLE_FLAT) /* && (btnPtr->iBitmap == 0) */) {
            if (dwStyle & CCS_VERT) {
                RECT rcsep = rc;
                InflateRect(&rcsep, -infoPtr->szPadding.cx, -infoPtr->szPadding.cy);
                TOOLBAR_DrawFlatHorizontalSeparator (&rcsep, hdc, infoPtr);
            }
            else {
                TOOLBAR_DrawFlatSeparator (&rc, hdc, infoPtr);
            }
        }
        else if (btnPtr->fsStyle != BTNS_SEP) {
            FIXME("Draw some kind of separator: fsStyle=%x\n",
              btnPtr->fsStyle);
        }
        return;
    }

    /* get a pointer to the text */
    lpText = TOOLBAR_GetText(infoPtr, btnPtr);

    if (hasDropDownArrow)
    {
        int right;

        if (dwStyle & TBSTYLE_FLAT)
            right = max(rc.left, rc.right - DDARROW_WIDTH);
        else
            right = max(rc.left, rc.right - DDARROW_WIDTH - 2);

        if (drawSepDropDownArrow)
           rc.right = right;

        rcArrow.left = right;
    }

    /* copy text & bitmap rects after adjusting for drop-down arrow
     * so that text & bitmap is centered in the rectangle not containing
     * the arrow */
    rcText = rc;
    rcBitmap = rc;

    /* Center the bitmap horizontally and vertically */
    if (dwStyle & TBSTYLE_LIST)
    {
        if (lpText &&
            infoPtr->nMaxTextRows > 0 &&
            (!(infoPtr->dwExStyle & TBSTYLE_EX_MIXEDBUTTONS) ||
            (btnPtr->fsStyle & BTNS_SHOWTEXT)) )
            rcBitmap.left += GetSystemMetrics(SM_CXEDGE) + infoPtr->szPadding.cx / 2;
        else
            rcBitmap.left += GetSystemMetrics(SM_CXEDGE) + infoPtr->iListGap / 2;
    }
    else
        rcBitmap.left += ((rc.right - rc.left) - infoPtr->nBitmapWidth) / 2;

    rcBitmap.top += infoPtr->szPadding.cy / 2;
#ifdef __REACTOS__
    rcBitmap.top += infoPtr->themeMargins.cyTopHeight;
#endif

    TRACE("iBitmap=%d, start=(%d,%d) w=%d, h=%d\n",
      btnPtr->iBitmap, rcBitmap.left, rcBitmap.top,
      infoPtr->nBitmapWidth, infoPtr->nBitmapHeight);
    TRACE("Text=%s\n", debugstr_w(lpText));
    TRACE("iListGap=%d, padding = { %d, %d }\n", infoPtr->iListGap, infoPtr->szPadding.cx, infoPtr->szPadding.cy);

    /* calculate text position */
    if (lpText)
    {
        InflateRect(&rcText, -GetSystemMetrics(SM_CXEDGE), 0);
        if (dwStyle & TBSTYLE_LIST)
        {
            rcText.left += infoPtr->nBitmapWidth + infoPtr->iListGap + 2;
        }
        else
        {
            if (ImageList_GetImageCount(GETDEFIMAGELIST(infoPtr, 0)) > 0)
                rcText.top += infoPtr->szPadding.cy/2 + infoPtr->nBitmapHeight + 1;
            else
                rcText.top += infoPtr->szPadding.cy/2 + 2;
        }
    }

    /* Initialize fields in all cases, because we use these later
     * NOTE: applications can and do alter these to customize their
     * toolbars */
    ZeroMemory (&tbcd, sizeof(NMTBCUSTOMDRAW));
    tbcd.clrText = comctl32_color.clrBtnText;
    tbcd.clrTextHighlight = comctl32_color.clrHighlightText;
    tbcd.clrBtnFace = comctl32_color.clrBtnFace;
    tbcd.clrBtnHighlight = comctl32_color.clrBtnHighlight;
    tbcd.clrMark = comctl32_color.clrHighlight;
    tbcd.clrHighlightHotTrack = 0;
    tbcd.nStringBkMode = TRANSPARENT;
    tbcd.nHLStringBkMode = OPAQUE;
    tbcd.rcText.left = 0;
    tbcd.rcText.top = 0;
    tbcd.rcText.right = rcText.right - rc.left;
    tbcd.rcText.bottom = rcText.bottom - rc.top;
    tbcd.nmcd.uItemState = TOOLBAR_TranslateState(btnPtr);
    tbcd.nmcd.hdc = hdc;
    tbcd.nmcd.rc = btnPtr->rect;
    tbcd.hbrMonoDither = COMCTL32_hPattern55AABrush;

    /* FIXME: what are these used for? */
    tbcd.hbrLines = 0;
    tbcd.hpenLines = 0;

    /* Issue Item Prepaint notify */
    dwItemCustDraw = 0;
    dwItemCDFlag = 0;
    if (dwBaseCustDraw & CDRF_NOTIFYITEMDRAW)
    {
	tbcd.nmcd.dwDrawStage = CDDS_ITEMPREPAINT;
	tbcd.nmcd.dwItemSpec = btnPtr->idCommand;
	tbcd.nmcd.lItemlParam = btnPtr->dwData;
	ntfret = TOOLBAR_SendNotify(&tbcd.nmcd.hdr, infoPtr, NM_CUSTOMDRAW);
        /* reset these fields so the user can't alter the behaviour like native */
        tbcd.nmcd.hdc = hdc;
        tbcd.nmcd.rc = btnPtr->rect;

	dwItemCustDraw = ntfret & 0xffff;
	dwItemCDFlag = ntfret & 0xffff0000;
	if (dwItemCustDraw & CDRF_SKIPDEFAULT)
	    return;
	/* save the only part of the rect that the user can change */
	rcText.right = tbcd.rcText.right + rc.left;
	rcText.bottom = tbcd.rcText.bottom + rc.top;
    }

    if (!(dwItemCDFlag & TBCDRF_NOOFFSET) &&
        (btnPtr->fsState & (TBSTATE_PRESSED | TBSTATE_CHECKED)))
        OffsetRect(&rcText, 1, 1);

    if (!(tbcd.nmcd.uItemState & CDIS_HOT) && 
        ((tbcd.nmcd.uItemState & CDIS_CHECKED) || (tbcd.nmcd.uItemState & CDIS_INDETERMINATE)))
        TOOLBAR_DrawPattern (&rc, &tbcd);

    if (((infoPtr->dwStyle & TBSTYLE_FLAT) || GetWindowTheme (infoPtr->hwndSelf)) 
        && (tbcd.nmcd.uItemState & CDIS_HOT))
    {
        if ( dwItemCDFlag & TBCDRF_HILITEHOTTRACK )
        {
            COLORREF oldclr;

            oldclr = SetBkColor(hdc, tbcd.clrHighlightHotTrack);
            ExtTextOutW(hdc, 0, 0, ETO_OPAQUE, &rc, NULL, 0, 0);
            if (hasDropDownArrow)
                ExtTextOutW(hdc, 0, 0, ETO_OPAQUE, &rcArrow, NULL, 0, 0);
            SetBkColor(hdc, oldclr);
        }
    }

#ifdef __REACTOS__
    if (theme && !(dwItemCDFlag & TBCDRF_NOBACKGROUND))
#else
    if (theme)
#endif
    {
        int partId = drawSepDropDownArrow ? TP_SPLITBUTTON : TP_BUTTON;
        int stateId = TS_NORMAL;
        
        if (tbcd.nmcd.uItemState & CDIS_DISABLED)
            stateId = TS_DISABLED;
        else if (tbcd.nmcd.uItemState & CDIS_SELECTED)
            stateId = TS_PRESSED;
        else if (tbcd.nmcd.uItemState & CDIS_CHECKED)
#ifdef __REACTOS__
            stateId = (tbcd.nmcd.uItemState & CDIS_HOT) ? TS_HOTCHECKED : TS_CHECKED;
#else
            stateId = (tbcd.nmcd.uItemState & CDIS_HOT) ? TS_HOTCHECKED : TS_HOT;
#endif
        else if ((tbcd.nmcd.uItemState & CDIS_HOT)
            || (drawSepDropDownArrow && btnPtr->bDropDownPressed))
            stateId = TS_HOT;
            
        DrawThemeBackground (theme, hdc, partId, stateId, &rc, NULL);
    }

#ifdef __REACTOS__
    if (!theme)
#else
    else
#endif
        TOOLBAR_DrawFrame(infoPtr, &tbcd, &rc, dwItemCDFlag);

    if (drawSepDropDownArrow)
    {
        if (theme)
        {
            int stateId = TS_NORMAL;
            
            if (tbcd.nmcd.uItemState & CDIS_DISABLED)
                stateId = TS_DISABLED;
            else if (btnPtr->bDropDownPressed || (tbcd.nmcd.uItemState & CDIS_SELECTED))
                stateId = TS_PRESSED;
            else if (tbcd.nmcd.uItemState & CDIS_CHECKED)
#ifdef __REACTOS__
                stateId = (tbcd.nmcd.uItemState & CDIS_HOT) ? TS_HOTCHECKED : TS_CHECKED;
#else
                stateId = (tbcd.nmcd.uItemState & CDIS_HOT) ? TS_HOTCHECKED : TS_HOT;
#endif
            else if (tbcd.nmcd.uItemState & CDIS_HOT)
                stateId = TS_HOT;
                
            DrawThemeBackground (theme, hdc, TP_DROPDOWNBUTTON, stateId, &rcArrow, NULL);
            DrawThemeBackground (theme, hdc, TP_SPLITBUTTONDROPDOWN, stateId, &rcArrow, NULL);
        }
        else
            TOOLBAR_DrawSepDDArrow(infoPtr, &tbcd, &rcArrow, btnPtr->bDropDownPressed, dwItemCDFlag);
    }

    oldBkMode = SetBkMode (hdc, tbcd.nStringBkMode);
    if (!(infoPtr->dwExStyle & TBSTYLE_EX_MIXEDBUTTONS) || (btnPtr->fsStyle & BTNS_SHOWTEXT))
        TOOLBAR_DrawString (infoPtr, &rcText, lpText, &tbcd, dwItemCDFlag);
    SetBkMode (hdc, oldBkMode);

    TOOLBAR_DrawImage(infoPtr, btnPtr, rcBitmap.left, rcBitmap.top, &tbcd, dwItemCDFlag);

    if (hasDropDownArrow && !drawSepDropDownArrow)
    {
        if (tbcd.nmcd.uItemState & (CDIS_DISABLED | CDIS_INDETERMINATE))
        {
            TOOLBAR_DrawArrow(hdc, rcArrow.left+1, rcArrow.top+1 + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, comctl32_color.clrBtnHighlight);
            TOOLBAR_DrawArrow(hdc, rcArrow.left, rcArrow.top + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, comctl32_color.clr3dShadow);
        }
#ifndef __REACTOS__
        else if (tbcd.nmcd.uItemState & (CDIS_SELECTED | CDIS_CHECKED))
        {
            offset = (dwItemCDFlag & TBCDRF_NOOFFSET) ? 0 : 1;
            TOOLBAR_DrawArrow(hdc, rcArrow.left + offset, rcArrow.top + offset + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, comctl32_color.clrBtnText);
        }
        else
            TOOLBAR_DrawArrow(hdc, rcArrow.left, rcArrow.top + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, comctl32_color.clrBtnText);
#else
        else
        {
            COLORREF clr = comctl32_color.clrBtnText;
            if (theme)
                GetThemeColor(theme, TP_BUTTON, TS_NORMAL, TMT_TEXTCOLOR, &clr);

            if (tbcd.nmcd.uItemState & (CDIS_SELECTED | CDIS_CHECKED))
            {
                offset = (dwItemCDFlag & TBCDRF_NOOFFSET) ? 0 : 1;
                TOOLBAR_DrawArrow(hdc, rcArrow.left + offset, rcArrow.top + offset + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, clr);
            }
            else
                TOOLBAR_DrawArrow(hdc, rcArrow.left, rcArrow.top + (rcArrow.bottom - rcArrow.top - ARROW_HEIGHT) / 2, clr);
        }
#endif
    }

    if (dwItemCustDraw & CDRF_NOTIFYPOSTPAINT)
    {
        tbcd.nmcd.dwDrawStage = CDDS_ITEMPOSTPAINT;
        TOOLBAR_SendNotify(&tbcd.nmcd.hdr, infoPtr, NM_CUSTOMDRAW);
    }

}