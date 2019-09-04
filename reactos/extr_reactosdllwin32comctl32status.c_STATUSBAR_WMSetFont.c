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
struct TYPE_4__ {int /*<<< orphan*/  Self; int /*<<< orphan*/  height; int /*<<< orphan*/  hFont; } ;
typedef  TYPE_1__ STATUS_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUSBAR_ComputeHeight (TYPE_1__*) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SIZE ; 

__attribute__((used)) static LRESULT
STATUSBAR_WMSetFont (STATUS_INFO *infoPtr, HFONT font, BOOL redraw)
{
    infoPtr->hFont = font;
    TRACE("%p\n", infoPtr->hFont);

    infoPtr->height = STATUSBAR_ComputeHeight(infoPtr);
    SendMessageW(infoPtr->Self, WM_SIZE, 0, 0);  /* update size */
    if (redraw)
        InvalidateRect(infoPtr->Self, NULL, FALSE);

    return 0;
}