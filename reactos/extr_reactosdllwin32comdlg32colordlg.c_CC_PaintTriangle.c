#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int top; int bottom; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_12__ {int /*<<< orphan*/  hwndSelf; TYPE_7__ old3angle; scalar_t__ l; } ;
struct TYPE_11__ {int y; scalar_t__ x; } ;
struct TYPE_10__ {int bottom; int top; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  TYPE_3__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_BRUSH ; 
 int /*<<< orphan*/  COLOR_BTNFACE ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  GCLP_HBRBACKGROUND ; 
 scalar_t__ GetClassLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDialogBaseUnits () ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 scalar_t__ GetSysColorBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 int /*<<< orphan*/  IDC_COLOR_LUMBAR ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ MAXVERT ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void CC_PaintTriangle(CCPRIV *infoPtr)
{
 HDC hDC;
 long temp;
 int w = LOWORD(GetDialogBaseUnits()) / 2;
 POINT points[3];
 int height;
 int oben;
 RECT rect;
 HBRUSH hbr;
 HWND hwnd = GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_LUMBAR);

 if (IsWindowVisible( GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_GRAPH)))   /* if full size */
 {
   GetClientRect(hwnd, &rect);
   height = rect.bottom;
   hDC = GetDC(infoPtr->hwndSelf);
   points[0].y = rect.top;
   points[0].x = rect.right;                  /*  |  /|  */
   ClientToScreen(hwnd, points);              /*  | / |  */
   ScreenToClient(infoPtr->hwndSelf, points); /*  |<  |  */
   oben = points[0].y;                        /*  | \ |  */
                                              /*  |  \|  */
   temp = (long)height * (long)infoPtr->l;
   points[0].x += 1;
   points[0].y = oben + height - temp / (long)MAXVERT;
   points[1].y = points[0].y + w;
   points[2].y = points[0].y - w;
   points[2].x = points[1].x = points[0].x + w;

   hbr = (HBRUSH)GetClassLongPtrW( hwnd, GCLP_HBRBACKGROUND);
   if (!hbr) hbr = GetSysColorBrush(COLOR_BTNFACE);
   FillRect(hDC, &infoPtr->old3angle, hbr);
   infoPtr->old3angle.left  = points[0].x;
   infoPtr->old3angle.right = points[1].x + 1;
   infoPtr->old3angle.top   = points[2].y - 1;
   infoPtr->old3angle.bottom= points[1].y + 1;

   hbr = SelectObject(hDC, GetStockObject(BLACK_BRUSH));
   Polygon(hDC, points, 3);
   SelectObject(hDC, hbr);

   ReleaseDC(infoPtr->hwndSelf, hDC);
 }
}