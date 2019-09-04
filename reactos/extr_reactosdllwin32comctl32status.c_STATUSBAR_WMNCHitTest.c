#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* y; void* x; } ;
struct TYPE_10__ {int top; scalar_t__ right; scalar_t__ left; } ;
struct TYPE_9__ {int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  void* INT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int GetWindowLongW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTBOTTOMLEFT ; 
 int /*<<< orphan*/  HTBOTTOMRIGHT ; 
 int /*<<< orphan*/  HTERROR ; 
 scalar_t__ PtInRect (TYPE_2__*,TYPE_3__) ; 
 int SBARS_SIZEGRIP ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int WS_EX_LAYOUTRTL ; 

__attribute__((used)) static BOOL
STATUSBAR_WMNCHitTest (const STATUS_INFO *infoPtr, INT x, INT y)
{
    if (GetWindowLongW (infoPtr->Self, GWL_STYLE) & SBARS_SIZEGRIP) {
	RECT  rect;
	POINT pt;

	GetClientRect (infoPtr->Self, &rect);

	pt.x = x;
	pt.y = y;
	ScreenToClient (infoPtr->Self, &pt);

	rect.left = rect.right - 13;
	rect.top += 2;

	if (PtInRect (&rect, pt))
        {
            if (GetWindowLongW( infoPtr->Self, GWL_EXSTYLE ) & WS_EX_LAYOUTRTL) return HTBOTTOMLEFT;
	    else return HTBOTTOMRIGHT;
        }
    }

    return HTERROR;
}