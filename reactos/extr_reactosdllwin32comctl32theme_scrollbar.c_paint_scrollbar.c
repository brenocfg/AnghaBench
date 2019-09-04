#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  sbi ;
struct TYPE_19__ {unsigned int cyTopHeight; unsigned int cyBottomHeight; unsigned int cxLeftWidth; unsigned int cxRightWidth; } ;
struct TYPE_18__ {scalar_t__ left; scalar_t__ top; scalar_t__ bottom; scalar_t__ right; } ;
struct TYPE_17__ {int cbSize; } ;
struct TYPE_16__ {int cbSize; int /*<<< orphan*/  fMask; } ;
struct TYPE_15__ {unsigned int cy; unsigned int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ SCROLLBARINFO ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_5__ MARGINS ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ABS_DOWNDISABLED ; 
 int ABS_DOWNHOT ; 
 int ABS_DOWNNORMAL ; 
 int ABS_LEFTDISABLED ; 
 int ABS_LEFTHOT ; 
 int ABS_LEFTNORMAL ; 
 int ABS_RIGHTDISABLED ; 
 int ABS_RIGHTHOT ; 
 int ABS_RIGHTNORMAL ; 
 int ABS_UPDISABLED ; 
 int ABS_UPHOT ; 
 int ABS_UPNORMAL ; 
 int /*<<< orphan*/  BeginPaint (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetScrollBarInfo (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  GetScrollInfo (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetThemeMargins (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  GetThemePartSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetWindowLongW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  IsWindowEnabled (scalar_t__) ; 
 int /*<<< orphan*/  OBJID_CLIENT ; 
 int /*<<< orphan*/  OffsetRect (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SBP_ARROWBTN ; 
 int /*<<< orphan*/  SBP_GRIPPERHORZ ; 
 int /*<<< orphan*/  SBP_GRIPPERVERT ; 
 int /*<<< orphan*/  SBP_LOWERTRACKHORZ ; 
 int /*<<< orphan*/  SBP_LOWERTRACKVERT ; 
 int /*<<< orphan*/  SBP_SIZEBOX ; 
 int /*<<< orphan*/  SBP_THUMBBTNHORZ ; 
 int /*<<< orphan*/  SBP_THUMBBTNVERT ; 
 int /*<<< orphan*/  SBP_UPPERTRACKHORZ ; 
 int /*<<< orphan*/  SBP_UPPERTRACKVERT ; 
 int SBS_SIZEBOX ; 
 int SBS_SIZEBOXTOPLEFTALIGN ; 
 int SBS_SIZEGRIP ; 
 int SBS_VERT ; 
 int /*<<< orphan*/  SB_CTL ; 
 int SCRBS_DISABLED ; 
 int SCRBS_HOT ; 
 int SCRBS_NORMAL ; 
 scalar_t__ SCROLL_BOTTOM_ARROW ; 
 scalar_t__ SCROLL_BOTTOM_RECT ; 
 scalar_t__ SCROLL_MIN_RECT ; 
 scalar_t__ SCROLL_THUMB ; 
 scalar_t__ SCROLL_TOP_ARROW ; 
 scalar_t__ SCROLL_TOP_RECT ; 
 int /*<<< orphan*/  SIF_ALL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int SZB_RIGHTALIGN ; 
 int SZB_TOPLEFTALIGN ; 
 int /*<<< orphan*/  TMT_CONTENTMARGINS ; 
 int /*<<< orphan*/  TS_DRAW ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  calc_thumb_dimensions (unsigned int,TYPE_2__*,unsigned int*,unsigned int*) ; 
 scalar_t__ tracking_hot_part ; 
 scalar_t__ tracking_win ; 

__attribute__((used)) static void paint_scrollbar(HWND hwnd, HTHEME theme)
{
    HDC dc;
    PAINTSTRUCT ps;
    RECT r;
    DWORD style = GetWindowLongW(hwnd, GWL_STYLE);
    BOOL vertical = style & SBS_VERT;
    BOOL disabled = !IsWindowEnabled(hwnd);

    GetWindowRect(hwnd, &r);
    OffsetRect(&r, -r.left, -r.top);

    dc = BeginPaint(hwnd, &ps);

    if (style & SBS_SIZEBOX || style & SBS_SIZEGRIP) {
        int state;

        if (style & SBS_SIZEBOXTOPLEFTALIGN)
            state = SZB_TOPLEFTALIGN;
        else
            state = SZB_RIGHTALIGN;

        DrawThemeBackground(theme, dc, SBP_SIZEBOX, state, &r, NULL);
    } else {
        SCROLLBARINFO sbi;
        SCROLLINFO si;
        unsigned int thumbpos, thumbsize;
        int uppertrackstate, lowertrackstate, thumbstate;
        RECT partrect, trackrect;
        SIZE grippersize;

        sbi.cbSize = sizeof(sbi);
        GetScrollBarInfo(hwnd, OBJID_CLIENT, &sbi);

        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        GetScrollInfo(hwnd, SB_CTL, &si);

        trackrect = r;

        if (disabled) {
            uppertrackstate = SCRBS_DISABLED;
            lowertrackstate = SCRBS_DISABLED;
            thumbstate = SCRBS_DISABLED;
        } else {
            uppertrackstate = SCRBS_NORMAL;
            lowertrackstate = SCRBS_NORMAL;
            thumbstate = SCRBS_NORMAL;

            if (tracking_win == hwnd) {
                if (tracking_hot_part == SCROLL_TOP_RECT)
                    uppertrackstate = SCRBS_HOT;
                else if (tracking_hot_part == SCROLL_BOTTOM_RECT)
                    lowertrackstate = SCRBS_HOT;
                else if (tracking_hot_part == SCROLL_THUMB)
                    thumbstate = SCRBS_HOT;
            }
        }

        if (vertical) {
            SIZE upsize, downsize;
            int uparrowstate, downarrowstate;

            if (disabled) {
                uparrowstate = ABS_UPDISABLED;
                downarrowstate = ABS_DOWNDISABLED;
            } else {
                uparrowstate = ABS_UPNORMAL;
                downarrowstate = ABS_DOWNNORMAL;

                if (tracking_win == hwnd) {
                    if (tracking_hot_part == SCROLL_TOP_ARROW)
                        uparrowstate = ABS_UPHOT;
                    else if (tracking_hot_part == SCROLL_BOTTOM_ARROW)
                        downarrowstate = ABS_DOWNHOT;
                }
            }

            if (FAILED(GetThemePartSize(theme, dc, SBP_ARROWBTN, uparrowstate, NULL, TS_DRAW, &upsize))) {
                WARN("Could not get up arrow size.\n");
                return;
            }

            if (FAILED(GetThemePartSize(theme, dc, SBP_ARROWBTN, downarrowstate, NULL, TS_DRAW, &downsize))) {
                WARN("Could not get down arrow size.\n");
                return;
            }

            if (r.bottom - r.top - upsize.cy - downsize.cy < SCROLL_MIN_RECT)
                upsize.cy = downsize.cy = (r.bottom - r.top - SCROLL_MIN_RECT)/2;

            partrect = r;
            partrect.bottom = partrect.top + upsize.cy;
            DrawThemeBackground(theme, dc, SBP_ARROWBTN, uparrowstate, &partrect, NULL);

            trackrect.top = partrect.bottom;

            partrect.bottom = r.bottom;
            partrect.top = partrect.bottom - downsize.cy;
            DrawThemeBackground(theme, dc, SBP_ARROWBTN, downarrowstate, &partrect, NULL);

            trackrect.bottom = partrect.top;

            calc_thumb_dimensions(trackrect.bottom - trackrect.top, &si, &thumbpos, &thumbsize);

            if (thumbpos > 0) {
                partrect.top = trackrect.top;
                partrect.bottom = partrect.top + thumbpos;

                DrawThemeBackground(theme, dc, SBP_UPPERTRACKVERT, uppertrackstate, &partrect, NULL);
            }

            if (thumbsize > 0) {
                partrect.top = trackrect.top + thumbpos;
                partrect.bottom = partrect.top + thumbsize;

                DrawThemeBackground(theme, dc, SBP_THUMBBTNVERT, thumbstate, &partrect, NULL);

                if (SUCCEEDED(GetThemePartSize(theme, dc, SBP_GRIPPERVERT, thumbstate, NULL, TS_DRAW, &grippersize))) {
                    MARGINS margins;

                    if (SUCCEEDED(GetThemeMargins(theme, dc, SBP_THUMBBTNVERT, thumbstate, TMT_CONTENTMARGINS, &partrect, &margins))) {
                        if (grippersize.cy <= (thumbsize - margins.cyTopHeight - margins.cyBottomHeight))
                            DrawThemeBackground(theme, dc, SBP_GRIPPERVERT, thumbstate, &partrect, NULL);
                    }
                }
            }

            if (thumbpos + thumbsize < trackrect.bottom - trackrect.top) {
                partrect.bottom = trackrect.bottom;
                partrect.top = trackrect.top + thumbsize + thumbpos;

                DrawThemeBackground(theme, dc, SBP_LOWERTRACKVERT, lowertrackstate, &partrect, NULL);
            }
        } else {
            SIZE leftsize, rightsize;
            int leftarrowstate, rightarrowstate;

            if (disabled) {
                leftarrowstate = ABS_LEFTDISABLED;
                rightarrowstate = ABS_RIGHTDISABLED;
            } else {
                leftarrowstate = ABS_LEFTNORMAL;
                rightarrowstate = ABS_RIGHTNORMAL;

                if (tracking_win == hwnd) {
                    if (tracking_hot_part == SCROLL_TOP_ARROW)
                        leftarrowstate = ABS_LEFTHOT;
                    else if (tracking_hot_part == SCROLL_BOTTOM_ARROW)
                        rightarrowstate = ABS_RIGHTHOT;
                }
            }

            if (FAILED(GetThemePartSize(theme, dc, SBP_ARROWBTN, leftarrowstate, NULL, TS_DRAW, &leftsize))) {
                WARN("Could not get left arrow size.\n");
                return;
            }

            if (FAILED(GetThemePartSize(theme, dc, SBP_ARROWBTN, rightarrowstate, NULL, TS_DRAW, &rightsize))) {
                WARN("Could not get right arrow size.\n");
                return;
            }

            if (r.right - r.left - leftsize.cx - rightsize.cx < SCROLL_MIN_RECT)
                leftsize.cx = rightsize.cx = (r.right - r.left - SCROLL_MIN_RECT)/2;

            partrect = r;
            partrect.right = partrect.left + leftsize.cx;
            DrawThemeBackground(theme, dc, SBP_ARROWBTN, leftarrowstate, &partrect, NULL);

            trackrect.left = partrect.right;

            partrect.right = r.right;
            partrect.left = partrect.right - rightsize.cx;
            DrawThemeBackground(theme, dc, SBP_ARROWBTN, rightarrowstate, &partrect, NULL);

            trackrect.right = partrect.left;

            calc_thumb_dimensions(trackrect.right - trackrect.left, &si, &thumbpos, &thumbsize);

            if (thumbpos > 0) {
                partrect.left = trackrect.left;
                partrect.right = partrect.left + thumbpos;

                DrawThemeBackground(theme, dc, SBP_UPPERTRACKHORZ, uppertrackstate, &partrect, NULL);
            }

            if (thumbsize > 0) {
                partrect.left = trackrect.left + thumbpos;
                partrect.right = partrect.left + thumbsize;

                DrawThemeBackground(theme, dc, SBP_THUMBBTNHORZ, thumbstate, &partrect, NULL);

                if (SUCCEEDED(GetThemePartSize(theme, dc, SBP_GRIPPERHORZ, thumbstate, NULL, TS_DRAW, &grippersize))) {
                    MARGINS margins;

                    if (SUCCEEDED(GetThemeMargins(theme, dc, SBP_THUMBBTNHORZ, thumbstate, TMT_CONTENTMARGINS, &partrect, &margins))) {
                        if (grippersize.cx <= (thumbsize - margins.cxLeftWidth - margins.cxRightWidth))
                            DrawThemeBackground(theme, dc, SBP_GRIPPERHORZ, thumbstate, &partrect, NULL);
                    }
                }
            }

            if (thumbpos + thumbsize < trackrect.right - trackrect.left) {
                partrect.right = trackrect.right;
                partrect.left = trackrect.left + thumbsize + thumbpos;

                DrawThemeBackground(theme, dc, SBP_LOWERTRACKHORZ, lowertrackstate, &partrect, NULL);
            }
        }
    }

    EndPaint(hwnd, &ps);
}