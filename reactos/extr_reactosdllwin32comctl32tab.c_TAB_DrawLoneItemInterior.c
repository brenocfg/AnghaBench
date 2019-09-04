#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_6__ {int /*<<< orphan*/  hwnd; int /*<<< orphan*/  hwndUpDown; scalar_t__ needsScrolling; } ;
typedef  TYPE_1__ TAB_INFO ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  ExcludeClipRect (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAB_DrawItemInterior (TYPE_1__ const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
TAB_DrawLoneItemInterior(const TAB_INFO* infoPtr, int iItem)
{
  HDC hdc = GetDC(infoPtr->hwnd);
  RECT r, rC;

  /* Clip UpDown control to not draw over it */
  if (infoPtr->needsScrolling)
  {
    GetWindowRect(infoPtr->hwnd, &rC);
    GetWindowRect(infoPtr->hwndUpDown, &r);
    ExcludeClipRect(hdc, r.left - rC.left, r.top - rC.top, r.right - rC.left, r.bottom - rC.top);
  }
  TAB_DrawItemInterior(infoPtr, hdc, iItem, NULL);
  ReleaseDC(infoPtr->hwnd, hdc);
}