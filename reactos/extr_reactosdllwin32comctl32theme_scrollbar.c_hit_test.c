#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  enum SCROLL_HITTEST { ____Placeholder_SCROLL_HITTEST } SCROLL_HITTEST ;
struct TYPE_14__ {unsigned int y; unsigned int x; } ;
struct TYPE_13__ {unsigned int bottom; unsigned int right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_12__ {int cbSize; int /*<<< orphan*/  fMask; } ;
struct TYPE_11__ {unsigned int cy; unsigned int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_4__ POINT ;
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
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  TS_DRAW ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  calc_thumb_dimensions (unsigned int,TYPE_2__*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static enum SCROLL_HITTEST hit_test(HWND hwnd, HTHEME theme, POINT pt)
{
    RECT r;
    DWORD style = GetWindowLongW(hwnd, GWL_STYLE);
    BOOL vertical = style & SBS_VERT;
    SIZE sz;
    SCROLLINFO si;
    unsigned int offset, size, upsize, downsize, thumbpos, thumbsize;

    GetWindowRect(hwnd, &r);
    OffsetRect(&r, -r.left, -r.top);

    if (vertical) {
        offset = pt.y;
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
        offset = pt.x;
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

    if (pt.x < 0 || pt.x > r.right || pt.y < 0 || pt.y > r.bottom)
        return SCROLL_NOWHERE;

    if (size < SCROLL_MIN_RECT + upsize + downsize)
        upsize = downsize = (size - SCROLL_MIN_RECT)/2;

    if (offset < upsize)
        return SCROLL_TOP_ARROW;

    if (offset > size - downsize)
        return SCROLL_BOTTOM_ARROW;

    si.cbSize = sizeof(si);
    si.fMask = SIF_ALL;
    if (!GetScrollInfo(hwnd, SB_CTL, &si)) {
        WARN("GetScrollInfo failed.\n");
        return SCROLL_NOWHERE;
    }

    calc_thumb_dimensions(size - upsize - downsize, &si, &thumbpos, &thumbsize);

    if (offset < upsize + thumbpos)
        return SCROLL_TOP_RECT;
    else if (offset < upsize + thumbpos + thumbsize)
        return SCROLL_THUMB;
    else
        return SCROLL_BOTTOM_RECT;
}