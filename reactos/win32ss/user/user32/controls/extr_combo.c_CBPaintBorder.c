#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  textRect; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ HEADCOMBO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BF_RECT ; 
 scalar_t__ CBS_SIMPLE ; 
 scalar_t__ CB_GETTYPE (TYPE_1__ const*) ; 
 int /*<<< orphan*/  COMBO_XBORDERSIZE () ; 
 int /*<<< orphan*/  COMBO_YBORDERSIZE () ; 
 int /*<<< orphan*/  CopyRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_SUNKEN ; 
 int /*<<< orphan*/  EDIT_CONTROL_PADDING () ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InflateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CBPaintBorder(
  HWND            hwnd,
  const HEADCOMBO *lphc,
  HDC             hdc)
{
  RECT clientRect;

  if (CB_GETTYPE(lphc) != CBS_SIMPLE)
  {
    GetClientRect(hwnd, &clientRect);
  }
  else
  {
    CopyRect(&clientRect, &lphc->textRect);

    InflateRect(&clientRect, EDIT_CONTROL_PADDING(), EDIT_CONTROL_PADDING());
    InflateRect(&clientRect, COMBO_XBORDERSIZE(), COMBO_YBORDERSIZE());
  }

  DrawEdge(hdc, &clientRect, EDGE_SUNKEN, BF_RECT);
}