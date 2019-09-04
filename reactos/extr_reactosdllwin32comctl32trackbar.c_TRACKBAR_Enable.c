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
struct TYPE_3__ {int /*<<< orphan*/  rcThumb; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  dwStyle; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int LRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WS_DISABLED ; 

__attribute__((used)) static LRESULT
TRACKBAR_Enable (TRACKBAR_INFO *infoPtr, BOOL enable)
{
    if (enable)
        infoPtr->dwStyle &= ~WS_DISABLED;
    else
        infoPtr->dwStyle |= WS_DISABLED;

    InvalidateRect(infoPtr->hwndSelf, &infoPtr->rcThumb, TRUE);

    return 1;
}