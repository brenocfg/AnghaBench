#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int left; int right; int top; int bottom; } ;
struct TYPE_7__ {int bottom; int top; int right; int left; } ;
struct TYPE_8__ {int lRangeMax; int lRangeMin; int uThumbLen; int dwStyle; TYPE_1__ rcChannel; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_2__ TRACKBAR_INFO ;
typedef  TYPE_3__ RECT ;
typedef  int LONG ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int TBS_BOTH ; 
 int TBS_LEFT ; 
 int TBS_NOTICKS ; 
 int TBS_TOP ; 
 int TBS_VERT ; 

__attribute__((used)) static void
TRACKBAR_CalcThumb (const TRACKBAR_INFO *infoPtr, LONG lPos, RECT *thumb)
{
    int range, width, height, thumbwidth;
    RECT lpRect;

    range = infoPtr->lRangeMax - infoPtr->lRangeMin;
    thumbwidth = (infoPtr->uThumbLen / 2) | 1;

    if (!range) range = 1;

    GetClientRect(infoPtr->hwndSelf, &lpRect);
    if (infoPtr->dwStyle & TBS_VERT)
    {
    	height = infoPtr->rcChannel.bottom - infoPtr->rcChannel.top - thumbwidth;

        if ((infoPtr->dwStyle & (TBS_BOTH | TBS_LEFT)) && !(infoPtr->dwStyle & TBS_NOTICKS))
            thumb->left = 10;
        else
            thumb->left = 2;
        thumb->right = thumb->left + infoPtr->uThumbLen;
        thumb->top = infoPtr->rcChannel.top +
                     (height*(lPos - infoPtr->lRangeMin))/range;
        thumb->bottom = thumb->top + thumbwidth;
    }
    else
    {
    	width = infoPtr->rcChannel.right - infoPtr->rcChannel.left - thumbwidth;

        thumb->left = infoPtr->rcChannel.left +
                      (width*(lPos - infoPtr->lRangeMin))/range;
        thumb->right = thumb->left + thumbwidth;
        if ((infoPtr->dwStyle & (TBS_BOTH | TBS_TOP)) && !(infoPtr->dwStyle & TBS_NOTICKS))
            thumb->top = 10;
        else
            thumb->top = 2;
        thumb->bottom = thumb->top + infoPtr->uThumbLen;
    }
}