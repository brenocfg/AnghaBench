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
typedef  int /*<<< orphan*/  st ;
struct TYPE_4__ {int wYear; int wMonth; int wDay; int wDayOfWeek; int wHour; int wMinute; int wSecond; int wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreateWindowA (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int GDTR_MAX ; 
 int GDTR_MIN ; 
 int GMR_VISIBLE ; 
 int /*<<< orphan*/  GetSystemTime (TYPE_1__*) ; 
 int /*<<< orphan*/  MCM_GETMONTHRANGE ; 
 int /*<<< orphan*/  MCM_GETRANGE ; 
 int /*<<< orphan*/  MCM_GETTODAY ; 
 int /*<<< orphan*/  MCM_SETRANGE ; 
 int /*<<< orphan*/  MONTHCAL_CLASSA ; 
 int SendMessageA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int WS_POPUP ; 
 int WS_VISIBLE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_monthcal(void)
{
    HWND hwnd;
    SYSTEMTIME st[2], st1[2], today;
    int res, month_range;
    DWORD limits;
    BOOL r;

    hwnd = CreateWindowA(MONTHCAL_CLASSA, "MonthCal", WS_POPUP | WS_VISIBLE, CW_USEDEFAULT,
                         0, 300, 300, 0, 0, NULL, NULL);
    ok(hwnd != NULL, "Failed to create MonthCal\n");

    /* test range just after creation */
    memset(&st, 0xcc, sizeof(st));
    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st);
    ok(limits == 0 ||
       broken(limits == GDTR_MIN), /* comctl32 <= 4.70 */
       "No limits should be set (%d)\n", limits);
    if (limits == GDTR_MIN)
    {
        win_skip("comctl32 <= 4.70 is broken\n");
        DestroyWindow(hwnd);
        return;
    }

    ok(0 == st[0].wYear ||
       broken(1752 == st[0].wYear), /* comctl32 <= 4.72 */
       "Expected 0, got %d\n", st[0].wYear);
    ok(0 == st[0].wMonth ||
       broken(9 == st[0].wMonth), /* comctl32 <= 4.72 */
       "Expected 0, got %d\n", st[0].wMonth);
    ok(0 == st[0].wDay ||
       broken(14 == st[0].wDay), /* comctl32 <= 4.72 */
       "Expected 0, got %d\n", st[0].wDay);
    expect(0, st[0].wDayOfWeek);
    expect(0, st[0].wHour);
    expect(0, st[0].wMinute);
    expect(0, st[0].wSecond);
    expect(0, st[0].wMilliseconds);

    expect(0, st[1].wYear);
    expect(0, st[1].wMonth);
    expect(0, st[1].wDay);
    expect(0, st[1].wDayOfWeek);
    expect(0, st[1].wHour);
    expect(0, st[1].wMinute);
    expect(0, st[1].wSecond);
    expect(0, st[1].wMilliseconds);

    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, 0);
    ok(limits == 0, "got %u\n", limits);

    GetSystemTime(&st[0]);
    st[1] = st[0];

    SendMessageA(hwnd, MCM_GETTODAY, 0, (LPARAM)&today);

