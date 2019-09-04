#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {short iNavWidth; } ;
struct TYPE_6__ {TYPE_1__ WinType; } ;
struct TYPE_5__ {short x; short y; } ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ HHInfo ;

/* Variables and functions */
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Help_OnSize (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 

__attribute__((used)) static void SB_OnLButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    HHInfo *pHHInfo = (HHInfo *)GetWindowLongPtrW(hWnd, 0);
    POINT pt;

    pt.x = (short)LOWORD(lParam);
    pt.y = (short)HIWORD(lParam);

    /* update the window sizes */
    pHHInfo->WinType.iNavWidth += pt.x;
    Help_OnSize(hWnd);

    ReleaseCapture();
}