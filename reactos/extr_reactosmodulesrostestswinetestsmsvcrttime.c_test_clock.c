#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dwLowDateTime; scalar_t__ dwHighDateTime; } ;
typedef  int LONGLONG ;
typedef  TYPE_1__ FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessTimes (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetSystemTimeAsFileTime (TYPE_1__*) ; 
 int const abs (int) ; 
 int clock () ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_clock(void)
{
    static const int THRESH = 100;
    FILETIME start, cur;
    int c, expect;
    BOOL ret;

    ret = GetProcessTimes(GetCurrentProcess(), &start, &cur, &cur, &cur);
    ok(ret, "GetProcessTimes failed with error: %d\n", GetLastError());
    GetSystemTimeAsFileTime(&cur);
    expect = (((LONGLONG)cur.dwHighDateTime<<32)+cur.dwLowDateTime -
            ((LONGLONG)start.dwHighDateTime<<32)-start.dwLowDateTime) / 10000;

    c = clock();
    ok(abs(c-expect) < THRESH, "clock() = %d, expected %d\n", c, expect);
}