#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GUI_FONT ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SetTextAlign (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TA_LEFT ; 
 int TA_TOP ; 
 int /*<<< orphan*/  TextOutW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ME_DebugWrite(HDC hDC, const POINT *pt, LPCWSTR szText) {
  int align = SetTextAlign(hDC, TA_LEFT|TA_TOP);
  HGDIOBJ hFont = SelectObject(hDC, GetStockObject(DEFAULT_GUI_FONT));
  COLORREF color = SetTextColor(hDC, RGB(128,128,128));
  TextOutW(hDC, pt->x, pt->y, szText, lstrlenW(szText));
  SelectObject(hDC, hFont);
  SetTextAlign(hDC, align);
  SetTextColor(hDC, color);
}