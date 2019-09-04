#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ height; scalar_t__ bottom; scalar_t__ width; scalar_t__ right; } ;
struct TYPE_9__ {int dwAnchor; int /*<<< orphan*/  iItemId; } ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  TYPE_2__ LAYOUT_INFO ;
typedef  TYPE_3__ LAYOUT_DATA ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int BF_BOTTOM ; 
 int BF_LEFT ; 
 int BF_RIGHT ; 
 int BF_TOP ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_DESKTOP ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LayoutUpdate(HWND hwnd, LAYOUT_DATA *data, const LAYOUT_INFO *layout_info, int layout_count)
{
    RECT rcWnd;
    int i;

    GetClientRect(hwnd, &rcWnd);
    for (i = 0; i < layout_count; i++)
    {
        RECT r;
        HWND hItem = GetDlgItem(hwnd, layout_info[i].iItemId);

        GetWindowRect(hItem, &r);
        MapWindowPoints(HWND_DESKTOP, hwnd, (LPPOINT)&r, 2);

        if (layout_info[i].dwAnchor & BF_RIGHT)
        {
            r.right = rcWnd.right - data[i].right;
            if (!(layout_info[i].dwAnchor & BF_LEFT))
                r.left = r.right - data[i].width;
        }

        if (layout_info[i].dwAnchor & BF_BOTTOM)
        {
            r.bottom = rcWnd.bottom - data[i].bottom;
            if (!(layout_info[i].dwAnchor & BF_TOP))
                r.top = r.bottom - data[i].height;
        }

        SetWindowPos(hItem, NULL, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER);
    }
}