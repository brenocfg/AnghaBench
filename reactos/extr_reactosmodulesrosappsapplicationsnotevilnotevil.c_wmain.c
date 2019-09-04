#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_10__ {int X; int Y; } ;
struct TYPE_9__ {int Right; int Left; int Bottom; int Top; } ;
struct TYPE_13__ {TYPE_2__ dwSize; TYPE_1__ srWindow; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int QuadPart; } ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_4__ COORD ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_TEXTMODE_BUFFER ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateConsoleScreenBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateWaitableTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillConsoleOutputAttribute (scalar_t__,int /*<<< orphan*/ ,int,TYPE_4__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ ,TYPE_6__*) ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MainLoop () ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 scalar_t__ ScreenBuffer ; 
 TYPE_6__ ScreenBufferInfo ; 
 int /*<<< orphan*/  SetConsoleActiveScreenBuffer (scalar_t__) ; 
 int /*<<< orphan*/  SetWaitableTimer (scalar_t__,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WaitableTimer ; 
 char* app_name ; 
 int /*<<< orphan*/  myself ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

int wmain(int argc, WCHAR* argv[])
{
    LARGE_INTEGER lint;
    DWORD Written;
    COORD Coord = { 0, 0 };

    myself = GetModuleHandle(NULL);

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                               &ScreenBufferInfo);
    ScreenBufferInfo.dwSize.X = ScreenBufferInfo.srWindow.Right - ScreenBufferInfo.srWindow.Left + 1;
    ScreenBufferInfo.dwSize.Y = ScreenBufferInfo.srWindow.Bottom - ScreenBufferInfo.srWindow.Top + 1;
    ScreenBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE,
                                             0,
                                             NULL,
                                             CONSOLE_TEXTMODE_BUFFER,
                                             NULL);
    if (ScreenBuffer == INVALID_HANDLE_VALUE)
    {
        wprintf(L"%s: could not create a new screen buffer\n", app_name);
        return EXIT_FAILURE;
    }

    /* Fill buffer with black background */
    FillConsoleOutputAttribute(ScreenBuffer,
                               0,
                               ScreenBufferInfo.dwSize.X * ScreenBufferInfo.dwSize.Y,
                               Coord,
                               &Written);

    WaitableTimer = CreateWaitableTimer(NULL, FALSE, NULL);
    if (WaitableTimer == INVALID_HANDLE_VALUE)
    {
        wprintf(L"CreateWaitabletimer() failed\n");
        return 1;
    }
    lint.QuadPart = -2000000;
    if (!SetWaitableTimer(WaitableTimer, &lint, 200, NULL, NULL, FALSE))
    {
        wprintf(L"SetWaitableTimer() failed: 0x%lx\n", GetLastError());
        return 2;
    }
    SetConsoleActiveScreenBuffer(ScreenBuffer);
    MainLoop();
    CloseHandle(ScreenBuffer);
    return EXIT_SUCCESS;
}