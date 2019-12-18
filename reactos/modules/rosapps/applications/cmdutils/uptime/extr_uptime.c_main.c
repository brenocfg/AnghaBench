#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int QuadPart; } ;
struct TYPE_6__ {int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int LONGLONG ;
typedef  TYPE_2__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 scalar_t__ QueryPerformanceCounter (TYPE_2__*) ; 
 scalar_t__ QueryPerformanceFrequency (TYPE_2__*) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,int,int,...) ; 

int main(int argc, char* argv[])
{
    SYSTEMTIME SystemTime;
    LARGE_INTEGER liCount, liFreq;

    GetLocalTime(&SystemTime);

    if (QueryPerformanceCounter(&liCount) &&
        QueryPerformanceFrequency(&liFreq))
    {
        LONGLONG TotalSecs = liCount.QuadPart / liFreq.QuadPart;
        LONGLONG Days  =  (TotalSecs / 86400);
        LONGLONG Hours = ((TotalSecs % 86400) / 3600);
        LONGLONG Mins  = ((TotalSecs % 86400) % 3600) / 60;
        LONGLONG Secs  = ((TotalSecs % 86400) % 3600) % 60;

#ifdef LINUX_OUTPUT
        UNREFERENCED_PARAMETER(Secs);
        _tprintf(_T("  %.2u:%.2u  "), SystemTime.wHour, SystemTime.wMinute);
        _tprintf(_T("up %I64u days, %I64u:%I64u\n"), Days, Hours, Mins); /*%.2I64u secs*/
#else
        _tprintf(_T("System Up Time:\t\t%I64u days, %I64u Hours, %I64u Minutes, %.2I64u Seconds\n"),
                 Days, Hours, Mins, Secs);
#endif
        return 0;
    }

    return -1;
}