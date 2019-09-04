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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int dwStyle; int /*<<< orphan*/  flags; int /*<<< orphan*/  uThumbLen; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int TBS_FIXEDLENGTH ; 
 int /*<<< orphan*/  TB_THUMBSIZECHANGED ; 
 int /*<<< orphan*/  TRACKBAR_InvalidateAll (TYPE_1__*) ; 

__attribute__((used)) static inline LRESULT
TRACKBAR_SetThumbLength (TRACKBAR_INFO *infoPtr, UINT iLength)
{
    if (infoPtr->dwStyle & TBS_FIXEDLENGTH) {
        /* We're not supposed to check if it's really changed or not,
           just repaint in any case. */
        infoPtr->uThumbLen = iLength;
	infoPtr->flags |= TB_THUMBSIZECHANGED;
	TRACKBAR_InvalidateAll(infoPtr);
    }

    return 0;
}