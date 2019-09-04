#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {long y; scalar_t__ x; } ;
struct TYPE_10__ {long right; long bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_LPARAMTOPOINT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 long MAXHORI ; 
 long MAXVERT ; 
 int /*<<< orphan*/  PtInRect (TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CC_MouseCheckColorGraph( HWND hDlg, int dlgitem, int *hori, int *vert, LPARAM lParam )
{
 HWND hwnd;
 POINT point;
 RECT rect;
 long x,y;

 CONV_LPARAMTOPOINT(lParam, &point);
 ClientToScreen(hDlg, &point);
 hwnd = GetDlgItem( hDlg, dlgitem );
 GetWindowRect(hwnd, &rect);

 if (!PtInRect(&rect, point))
  return FALSE;

 GetClientRect(hwnd, &rect);
 ScreenToClient(hwnd, &point);

 x = (long) point.x * MAXHORI;
 x /= rect.right;
 y = (long) (rect.bottom - point.y) * MAXVERT;
 y /= rect.bottom;

 if (x < 0) x = 0;
 if (y < 0) y = 0;
 if (x > MAXHORI) x = MAXHORI;
 if (y > MAXVERT) y = MAXVERT;

 if (hori)
  *hori = x;
 if (vert)
  *vert = y;

 return TRUE;
}