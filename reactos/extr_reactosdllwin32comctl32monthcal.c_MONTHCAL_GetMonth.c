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
struct TYPE_4__ {int wMonth; int wDay; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  MONTHCAL_CalculateDayOfWeek (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MONTHCAL_MonthLength (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline void MONTHCAL_GetMonth(SYSTEMTIME *date, INT months)
{
  INT length, m = date->wMonth + months;

  date->wYear += m > 0 ? (m - 1) / 12 : m / 12 - 1;
  date->wMonth = m > 0 ? (m - 1) % 12 + 1 : 12 + m % 12;
  /* fix moving from last day in a month */
  length = MONTHCAL_MonthLength(date->wMonth, date->wYear);
  if(date->wDay > length) date->wDay = length;
  MONTHCAL_CalculateDayOfWeek(date, TRUE);
}