#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int firstDay; TYPE_1__* calendars; } ;
struct TYPE_9__ {int wDay; int /*<<< orphan*/  wYear; int /*<<< orphan*/  wMonth; } ;
struct TYPE_8__ {TYPE_2__ month; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ MONTHCAL_INFO ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MONTHCAL_CalculateDayOfWeek (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MONTHCAL_GetPrevMonth (TYPE_2__*) ; 
 scalar_t__ MONTHCAL_MonthLength (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void MONTHCAL_GetMinDate(const MONTHCAL_INFO *infoPtr, SYSTEMTIME *date)
{
  /* zero indexed calendar has the earliest date */
  SYSTEMTIME st_first = infoPtr->calendars[0].month;
  INT firstDay;

  st_first.wDay = 1;
  firstDay = MONTHCAL_CalculateDayOfWeek(&st_first, FALSE);

  *date = infoPtr->calendars[0].month;
  MONTHCAL_GetPrevMonth(date);

  date->wDay = MONTHCAL_MonthLength(date->wMonth, date->wYear) +
               (infoPtr->firstDay - firstDay) % 7 + 1;

  if(date->wDay > MONTHCAL_MonthLength(date->wMonth, date->wYear))
    date->wDay -= 7;

  /* fix day of week */
  MONTHCAL_CalculateDayOfWeek(date, TRUE);
}