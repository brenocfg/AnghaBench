#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int top; int bottom; int left; int right; } ;
struct TYPE_9__ {int bottom; int top; int left; int right; } ;
struct TYPE_8__ {int bottom; int top; int right; int left; } ;
struct TYPE_10__ {int lRangeMax; int lRangeMin; int dwStyle; int lSelMin; int lSelMax; TYPE_2__ rcChannel; TYPE_1__ rcThumb; TYPE_4__ rcSelection; } ;
typedef  TYPE_3__ TRACKBAR_INFO ;
typedef  TYPE_4__ RECT ;

/* Variables and functions */
 int /*<<< orphan*/  SetRectEmpty (TYPE_4__*) ; 
 int TBS_VERT ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_4__*) ; 

__attribute__((used)) static void
TRACKBAR_CalcSelection (TRACKBAR_INFO *infoPtr)
{
    RECT *selection = &infoPtr->rcSelection;
    int range = infoPtr->lRangeMax - infoPtr->lRangeMin;
    int offsetthumb, height, width;

    if (range <= 0) {
        SetRectEmpty (selection);
    } else {
        if (infoPtr->dwStyle & TBS_VERT) {
            offsetthumb = (infoPtr->rcThumb.bottom - infoPtr->rcThumb.top)/2;
            height = infoPtr->rcChannel.bottom - infoPtr->rcChannel.top - offsetthumb*2;
            selection->top    = infoPtr->rcChannel.top + offsetthumb +
                (height*infoPtr->lSelMin)/range;
            selection->bottom = infoPtr->rcChannel.top + offsetthumb +
                (height*infoPtr->lSelMax)/range;
            selection->left   = infoPtr->rcChannel.left + 3;
            selection->right  = infoPtr->rcChannel.right - 3;
        } else {
            offsetthumb = (infoPtr->rcThumb.right - infoPtr->rcThumb.left)/2;
            width = infoPtr->rcChannel.right - infoPtr->rcChannel.left - offsetthumb*2;
            selection->left   = infoPtr->rcChannel.left + offsetthumb +
                (width*infoPtr->lSelMin)/range;
            selection->right  = infoPtr->rcChannel.left + offsetthumb +
                (width*infoPtr->lSelMax)/range;
            selection->top    = infoPtr->rcChannel.top + 3;
            selection->bottom = infoPtr->rcChannel.bottom - 3;
        }
    }

    TRACE("selection[%s]\n", wine_dbgstr_rect(selection));
}