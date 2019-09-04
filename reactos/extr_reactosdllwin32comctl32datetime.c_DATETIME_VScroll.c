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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_5__ {int select; scalar_t__ pendingUpdown; int /*<<< orphan*/  hwndSelf; int /*<<< orphan*/  haveFocus; } ;
typedef  scalar_t__ SHORT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_IncreaseField (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  DATETIME_SendDateTimeChangeNotify (TYPE_1__*) ; 
 int DTHT_DATEFIELD ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ SB_THUMBPOSITION ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT
DATETIME_VScroll (DATETIME_INFO *infoPtr, WORD wScroll)
{
    int fieldNum = infoPtr->select & DTHT_DATEFIELD;

    if ((SHORT)LOWORD(wScroll) != SB_THUMBPOSITION) return 0;
    if (!(infoPtr->haveFocus)) return 0;
    if ((fieldNum==0) && (infoPtr->select)) return 0;

    if (infoPtr->pendingUpdown >= 0) {
	DATETIME_IncreaseField (infoPtr, fieldNum, 1);
	DATETIME_SendDateTimeChangeNotify (infoPtr);
    }
    else {
	DATETIME_IncreaseField (infoPtr, fieldNum, -1);
	DATETIME_SendDateTimeChangeNotify (infoPtr);
    }

    InvalidateRect(infoPtr->hwndSelf, NULL, TRUE);

    return 0;
}