#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int firstDay; int /*<<< orphan*/  firstDaySet; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  MAKELONG (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LRESULT
MONTHCAL_GetFirstDayOfWeek(const MONTHCAL_INFO *infoPtr)
{
  int day;

  /* convert from SYSTEMTIME to locale format */
  day = (infoPtr->firstDay >= 0) ? (infoPtr->firstDay+6)%7 : infoPtr->firstDay;

  return MAKELONG(day, infoPtr->firstDaySet);
}