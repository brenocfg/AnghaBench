#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int left; int right; int top; int bottom; } ;
struct TYPE_12__ {int h; int s; TYPE_1__ oldcross; int /*<<< orphan*/  hdcMem; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_11__ {long x; long y; } ;
struct TYPE_10__ {long bottom; scalar_t__ right; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_4__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgnIndirect (TYPE_2__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetDialogBaseUnits () ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ MAXHORI ; 
 scalar_t__ MAXVERT ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,TYPE_3__*) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CC_PaintCross(CCPRIV *infoPtr)
{
 HWND hwnd = GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_GRAPH);

 if (IsWindowVisible(hwnd))   /* if full size */
 {
   HDC hDC;
   int w = GetDialogBaseUnits() - 1;
   int wc = GetDialogBaseUnits() * 3 / 4;
   RECT rect;
   POINT point, p;
   HPEN hPen;
   int x, y;

   x = infoPtr->h;
   y = infoPtr->s;

   GetClientRect(hwnd, &rect);
   hDC = GetDC(hwnd);
   SelectClipRgn( hDC, CreateRectRgnIndirect(&rect));

   point.x = ((long)rect.right * (long)x) / (long)MAXHORI;
   point.y = rect.bottom - ((long)rect.bottom * (long)y) / (long)MAXVERT;
   if ( infoPtr->oldcross.left != infoPtr->oldcross.right )
     BitBlt(hDC, infoPtr->oldcross.left, infoPtr->oldcross.top,
              infoPtr->oldcross.right - infoPtr->oldcross.left,
              infoPtr->oldcross.bottom - infoPtr->oldcross.top,
              infoPtr->hdcMem, infoPtr->oldcross.left, infoPtr->oldcross.top, SRCCOPY);
   infoPtr->oldcross.left   = point.x - w - 1;
   infoPtr->oldcross.right  = point.x + w + 1;
   infoPtr->oldcross.top    = point.y - w - 1;
   infoPtr->oldcross.bottom = point.y + w + 1;

   hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); /* -black- color */
   hPen = SelectObject(hDC, hPen);
   MoveToEx(hDC, point.x - w, point.y, &p);
   LineTo(hDC, point.x - wc, point.y);
   MoveToEx(hDC, point.x + wc, point.y, &p);
   LineTo(hDC, point.x + w, point.y);
   MoveToEx(hDC, point.x, point.y - w, &p);
   LineTo(hDC, point.x, point.y - wc);
   MoveToEx(hDC, point.x, point.y + wc, &p);
   LineTo(hDC, point.x, point.y + w);
   DeleteObject( SelectObject(hDC, hPen));

   ReleaseDC(hwnd, hDC);
 }
}