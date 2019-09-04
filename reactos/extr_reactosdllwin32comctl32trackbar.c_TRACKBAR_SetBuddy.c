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
struct TYPE_4__ {void* hwndBuddyRB; void* hwndBuddyLA; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  void* HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACKBAR_AlignBuddies (TYPE_1__*) ; 

__attribute__((used)) static HWND
TRACKBAR_SetBuddy (TRACKBAR_INFO *infoPtr, BOOL fLocation, HWND hwndBuddy)
{
    HWND hwndTemp;

    if (fLocation) {
	/* buddy is left or above */
	hwndTemp = infoPtr->hwndBuddyLA;
	infoPtr->hwndBuddyLA = hwndBuddy;
    }
    else {
        /* buddy is right or below */
        hwndTemp = infoPtr->hwndBuddyRB;
        infoPtr->hwndBuddyRB = hwndBuddy;
    }

    TRACKBAR_AlignBuddies (infoPtr);

    return hwndTemp;
}