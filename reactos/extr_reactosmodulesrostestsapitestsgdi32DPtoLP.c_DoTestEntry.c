#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int eM11; int eM12; int eM21; int eM22; scalar_t__ eDy; scalar_t__ eDx; } ;
typedef  TYPE_3__ XFORM ;
struct TYPE_21__ {int x; int y; } ;
struct TYPE_20__ {int cx; int cy; } ;
struct TYPE_16__ {int x; int y; } ;
struct TYPE_17__ {int /*<<< orphan*/  cyView; int /*<<< orphan*/  cxView; int /*<<< orphan*/  yView; int /*<<< orphan*/  xView; int /*<<< orphan*/  cyWnd; int /*<<< orphan*/  cxWnd; int /*<<< orphan*/  yWnd; int /*<<< orphan*/  xWnd; } ;
struct TYPE_19__ {scalar_t__ bWndExt; int xWndOut; int yWndOut; int cxWndOut; int cyWndOut; int xViewOut; int yViewOut; int cxViewOut; int cyViewOut; scalar_t__ ret; TYPE_1__ ptDest; int /*<<< orphan*/  lineno; TYPE_6__ ptSrc; int /*<<< orphan*/  error; TYPE_2__ preset; int /*<<< orphan*/  nMapMode; } ;
typedef  TYPE_4__ TEST_ENTRY ;
typedef  TYPE_5__ SIZE ;
typedef  TYPE_6__ POINT ;
typedef  int LONG ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int CALC_VALUE_1 ; 
 int CALC_VALUE_2 ; 
 int CALC_VALUE_3 ; 
 int DISPLAY_SIZE ; 
 scalar_t__ DPtoLP (int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetViewportExtEx (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ GetViewportOrgEx (int /*<<< orphan*/ ,TYPE_6__*) ; 
 scalar_t__ GetWindowExtEx (int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ GetWindowOrgEx (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 scalar_t__ InverseXForm (TYPE_3__*) ; 
 int MulDiv (int,int,int) ; 
 int NEGA_DISPLAY_SIZE ; 
 int NO_CHECK ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SetViewportExtEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetViewportOrgEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetWindowExtEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SetWindowOrgEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetXForm1 (TYPE_3__*) ; 
 int /*<<< orphan*/  SetXForm2 (TYPE_3__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VERTRES ; 
 int labs (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void DoTestEntry(HDC hDC, const TEST_ENTRY *entry)
{
    POINT pt, ptWnd, ptView;
    SIZE siz, sizWnd, sizView;
    INT ret;

    SetMapMode(hDC, entry->nMapMode);

    ret = SetWindowOrgEx(hDC, entry->preset.xWnd, entry->preset.yWnd, NULL);
    ok(ret == TRUE, "Line %d: SetWindowOrgEx failed\n", entry->lineno);

    ret = SetWindowExtEx(hDC, entry->preset.cxWnd, entry->preset.cyWnd, NULL);
    ok(ret == entry->bWndExt, "Line %d: SetWindowExtEx() expected %d, was %d\n", entry->lineno, entry->bWndExt, ret);

    ret = SetViewportOrgEx(hDC, entry->preset.xView, entry->preset.yView, NULL);
    ok(ret == TRUE, "Line %d: SetViewportOrgEx failed\n", entry->lineno);

    ret = SetViewportExtEx(hDC, entry->preset.cxView, entry->preset.cyView, NULL);
    ok(ret == TRUE, "Line %d: SetViewportExtEx failed\n", entry->lineno);

    ok(GetWindowOrgEx(hDC, &pt) == TRUE, "Line %d: GetWindowOrgEx failed\n", entry->lineno);
    ptWnd = pt;
    ok(GetWindowExtEx(hDC, &siz) == TRUE, "Line %d: GetWindowExtEx failed\n", entry->lineno);
    sizWnd = siz;

    ok(pt.x == entry->xWndOut && pt.y == entry->yWndOut,
       "Line %d: Window org expected (%ld, %ld), was (%ld, %ld)\n",
        entry->lineno, entry->xWndOut, entry->yWndOut, pt.x, pt.y);

    if (entry->cxWndOut == DISPLAY_SIZE || entry->cxWndOut == NEGA_DISPLAY_SIZE)
    {
        LONG cx = GetDeviceCaps(hDC, HORZRES);
        LONG cy = GetDeviceCaps(hDC, VERTRES);
        if (entry->cxWndOut == NEGA_DISPLAY_SIZE)
            cx = -cx;
        if (entry->cyWndOut == NEGA_DISPLAY_SIZE)
            cy = -cy;
        ok(siz.cx == cx && siz.cy == cy,
           "Line %d: Window ext expected display size (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, cx, cy, siz.cx, siz.cy);
    }
    else if (entry->cxWndOut != NO_CHECK)
    {
        ok(siz.cx == entry->cxWndOut && siz.cy == entry->cyWndOut,
           "Line %d: Window ext expected (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, entry->cxWndOut, entry->cyWndOut, siz.cx, siz.cy);
    }

    ok(GetViewportOrgEx(hDC, &pt) == TRUE, "Line %d: GetViewportOrgEx failed\n", entry->lineno);
    ptView = pt;
    ok(GetViewportExtEx(hDC, &siz) == TRUE, "Line %d: GetViewportExtEx failed\n", entry->lineno);
    sizView = siz;

    ok(pt.x == entry->xViewOut && pt.y == entry->yViewOut,
       "Line %d: Viewport org expected (%ld, %ld), was (%ld, %ld)\n",
        entry->lineno, entry->xViewOut , entry->yViewOut, pt.x, pt.y);

    if (entry->cxViewOut == DISPLAY_SIZE || entry->cxViewOut == NEGA_DISPLAY_SIZE)
    {
        LONG cx = GetDeviceCaps(hDC, HORZRES);
        LONG cy = GetDeviceCaps(hDC, VERTRES);
        if (entry->cxViewOut == NEGA_DISPLAY_SIZE)
            cx = -cx;
        if (entry->cyViewOut == NEGA_DISPLAY_SIZE)
            cy = -cy;
        ok(siz.cx == cx && siz.cy == cy,
           "Line %d: Viewport ext expected display size (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, cx, cy, siz.cx, siz.cy);
    }
    else if (entry->cxViewOut != NO_CHECK)
    {
        ok(siz.cx == entry->cxViewOut && siz.cy == entry->cyViewOut,
           "Line %d: Viewport ext expected (%ld, %ld), was (%ld, %ld)\n",
            entry->lineno, entry->cxViewOut, entry->cyViewOut, siz.cx, siz.cy);
    }

    pt = entry->ptSrc;

    SetLastError(0xDEADBEEF);
    ret = DPtoLP(hDC, &pt, 1);
    ok(ret == entry->ret, "Line %d: DPtoLP() expected %d, was %d\n", entry->lineno, entry->ret, ret);

    ok(GetLastError() == entry->error, "Line %d: GetLastError() expected %ld, was %ld\n",
       entry->lineno, entry->error, GetLastError());

    if (entry->ptDest.x == CALC_VALUE_1)
    {
        LONG x = MulDiv(entry->ptSrc.x - ptView.x, sizWnd.cx, sizView.cx) + ptWnd.x;
        LONG y = MulDiv(entry->ptSrc.y - ptView.y, sizWnd.cy, sizView.cy) + ptWnd.y;
        // TODO: make more accurate
        ok(labs(pt.x - x) <= 1 && labs(pt.y - y) <= 1,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, x, y, pt.x, pt.y);
    }
    else if (entry->ptDest.x == CALC_VALUE_2)
    {
        XFORM xform;
        LONG x, y;
        SetXForm1(&xform);
        if (InverseXForm(&xform))
        {
            x = MulDiv(entry->ptSrc.x - ptView.x, sizWnd.cx, sizView.cx) + ptWnd.x;
            y = MulDiv(entry->ptSrc.y - ptView.y, sizWnd.cy, sizView.cy) + ptWnd.y;
            x = (LONG)((xform.eM11 * x + xform.eM12 * y) + xform.eDx);
            y = (LONG)((xform.eM21 * x + xform.eM22 * y) + xform.eDy);
            // TODO: make more accurate
            ok(labs(pt.x - x) <= 1 && labs(pt.y - y) <= 1,
               "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
               entry->lineno, x, y, pt.x, pt.y);
        }
    }
    else if (entry->ptDest.x == CALC_VALUE_3)
    {
        XFORM xform;
        LONG x, y;
        SetXForm2(&xform);
        if (InverseXForm(&xform))
        {
            x = MulDiv(entry->ptSrc.x - ptView.x, sizWnd.cx, sizView.cx) + ptWnd.x;
            y = MulDiv(entry->ptSrc.y - ptView.y, sizWnd.cy, sizView.cy) + ptWnd.y;
            x = (LONG)((xform.eM11 * x + xform.eM12 * y) + xform.eDx);
            y = (LONG)((xform.eM21 * x + xform.eM22 * y) + xform.eDy);
            // TODO: make more accurate
            ok(labs(pt.x - x) <= 2 && labs(pt.y - y) <= 2,
               "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
               entry->lineno, x, y, pt.x, pt.y);
        }
    }
    else if (entry->ptDest.x != NO_CHECK)
    {
        ok(pt.x == entry->ptDest.x && pt.y == entry->ptDest.y,
           "Line %d: Dest expected (%ld, %ld), was (%ld, %ld)\n",
           entry->lineno, entry->ptDest.x, entry->ptDest.y, pt.x, pt.y);
    }
}