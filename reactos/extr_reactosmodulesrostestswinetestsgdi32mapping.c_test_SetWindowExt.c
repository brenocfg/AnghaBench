#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_7__ {scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ POINT ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetViewportExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetViewportOrgEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowOrgEx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SetWindowExtEx (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rough_match (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void test_SetWindowExt(HDC hdc, LONG cx, LONG cy, LONG expected_vp_cx, LONG expected_vp_cy)
{
    SIZE windowExt, viewportExt;
    POINT windowOrg, windowOrgAfter, viewportOrg, viewportOrgAfter;

    GetWindowOrgEx(hdc, &windowOrg);
    GetViewportOrgEx(hdc, &viewportOrg);

    SetWindowExtEx(hdc, cx, cy, NULL);
    GetWindowExtEx(hdc, &windowExt);
    ok(windowExt.cx == cx && windowExt.cy == cy,
       "Window extension: Expected %dx%d, got %dx%d\n",
       cx, cy, windowExt.cx, windowExt.cy);

    GetViewportExtEx(hdc, &viewportExt);
    ok(rough_match(viewportExt.cx, expected_vp_cx) && rough_match(viewportExt.cy, expected_vp_cy),
        "Viewport extents have not been properly adjusted: Expected %dx%d, got %dx%d\n",
        expected_vp_cx, expected_vp_cy, viewportExt.cx, viewportExt.cy);

    GetWindowOrgEx(hdc, &windowOrgAfter);
    ok(windowOrg.x == windowOrgAfter.x && windowOrg.y == windowOrgAfter.y,
        "Window origin changed from (%d,%d) to (%d,%d)\n",
        windowOrg.x, windowOrg.y, windowOrgAfter.x, windowOrgAfter.y);

    GetViewportOrgEx(hdc, &viewportOrgAfter);
    ok(viewportOrg.x == viewportOrgAfter.x && viewportOrg.y == viewportOrgAfter.y,
        "Viewport origin changed from (%d,%d) to (%d,%d)\n",
        viewportOrg.x, viewportOrg.y, viewportOrgAfter.x, viewportOrgAfter.y);
}