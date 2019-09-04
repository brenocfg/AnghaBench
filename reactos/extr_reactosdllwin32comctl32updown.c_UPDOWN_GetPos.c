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
struct TYPE_5__ {int CurVal; int MinVal; int MaxVal; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int UPDOWN_GetBuddyInt (TYPE_1__*) ; 
 int /*<<< orphan*/  UPDOWN_InBounds (TYPE_1__*,int) ; 

__attribute__((used)) static int UPDOWN_GetPos(UPDOWN_INFO *infoPtr, BOOL *err)
{
    BOOL succ = UPDOWN_GetBuddyInt(infoPtr);
    int val = infoPtr->CurVal;

    if(!UPDOWN_InBounds(infoPtr, val)) {
        if((infoPtr->MinVal < infoPtr->MaxVal && val < infoPtr->MinVal)
                || (infoPtr->MinVal > infoPtr->MaxVal && val > infoPtr->MinVal))
            val = infoPtr->MinVal;
        else
            val = infoPtr->MaxVal;

        succ = FALSE;
    }

    if(err) *err = !succ;
    return val;
}