#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  enum SCROLL_HITTEST { ____Placeholder_SCROLL_HITTEST } SCROLL_HITTEST ;
struct TYPE_12__ {unsigned int left; unsigned int top; unsigned int bottom; unsigned int right; } ;
struct TYPE_11__ {int cbSize; int /*<<< orphan*/  fMask; } ;
struct TYPE_10__ {unsigned int cy; unsigned int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTHEME ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_DOWNNORMAL ; 
 int /*<<< orphan*/  ABS_LEFTNORMAL ; 
 int /*<<< orphan*/  ABS_RIGHTNORMAL ; 
 int /*<<< orphan*/  ABS_UPNORMAL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetThemePartSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  SBP_ARROWBTN ; 
 int SBS_VERT ; 
 int /*<<< orphan*/  SB_CTL ; 
 int SCROLL_BOTTOM_ARROW ; 
 int SCROLL_BOTTOM_RECT ; 
 unsigned int SCROLL_MIN_RECT ; 
 int SCROLL_NOWHERE ; 
 int SCROLL_THUMB ; 
 int SCROLL_TOP_ARROW ; 
 int SCROLL_TOP_RECT ; 
 int /*<<< orphan*/  SIF_ALL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TS_DRAW ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  calc_thumb_dimensions (unsigned int,TYPE_2__*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void redraw_part(HWND hwnd, HTHEME theme, enum SCROLL_HITTEST part)
{
    DWORD style = GetWindowLongW(hwnd, GWL_STYLE);
    BOOL vertical = style & SBS_VERT;
    SIZE sz;
    RECT r, partrect;
    unsigned int size, upsize, downsize;

    if (part == SCROLL_NOWHERE) { /* redraw everything */
        InvalidateRect(hwnd, NULL, TRUE);
        return;
    }

    GetWindowRect(hwnd, &r);
    OffsetRect(&r, -r.left, -r.top);

    if (vertical) {
        size = r.bottom;

        if (FAILED(GetThemePartSize(theme, NULL, SBP_ARROWBTN, ABS_UPNORMAL, NULL, TS_DRAW, &sz))) {
            WARN("Could not get up arrow size.\n");
            upsize = 0;
        } else
            upsize = sz.cy;

        if (FAILED(GetThemePartSize(theme, NULL, SBP_ARROWBTN, ABS_DOWNNORMAL, NULL, TS_DRAW, &sz))) {
            WARN("Could not get down arrow size.\n");
            downsize = 0;
        } else
            downsize = sz.cy;
    } else {
        size = r.right;

        if (FAILED(GetThemePartSize(theme, NULL, SBP_ARROWBTN, ABS_LEFTNORMAL, NULL, TS_DRAW, &sz))) {
            WARN("Could not get left arrow size.\n");
            upsize = 0;
        } else
            upsize = sz.cx;

        if (FAILED(GetThemePartSize(theme, NULL, SBP_ARROWBTN, ABS_RIGHTNORMAL, NULL, TS_DRAW, &sz))) {
            WARN("Could not get right arrow size.\n");
            downsize = 0;
        } else
            downsize = sz.cx;
    }

    if (size < SCROLL_MIN_RECT + upsize + downsize)
        upsize = downsize = (size - SCROLL_MIN_RECT)/2;

    partrect = r;

    if (part == SCROLL_TOP_ARROW) {
        if (vertical)
            partrect.bottom = partrect.top + upsize;
        else
            partrect.right = partrect.left + upsize;
    } else if (part == SCROLL_BOTTOM_ARROW) {
        if (vertical)
            partrect.top = partrect.bottom - downsize;
        else
            partrect.left = partrect.right - downsize;
    } else {
        unsigned int thumbpos, thumbsize;
        SCROLLINFO si;

        si.cbSize = sizeof(si);
        si.fMask = SIF_ALL;
        if (!GetScrollInfo(hwnd, SB_CTL, &si)) {
            WARN("GetScrollInfo failed.\n");
            return;
        }

        calc_thumb_dimensions(size - upsize - downsize, &si, &thumbpos, &thumbsize);

        if (part == SCROLL_TOP_RECT) {
            if (vertical) {
                partrect.top = r.top + upsize;
                partrect.bottom = partrect.top + thumbpos;
            } else {
                partrect.left = r.left + upsize;
                partrect.right = partrect.left + thumbpos;
            }
        } else if (part == SCROLL_THUMB) {
            if (vertical) {
                partrect.top = r.top + upsize + thumbpos;
                partrect.bottom = partrect.top + thumbsize;
            } else {
                partrect.left = r.left + upsize + thumbpos;
                partrect.right = partrect.left + thumbsize;
            }
        } else if (part == SCROLL_BOTTOM_RECT) {
            if (vertical) {
                partrect.top = r.top + upsize + thumbpos + thumbsize;
                partrect.bottom = r.bottom - downsize;
            } else {
                partrect.left = r.left + upsize + thumbpos + thumbsize;
                partrect.right = r.right - downsize;
            }
        }
    }

    InvalidateRect(hwnd, &partrect, TRUE);
}