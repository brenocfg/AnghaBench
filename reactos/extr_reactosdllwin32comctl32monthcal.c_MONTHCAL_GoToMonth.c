#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum nav_direction { ____Placeholder_nav_direction } nav_direction ;
struct TYPE_10__ {int delta; int dwStyle; TYPE_1__* calendars; } ;
struct TYPE_9__ {int /*<<< orphan*/  month; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int INT ;
typedef  int BOOL ;

/* Variables and functions */
 int DIRECTION_BACKWARD ; 
 int /*<<< orphan*/  FALSE ; 
 int MCS_NOSELCHANGEONNAV ; 
 int MONTHCAL_GetCalCount (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetMonth (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MONTHCAL_IsDateInValidRange (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_NotifyDayState (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_NotifySelectionChange (TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_Scroll (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 

__attribute__((used)) static void MONTHCAL_GoToMonth(MONTHCAL_INFO *infoPtr, enum nav_direction direction)
{
  INT delta = infoPtr->delta ? infoPtr->delta : MONTHCAL_GetCalCount(infoPtr);
  BOOL keep_selection;
  SYSTEMTIME st;

  TRACE("%s\n", direction == DIRECTION_BACKWARD ? "back" : "fwd");

  /* check if change allowed by range set */
  if(direction == DIRECTION_BACKWARD)
  {
    st = infoPtr->calendars[0].month;
    MONTHCAL_GetMonth(&st, -delta);
  }
  else
  {
    st = infoPtr->calendars[MONTHCAL_GetCalCount(infoPtr)-1].month;
    MONTHCAL_GetMonth(&st, delta);
  }

  if(!MONTHCAL_IsDateInValidRange(infoPtr, &st, FALSE)) return;

  keep_selection = infoPtr->dwStyle & MCS_NOSELCHANGEONNAV;
  MONTHCAL_Scroll(infoPtr, direction == DIRECTION_BACKWARD ? -delta : delta, keep_selection);
  MONTHCAL_NotifyDayState(infoPtr);
  if (!keep_selection)
    MONTHCAL_NotifySelectionChange(infoPtr);
}