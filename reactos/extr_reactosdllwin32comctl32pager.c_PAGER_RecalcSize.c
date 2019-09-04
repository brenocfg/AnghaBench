#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nPos; scalar_t__ hwndChild; int /*<<< orphan*/  hwndSelf; } ;
typedef  TYPE_1__ PAGER_INFO ;
typedef  int LRESULT ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PAGER_GetScrollRange (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGER_PositionChildWnd (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGER_SetPos (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
PAGER_RecalcSize(PAGER_INFO *infoPtr)
{
    TRACE("[%p]\n", infoPtr->hwndSelf);

    if (infoPtr->hwndChild)
    {
        INT scrollRange = PAGER_GetScrollRange(infoPtr, TRUE);

        if (scrollRange <= 0)
        {
            infoPtr->nPos = -1;
            PAGER_SetPos(infoPtr, 0, FALSE, TRUE);
        }
        else
            PAGER_PositionChildWnd(infoPtr);
    }

    return 1;
}