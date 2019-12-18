#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  void* UINT ;
struct TYPE_6__ {void* dwLowDateTime; void* dwHighDateTime; } ;
struct TYPE_5__ {int wYear; int wMonth; int wDay; scalar_t__ wHour; scalar_t__ wMinute; int wSecond; scalar_t__ wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FileTimeToSystemTime (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ TICKSPERSEC ; 
 int TICKS_1601_TO_1970 ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_FileTimeToSystemTime(void)
{
    FILETIME ft;
    SYSTEMTIME st;
    ULONGLONG time = (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1970;
    BOOL ret;

    ft.dwHighDateTime = 0;
    ft.dwLowDateTime  = 0;
    ret = FileTimeToSystemTime(&ft, &st);
    ok( ret,
       "FileTimeToSystemTime() failed with Error %d\n",GetLastError());
    ok(((st.wYear == 1601) && (st.wMonth  == 1) && (st.wDay    == 1) &&
	(st.wHour ==    0) && (st.wMinute == 0) && (st.wSecond == 0) &&
	(st.wMilliseconds == 0)),
	"Got Year %4d Month %2d Day %2d\n",  st.wYear, st.wMonth, st.wDay);

    ft.dwHighDateTime = (UINT)(time >> 32);
    ft.dwLowDateTime  = (UINT)time;
    ret = FileTimeToSystemTime(&ft, &st);
    ok( ret,
       "FileTimeToSystemTime() failed with Error %d\n",GetLastError());
    ok(((st.wYear == 1970) && (st.wMonth == 1) && (st.wDay == 1) &&
	(st.wHour ==    0) && (st.wMinute == 0) && (st.wSecond == 1) &&
	(st.wMilliseconds == 0)),
       "Got Year %4d Month %2d Day %2d Hour %2d Min %2d Sec %2d mSec %3d\n",
       st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
       st.wMilliseconds);
}