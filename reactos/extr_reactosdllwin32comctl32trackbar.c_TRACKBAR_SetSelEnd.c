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
struct TYPE_4__ {int dwStyle; scalar_t__ lSelMax; scalar_t__ lRangeMax; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int TBS_ENABLESELRANGE ; 
 int /*<<< orphan*/  TB_SELECTIONCHANGED ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetSelEnd (TRACKBAR_INFO *infoPtr, BOOL fRedraw, LONG lEnd)
{
    if (!(infoPtr->dwStyle & TBS_ENABLESELRANGE)){
        infoPtr->lSelMax = 0;
	return 0;
    }

    infoPtr->lSelMax = lEnd;
    infoPtr->flags |= TB_SELECTIONCHANGED;

    if (infoPtr->lSelMax > infoPtr->lRangeMax)
        infoPtr->lSelMax = infoPtr->lRangeMax;

    if (fRedraw) TRACKBAR_InvalidateAll(infoPtr);

    return 0;
}