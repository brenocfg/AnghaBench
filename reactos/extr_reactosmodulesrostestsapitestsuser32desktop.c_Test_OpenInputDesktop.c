#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ HWINSTA ;
typedef  int /*<<< orphan*/ * HDESK ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CloseDesktop (int /*<<< orphan*/ *) ; 
 scalar_t__ CloseWindowStation (scalar_t__) ; 
 scalar_t__ CreateWindowStationW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DESKTOP_ALL_ACCESS ; 
 scalar_t__ ERROR_INVALID_FUNCTION ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetProcessWindowStation () ; 
 int /*<<< orphan*/ * GetThreadDesktop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenInputDesktop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SetProcessWindowStation (scalar_t__) ; 
 scalar_t__ SetThreadDesktop (int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WINSTA_ALL_ACCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_OpenInputDesktop()
{
    HDESK hDeskInput ,hDeskInput2;
    HDESK hDeskInitial;
    BOOL ret;
    HWINSTA hwinsta = NULL, hwinstaInitial;
    DWORD err;

    hDeskInput = OpenInputDesktop(0, FALSE, DESKTOP_ALL_ACCESS);
    ok(hDeskInput != NULL, "OpenInputDesktop failed\n");
    hDeskInitial = GetThreadDesktop( GetCurrentThreadId() );
    ok(hDeskInitial != NULL, "GetThreadDesktop failed\n");
    ok(hDeskInput != hDeskInitial, "OpenInputDesktop returned thread desktop\n");

    hDeskInput2 = OpenInputDesktop(0, FALSE, DESKTOP_ALL_ACCESS);
    ok(hDeskInput2 != NULL, "Second call to OpenInputDesktop failed\n");
    ok(hDeskInput2 != hDeskInput, "Second call to OpenInputDesktop returned same handle\n");

    ok(CloseDesktop(hDeskInput2) != 0, "CloseDesktop failed\n");

    ret = SetThreadDesktop(hDeskInput);
    ok(ret == TRUE, "SetThreadDesktop for input desktop failed\n");

    ret = SetThreadDesktop(hDeskInitial);
    ok(ret == TRUE, "SetThreadDesktop for initial desktop failed\n");

    ok(CloseDesktop(hDeskInput) != 0, "CloseDesktop failed\n");

    /* Try calling OpenInputDesktop after switching to a new winsta */
    hwinstaInitial = GetProcessWindowStation();
    ok(hwinstaInitial != 0, "GetProcessWindowStation failed\n");

    hwinsta = CreateWindowStationW(L"TestWinsta", 0, WINSTA_ALL_ACCESS, NULL);
    ok(hwinsta != 0, "CreateWindowStationW failed\n");

    ret = SetProcessWindowStation(hwinsta);
    ok(ret != FALSE, "SetProcessWindowStation failed\n");

    hDeskInput = OpenInputDesktop(0, FALSE, DESKTOP_ALL_ACCESS);
    ok(hDeskInput == 0, "OpenInputDesktop should fail\n");

    err = GetLastError();
    ok(err == ERROR_INVALID_FUNCTION, "Got last error: %lu\n", err);

    ret = SetProcessWindowStation(hwinstaInitial);
    ok(ret != FALSE, "SetProcessWindowStation failed\n");

    ret = CloseWindowStation(hwinsta);
    ok(ret != FALSE, "CloseWindowStation failed\n");

}