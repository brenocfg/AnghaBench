#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_wday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_7__ {int /*<<< orphan*/  time; } ;
struct TYPE_8__ {TYPE_1__ names; } ;
struct TYPE_10__ {TYPE_2__ str; int /*<<< orphan*/  lcid; } ;
struct TYPE_9__ {scalar_t__ wMilliseconds; int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wDayOfWeek; scalar_t__ wMonth; scalar_t__ wYear; } ;
typedef  TYPE_3__ SYSTEMTIME ;
typedef  TYPE_4__ MSVCRT___lc_time_data ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  FALSE ; 
 size_t GetTimeFormatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * _errno () ; 

__attribute__((used)) static inline BOOL strftime_time(char *str, size_t *pos, size_t max,
        const struct tm *mstm, MSVCRT___lc_time_data *time_data)
{
    SYSTEMTIME st;
    size_t ret;

    st.wYear = mstm->tm_year + 1900;
    st.wMonth = mstm->tm_mon + 1;
    st.wDayOfWeek = mstm->tm_wday;
    st.wDay = mstm->tm_mday;
    st.wHour = mstm->tm_hour;
    st.wMinute = mstm->tm_min;
    st.wSecond = mstm->tm_sec;
    st.wMilliseconds = 0;

    ret = GetTimeFormatA(time_data->lcid, 0, &st, time_data->str.names.time, NULL, 0);
    if(ret && ret<max-*pos)
        ret = GetTimeFormatA(time_data->lcid, 0, &st, time_data->str.names.time,
                str+*pos, max-*pos);
    if(!ret) {
        *str = 0;
        *_errno() = EINVAL;
        return FALSE;
    }else if(ret > max-*pos) {
        *str = 0;
        *_errno() = ERANGE;
        return FALSE;
    }
    *pos += ret-1;
    return TRUE;
}