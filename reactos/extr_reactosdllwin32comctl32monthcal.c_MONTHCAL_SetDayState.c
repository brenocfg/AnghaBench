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
struct TYPE_5__ {int dwStyle; int /*<<< orphan*/  monthdayState; } ;
typedef  int /*<<< orphan*/  MONTHDAYSTATE ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int LRESULT ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  GMR_DAYSTATE ; 
 int MCS_DAYSTATE ; 
 int MONTHCAL_GetMonthRange (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static LRESULT
MONTHCAL_SetDayState(const MONTHCAL_INFO *infoPtr, INT months, MONTHDAYSTATE *states)
{
  TRACE("%p %d %p\n", infoPtr, months, states);

  if (!(infoPtr->dwStyle & MCS_DAYSTATE)) return 0;
  if (months != MONTHCAL_GetMonthRange(infoPtr, GMR_DAYSTATE, 0)) return 0;

  memcpy(infoPtr->monthdayState, states, months*sizeof(MONTHDAYSTATE));

  return 1;
}