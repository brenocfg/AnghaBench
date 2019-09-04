#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* lpcc; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_15__ {int x; int y; } ;
struct TYPE_14__ {int right; int left; int bottom; int top; } ;
struct TYPE_13__ {int /*<<< orphan*/  rgbResult; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_4__ CCPRIV ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CC_DrawFocusRect (TYPE_4__*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  CONV_LPARAMTOPOINT (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int DISTANCE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDC_COLOR_PREDEF ; 
 scalar_t__ PtInRect (TYPE_2__*,TYPE_3__) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ ** predefcolors ; 

__attribute__((used)) static BOOL CC_MouseCheckPredefColorArray(CCPRIV *lpp, int rows, int cols, LPARAM lParam)
{
 HWND hwnd;
 POINT point;
 RECT rect;
 int dx, dy, x, y;

 CONV_LPARAMTOPOINT(lParam, &point);
 ClientToScreen(lpp->hwndSelf, &point);
 hwnd = GetDlgItem(lpp->hwndSelf, IDC_COLOR_PREDEF);
 GetWindowRect(hwnd, &rect);
 if (PtInRect(&rect, point))
 {
  dx = (rect.right - rect.left) / cols;
  dy = (rect.bottom - rect.top) / rows;
  ScreenToClient(hwnd, &point);

  if (point.x % dx < ( dx - DISTANCE) && point.y % dy < ( dy - DISTANCE))
  {
   x = point.x / dx;
   y = point.y / dy;
   lpp->lpcc->rgbResult = predefcolors[y][x];
   CC_DrawFocusRect(lpp, hwnd, x, y, rows, cols);
   return TRUE;
  }
 }
 return FALSE;
}