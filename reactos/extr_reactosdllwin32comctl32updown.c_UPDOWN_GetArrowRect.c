#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int dwStyle; int /*<<< orphan*/  Buddy; int /*<<< orphan*/  Self; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
struct TYPE_9__ {int left; int right; int bottom; int top; } ;
typedef  TYPE_2__ RECT ;
typedef  scalar_t__ HTHEME ;

/* Variables and functions */
 int DEFAULT_BUDDYBORDER ; 
 int DEFAULT_BUDDYBORDER_THEMED ; 
 int DEFAULT_BUDDYSPACER ; 
 int DEFAULT_BUDDYSPACER_THEMED ; 
 int FLAG_DECR ; 
 int FLAG_INCR ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (TYPE_2__*,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 int UDS_ALIGNLEFT ; 
 int UDS_ALIGNRIGHT ; 
 int UDS_HORZ ; 
 scalar_t__ UPDOWN_HasBuddyBorder (TYPE_1__ const*) ; 

__attribute__((used)) static void UPDOWN_GetArrowRect (const UPDOWN_INFO* infoPtr, RECT *rect, int arrow)
{
    HTHEME theme = GetWindowTheme (infoPtr->Self);
    const int border = theme ? DEFAULT_BUDDYBORDER_THEMED : DEFAULT_BUDDYBORDER;
    const int spacer = theme ? DEFAULT_BUDDYSPACER_THEMED : DEFAULT_BUDDYSPACER;
    GetClientRect (infoPtr->Self, rect);

    /*
     * Make sure we calculate the rectangle to fit even if we draw the
     * border.
     */
    if (UPDOWN_HasBuddyBorder(infoPtr)) {
        if (infoPtr->dwStyle & UDS_ALIGNLEFT)
            rect->left += border;
        else
            rect->right -= border;

        InflateRect(rect, 0, -border);
    }

    /* now figure out if we need a space away from the buddy */
    if (IsWindow(infoPtr->Buddy) ) {
	if (infoPtr->dwStyle & UDS_ALIGNLEFT) rect->right -= spacer;
	else if (infoPtr->dwStyle & UDS_ALIGNRIGHT) rect->left += spacer;
    }

    /*
     * We're calculating the midpoint to figure-out where the
     * separation between the buttons will lay. We make sure that we
     * round the uneven numbers by adding 1.
     */
    if (infoPtr->dwStyle & UDS_HORZ) {
        int len = rect->right - rect->left + 1; /* compute the width */
        if (arrow & FLAG_INCR)
            rect->left = rect->left + len/2;
        if (arrow & FLAG_DECR)
            rect->right =  rect->left + len/2 - (theme ? 0 : 1);
    } else {
        int len = rect->bottom - rect->top + 1; /* compute the height */
        if (arrow & FLAG_INCR)
            rect->bottom =  rect->top + len/2 - (theme ? 0 : 1);
        if (arrow & FLAG_DECR)
            rect->top =  rect->top + len/2;
    }
}