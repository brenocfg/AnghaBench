#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ lRangeMax; int lRangeMin; scalar_t__ lPos; int lPageSize; int dwStyle; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  int BOOL ;

/* Variables and functions */
 int TBS_AUTOTICKS ; 
 int /*<<< orphan*/  TB_THUMBPOSCHANGED ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 
 int /*<<< orphan*/  TRACKBAR_RecalculateTics (TYPE_1__*) ; 
 scalar_t__ max (scalar_t__,int) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetRangeMax (TRACKBAR_INFO *infoPtr, BOOL redraw, LONG lMax)
{
    BOOL changed = infoPtr->lRangeMax != lMax;
    LONG rightmost = max(lMax, infoPtr->lRangeMin);

    infoPtr->lRangeMax = lMax;
    if (infoPtr->lPos > rightmost) {
        infoPtr->lPos = rightmost;
        infoPtr->flags |= TB_THUMBPOSCHANGED;
    }

    infoPtr->lPageSize = (infoPtr->lRangeMax - infoPtr->lRangeMin) / 5;
    if (infoPtr->lPageSize == 0) infoPtr->lPageSize = 1;

    if (changed && (infoPtr->dwStyle & TBS_AUTOTICKS))
        TRACKBAR_RecalculateTics (infoPtr);

    if (redraw) TRACKBAR_InvalidateAll(infoPtr);

    return 0;
}