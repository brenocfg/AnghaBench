#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
struct TYPE_8__ {int bottom; int top; int left; int right; } ;
struct TYPE_7__ {int top; int bottom; int left; int right; } ;
struct TYPE_9__ {int lRangeMax; int lRangeMin; TYPE_2__ rcThumb; TYPE_1__ rcChannel; } ;
typedef  TYPE_3__ TRACKBAR_INFO ;
typedef  TYPE_4__ RECT ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_4__*,int,int,int,int) ; 
 int TBS_LEFT ; 
 int TBS_TOP ; 
 int TBS_VERT ; 
 int TIC_EDGE ; 
 int TIC_SELECTIONMARK ; 
 int TIC_SELECTIONMARKMIN ; 

__attribute__((used)) static void
TRACKBAR_DrawOneTic (const TRACKBAR_INFO *infoPtr, HDC hdc, LONG ticPos, int flags)
{
    int x, y, ox, oy, range, side, indent = 0, len = 3;
    int offsetthumb;
    RECT rcTics;

    if (flags & TBS_VERT) {
        offsetthumb = (infoPtr->rcThumb.bottom - infoPtr->rcThumb.top)/2;
        SetRect(&rcTics, infoPtr->rcThumb.left - 2, infoPtr->rcChannel.top + offsetthumb,
                infoPtr->rcThumb.right + 2, infoPtr->rcChannel.bottom - offsetthumb - 1);
    } else {
        offsetthumb = (infoPtr->rcThumb.right - infoPtr->rcThumb.left)/2;
        SetRect(&rcTics, infoPtr->rcChannel.left + offsetthumb, infoPtr->rcThumb.top - 2,
                infoPtr->rcChannel.right - offsetthumb - 1, infoPtr->rcThumb.bottom + 2);
    }

    if (flags & (TBS_TOP | TBS_LEFT)) {
	x = rcTics.left;
	y = rcTics.top;
	side = -1;
    } else {
  	x = rcTics.right;
  	y = rcTics.bottom;
	side = 1;
    }

    range = infoPtr->lRangeMax - infoPtr->lRangeMin;
    if (range <= 0)
      range = 1; /* to avoid division by zero */

    if (flags & TIC_SELECTIONMARK) {
  	indent = (flags & TIC_SELECTIONMARKMIN) ? -1 : 1;
    } else if (flags & TIC_EDGE) {
	len++;
    }

    if (flags & TBS_VERT) {
	int height = rcTics.bottom - rcTics.top;
	y = rcTics.top + (height*(ticPos - infoPtr->lRangeMin))/range;
    } else {
        int width = rcTics.right - rcTics.left;
        x = rcTics.left + (width*(ticPos - infoPtr->lRangeMin))/range;
    }

    ox = x;
    oy = y;
    MoveToEx(hdc, x, y, 0);
    if (flags & TBS_VERT) x += len * side;
    else y += len * side;
    LineTo(hdc, x, y);
	    
    if (flags & TIC_SELECTIONMARK) {
	if (flags & TBS_VERT) {
	    x -= side;
	} else {
	    y -= side;
	}
	MoveToEx(hdc, x, y, 0);
	if (flags & TBS_VERT) {
	    y += 2 * indent;
	} else {
	    x += 2 * indent;
	}
	
	LineTo(hdc, x, y);
	LineTo(hdc, ox, oy);
    }
}