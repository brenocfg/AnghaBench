#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x; int y; } ;
struct TYPE_5__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustWindowRectEx (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExStyle ; 
 int /*<<< orphan*/  FALSE ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXSCREEN ; 
 int /*<<< orphan*/  SM_CYSCREEN ; 
 int /*<<< orphan*/  SetRect (TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  Style ; 
 TYPE_2__ ptStart ; 

void ResizeAndCenter(HWND hwnd, int width, int height)
{
   int x, y;
   RECT Rect;

   int screenwidth = GetSystemMetrics(SM_CXSCREEN);
   int screenheight = GetSystemMetrics(SM_CYSCREEN);

   x = (screenwidth - width) / 2;
   y = (screenheight - height) / 2;

   SetRect(&Rect, x, y, x + width, y + height);
   AdjustWindowRectEx(&Rect, Style, FALSE, ExStyle);

   x = Rect.left;
   y = Rect.top;
   width = Rect.right - Rect.left;
   height = Rect.bottom - Rect.top;
   MoveWindow(hwnd, x, y, width, height, FALSE);

   ptStart.x = x;
   ptStart.y = y;
}