    /* Invalid date/time */
    st[0].wYear  = 2000;
    /* Time should not matter */
    st[1].wHour = st[1].wMinute = st[1].wSecond = 70;
    st[1].wMilliseconds = 1200;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set MAX limit\n");
    /* invalid timestamp is written back with today data and msecs untouched */
    expect(today.wHour, st[1].wHour);
    expect(today.wMinute, st[1].wMinute);
    expect(today.wSecond, st[1].wSecond);
    expect(1200, st[1].wMilliseconds);

    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX, "No limits should be set\n");
    ok(st1[0].wYear != 2000, "Lower limit changed\n");
    /* invalid timestamp should be replaced with today data, except msecs */
    expect(today.wHour, st1[1].wHour);
    expect(today.wMinute, st1[1].wMinute);
    expect(today.wSecond, st1[1].wSecond);
    expect(1200, st1[1].wMilliseconds);

    /* Invalid date/time with invalid milliseconds only */
    GetSystemTime(&st[0]);
    st[1] = st[0];
    /* Time should not matter */
    st[1].wMilliseconds = 1200;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set MAX limit\n");
    /* invalid milliseconds field doesn't lead to invalid timestamp */
    expect(st[0].wHour,   st[1].wHour);
    expect(st[0].wMinute, st[1].wMinute);
    expect(st[0].wSecond, st[1].wSecond);
    expect(1200, st[1].wMilliseconds);

    GetSystemTime(&st[0]);

    st[1].wMonth = 0;
    ok(!SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN | GDTR_MAX, (LPARAM)st),
            "Should have failed to set limits\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX, "No limits should be set\n");
    ok(st1[0].wYear != 2000, "Lower limit changed\n");
    ok(!SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st),
            "Should have failed to set MAX limit\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX, "No limits should be set\n");
    ok(st1[0].wYear != 2000, "Lower limit changed\n");

    GetSystemTime(&st[0]);
    st[0].wDay = 20;
    st[0].wMonth = 5;
    st[1] = st[0];

    month_range = SendMessageA(hwnd, MCM_GETMONTHRANGE, GMR_VISIBLE, (LPARAM)st1);
    st[1].wMonth--;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN | GDTR_MAX, (LPARAM)st),
            "Failed to set both min and max limits\n");
    res = SendMessageA(hwnd, MCM_GETMONTHRANGE, GMR_VISIBLE, (LPARAM)st1);
    ok(res == month_range, "Invalid month range (%d)\n", res);
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == (GDTR_MIN|GDTR_MAX),
            "Limits should be set\n");

    st[1].wMonth += 2;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN | GDTR_MAX, (LPARAM)st),
            "Failed to set both min and max limits\n");
    res = SendMessageA(hwnd, MCM_GETMONTHRANGE, GMR_VISIBLE, (LPARAM)st1);
    ok(res == month_range, "Invalid month range (%d)\n", res);

    st[1].wYear --;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN | GDTR_MAX, (LPARAM)st),
            "Failed to set both min and max limits\n");
    st[1].wYear += 1;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN | GDTR_MAX, (LPARAM)st),
            "Failed to set both min and max limits\n");

    st[1].wMonth -= 3;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set max limit\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX,
            "Only MAX limit should be set\n");
    st[1].wMonth += 4;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set max limit\n");
    st[1].wYear -= 3;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set max limit\n");
    st[1].wYear += 4;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set max limit\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX,
            "Only MAX limit should be set\n");

    /* set both limits, then set max < min */
    GetSystemTime(&st[0]);
    st[0].wDay = 25;
    st[1] = st[0];
    st[1].wYear++;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN|GDTR_MAX, (LPARAM)st), "Failed to set limits\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == (GDTR_MIN|GDTR_MAX),
            "Min limit expected\n");
    st[1].wYear -= 2;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st), "Failed to set limits\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MAX, "Max limit expected\n");

    expect(0, st1[0].wYear);
    expect(0, st1[0].wMonth);
    expect(0, st1[0].wDay);
    expect(0, st1[0].wDayOfWeek);
    expect(0, st1[0].wHour);
    expect(0, st1[0].wMinute);
    expect(0, st1[0].wSecond);
    expect(0, st1[0].wMilliseconds);

    expect(st[1].wYear,      st1[1].wYear);
    expect(st[1].wMonth,     st1[1].wMonth);
    expect(st[1].wDay,       st1[1].wDay);
    expect(st[1].wDayOfWeek, st1[1].wDayOfWeek);
    expect(st[1].wHour,      st1[1].wHour);
    expect(st[1].wMinute,    st1[1].wMinute);
    expect(st[1].wSecond,    st1[1].wSecond);
    expect(st[1].wMilliseconds, st1[1].wMilliseconds);

    st[1] = st[0];
    st[1].wYear++;
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN|GDTR_MAX, (LPARAM)st), "Failed to set limits\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == (GDTR_MIN|GDTR_MAX),
            "Min limit expected\n");
    st[0].wYear++; /* start == end now */
    ok(SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN, (LPARAM)st), "Failed to set limits\n");
    ok(SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1) == GDTR_MIN, "Min limit expected\n");

    expect(st[0].wYear,      st1[0].wYear);
    expect(st[0].wMonth,     st1[0].wMonth);
    expect(st[0].wDay,       st1[0].wDay);
    expect(st[0].wDayOfWeek, st1[0].wDayOfWeek);
    expect(st[0].wHour,      st1[0].wHour);
    expect(st[0].wMinute,    st1[0].wMinute);
    expect(st[0].wSecond,    st1[0].wSecond);
    expect(st[0].wMilliseconds, st1[0].wMilliseconds);

    expect(0, st1[1].wYear);
    expect(0, st1[1].wMonth);
    expect(0, st1[1].wDay);
    expect(0, st1[1].wDayOfWeek);
    expect(0, st1[1].wHour);
    expect(0, st1[1].wMinute);
    expect(0, st1[1].wSecond);
    expect(0, st1[1].wMilliseconds);

    /* 0 limit flags */
    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1);
    ok(limits == GDTR_MIN, "got 0x%08x\n", limits);

    GetSystemTime(st);
    st[1] = st[0];
    st[1].wYear++;
    r = SendMessageA(hwnd, MCM_SETRANGE, 0, (LPARAM)st);
    ok(r, "got %d\n", r);

    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st);
    ok(limits == 0, "got 0x%08x\n", limits);
    ok(st[0].wYear == 0 && st[1].wYear == 0, "got %u, %u\n", st[0].wYear, st[1].wYear);

    /* flags are 0, set min limit */
    GetSystemTime(st);
    st[1] = st[0];
    st[1].wYear++;

    r = SendMessageA(hwnd, MCM_SETRANGE, GDTR_MIN, (LPARAM)st);
    ok(r, "got %d\n", r);

    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1);
    ok(limits == GDTR_MIN, "got 0x%08x\n", limits);
    ok(st1[1].wYear == 0, "got %u\n", st1[1].wYear);

    /* now set max limit, check flags */
    r = SendMessageA(hwnd, MCM_SETRANGE, GDTR_MAX, (LPARAM)st);
    ok(r, "got %d\n", r);

    limits = SendMessageA(hwnd, MCM_GETRANGE, 0, (LPARAM)st1);
    ok(limits == GDTR_MAX, "got 0x%08x\n", limits);
    ok(st1[0].wYear == 0, "got %u\n", st1[0].wYear);

    DestroyWindow(hwnd);
}