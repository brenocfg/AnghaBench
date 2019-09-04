#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_16__ {int dwStyle; size_t* monthdayState; TYPE_1__* calendars; int /*<<< orphan*/ * colors; } ;
struct TYPE_15__ {int wDay; int /*<<< orphan*/  wYear; scalar_t__ wMonth; } ;
struct TYPE_14__ {TYPE_2__ month; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GMR_DAYSTATE ; 
 size_t MCSC_TRAILINGTEXT ; 
 int MCS_NOTRAILINGDATES ; 
 int /*<<< orphan*/  MONTHCAL_DrawDay (TYPE_3__ const*,int /*<<< orphan*/ ,TYPE_2__*,size_t,int /*<<< orphan*/  const*) ; 
 int MONTHCAL_GetCalCount (TYPE_3__ const*) ; 
 int /*<<< orphan*/  MONTHCAL_GetMaxDate (TYPE_3__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  MONTHCAL_GetMinDate (TYPE_3__ const*,TYPE_2__*) ; 
 int MONTHCAL_GetMonthRange (TYPE_3__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_GetNextMonth (TYPE_2__*) ; 
 int MONTHCAL_MonthLength (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTextColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MONTHCAL_PaintLeadTrailMonths(const MONTHCAL_INFO *infoPtr, HDC hdc, const PAINTSTRUCT *ps)
{
  INT mask, index;
  UINT length;
  SYSTEMTIME st_max, st;

  if (infoPtr->dwStyle & MCS_NOTRAILINGDATES) return;

  SetTextColor(hdc, infoPtr->colors[MCSC_TRAILINGTEXT]);

  /* draw prev month */
  MONTHCAL_GetMinDate(infoPtr, &st);
  mask = 1 << (st.wDay-1);
  /* December and January both 31 days long, so no worries if wrapped */
  length = MONTHCAL_MonthLength(infoPtr->calendars[0].month.wMonth - 1,
                                infoPtr->calendars[0].month.wYear);
  index = 0;
  while(st.wDay <= length)
  {
      MONTHCAL_DrawDay(infoPtr, hdc, &st, infoPtr->monthdayState[index] & mask, ps);
      mask <<= 1;
      st.wDay++;
  }

  /* draw next month */
  st = infoPtr->calendars[MONTHCAL_GetCalCount(infoPtr)-1].month;
  st.wDay = 1;
  MONTHCAL_GetNextMonth(&st);
  MONTHCAL_GetMaxDate(infoPtr, &st_max);
  mask = 1;
  index = MONTHCAL_GetMonthRange(infoPtr, GMR_DAYSTATE, 0)-1;
  while(st.wDay <= st_max.wDay)
  {
      MONTHCAL_DrawDay(infoPtr, hdc, &st, infoPtr->monthdayState[index] & mask, ps);
      mask <<= 1;
      st.wDay++;
  }
}