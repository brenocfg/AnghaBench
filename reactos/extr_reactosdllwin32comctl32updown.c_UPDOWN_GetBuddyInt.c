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
typedef  scalar_t__ WCHAR ;
struct TYPE_5__ {int Flags; int CurVal; int /*<<< orphan*/  Base; int /*<<< orphan*/  Buddy; } ;
typedef  TYPE_1__ UPDOWN_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FLAG_BUDDYINT ; 
 scalar_t__ GetWindowTextW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETCARETINDEX ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UPDOWN_GetThousandSep () ; 
 int /*<<< orphan*/  UPDOWN_InBounds (TYPE_1__*,int) ; 
 scalar_t__ UPDOWN_IsBuddyListbox (TYPE_1__*) ; 
 int strtolW (scalar_t__*,scalar_t__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL UPDOWN_GetBuddyInt (UPDOWN_INFO *infoPtr)
{
    WCHAR txt[20], sep, *src, *dst;
    int newVal;

    if (!((infoPtr->Flags & FLAG_BUDDYINT) && IsWindow(infoPtr->Buddy)))
        return FALSE;

    /*if the buddy is a list window, we must set curr index */
    if (UPDOWN_IsBuddyListbox(infoPtr)) {
        newVal = SendMessageW(infoPtr->Buddy, LB_GETCARETINDEX, 0, 0);
        if(newVal < 0) return FALSE;
    } else {
        /* we have a regular window, so will get the text */
        /* note that a zero-length string is a legitimate value for 'txt',
         * and ought to result in a successful conversion to '0'. */
        if (GetWindowTextW(infoPtr->Buddy, txt, ARRAY_SIZE(txt)) < 0)
            return FALSE;

        sep = UPDOWN_GetThousandSep();

        /* now get rid of the separators */
        for(src = dst = txt; *src; src++)
            if(*src != sep) *dst++ = *src;
        *dst = 0;

        /* try to convert the number and validate it */
        newVal = strtolW(txt, &src, infoPtr->Base);
        if(*src || !UPDOWN_InBounds (infoPtr, newVal)) return FALSE;
    }

    TRACE("new value(%d) from buddy (old=%d)\n", newVal, infoPtr->CurVal);
    infoPtr->CurVal = newVal;
    return TRUE;
}