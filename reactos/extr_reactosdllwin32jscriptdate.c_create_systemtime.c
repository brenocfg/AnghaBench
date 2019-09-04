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
struct TYPE_3__ {int /*<<< orphan*/  wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wDayOfWeek; scalar_t__ wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  date_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hour_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_from_time (int /*<<< orphan*/ ) ; 
 scalar_t__ month_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_from_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  week_day (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  year_from_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SYSTEMTIME create_systemtime(DOUBLE time)
{
    SYSTEMTIME st;

    st.wYear = year_from_time(time);
    st.wMonth = month_from_time(time) + 1;
    st.wDayOfWeek = week_day(time);
    st.wDay = date_from_time(time);
    st.wHour = hour_from_time(time);
    st.wMinute = min_from_time(time);
    st.wSecond = sec_from_time(time);
    st.wMilliseconds = ms_from_time(time);

    return st;
}