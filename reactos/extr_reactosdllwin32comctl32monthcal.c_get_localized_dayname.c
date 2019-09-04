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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int dwStyle; } ;
typedef  TYPE_1__ MONTHCAL_INFO ;
typedef  scalar_t__ LCTYPE ;

/* Variables and functions */
 int GetLocaleInfoW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ LOCALE_SABBREVDAYNAME1 ; 
 scalar_t__ LOCALE_SSHORTESTDAYNAME1 ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int MCS_SHORTDAYSOFWEEK ; 

__attribute__((used)) static int get_localized_dayname(const MONTHCAL_INFO *infoPtr, unsigned int day, WCHAR *buff, unsigned int count)
{
  LCTYPE lctype;

  if (infoPtr->dwStyle & MCS_SHORTDAYSOFWEEK)
      lctype = LOCALE_SSHORTESTDAYNAME1 + day;
  else
      lctype = LOCALE_SABBREVDAYNAME1 + day;

  return GetLocaleInfoW(LOCALE_USER_DEFAULT, lctype, buff, count);
}