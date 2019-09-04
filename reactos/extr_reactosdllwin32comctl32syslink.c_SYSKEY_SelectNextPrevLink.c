#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ HasFocus; } ;
typedef  TYPE_1__ SYSLINK_INFO ;
typedef  int /*<<< orphan*/ * PDOC_ITEM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * SYSLINK_GetFocusLink (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/ * SYSLINK_GetNextLink (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SYSLINK_GetPrevLink (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSLINK_RepaintLink (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SYSLINK_SetFocusLink (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static BOOL SYSKEY_SelectNextPrevLink (const SYSLINK_INFO *infoPtr, BOOL Prev)
{
    if(infoPtr->HasFocus)
    {
        PDOC_ITEM Focus;
        int id;

        Focus = SYSLINK_GetFocusLink(infoPtr, &id);
        if(Focus != NULL)
        {
            PDOC_ITEM NewFocus, OldFocus;

            if(Prev)
                NewFocus = SYSLINK_GetPrevLink(infoPtr, Focus);
            else
                NewFocus = SYSLINK_GetNextLink(infoPtr, Focus);

            if(NewFocus != NULL)
            {
                OldFocus = SYSLINK_SetFocusLink(infoPtr, NewFocus);

                if(OldFocus && OldFocus != NewFocus)
                {
                    SYSLINK_RepaintLink(infoPtr, OldFocus);
                }
                SYSLINK_RepaintLink(infoPtr, NewFocus);
                return TRUE;
            }
        }
    }
    return FALSE;
}