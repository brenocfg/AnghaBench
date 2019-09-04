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
typedef  int /*<<< orphan*/  time_t ;
struct tm {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_mday; scalar_t__ tm_wday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
typedef  void* WORD ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ wMilliseconds; void* wSecond; void* wMinute; void* wHour; void* wDay; void* wDayOfWeek; void* wMonth; void* wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__ LPWSTR ;

/* Variables and functions */
 scalar_t__ BUFFER_SIZE ; 
 unsigned int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 scalar_t__ swprintf (scalar_t__,char*) ; 

__attribute__((used)) static
VOID
FormatDateTime(time_t Time, LPWSTR lpBuf)
{
    unsigned i;
    SYSTEMTIME SysTime;
    const struct tm *lpTm;

    lpTm = localtime(&Time);
    SysTime.wYear = (WORD)(1900 + lpTm->tm_year);
    SysTime.wMonth = (WORD)(1 + lpTm->tm_mon);
    SysTime.wDayOfWeek = (WORD)lpTm->tm_wday;
    SysTime.wDay = (WORD)lpTm->tm_mday;
    SysTime.wHour = (WORD)lpTm->tm_hour;
    SysTime.wMinute = (WORD)lpTm->tm_min;
    SysTime.wSecond = (WORD)lpTm->tm_sec;
    SysTime.wMilliseconds = 0;

    /* Copy date first */
    i = GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &SysTime, NULL, lpBuf, BUFFER_SIZE - 2);
    if (i)
        --i; /* don't count NULL character */

    /* Copy time now */
    i += swprintf(lpBuf + i, L", ");

    GetTimeFormatW(LOCALE_SYSTEM_DEFAULT, 0, &SysTime, NULL, lpBuf + i, BUFFER_SIZE - i);
}