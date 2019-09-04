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
typedef  char WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; } ;
struct TYPE_6__ {int cb; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_2__ PROCESS_INFORMATION ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void run_child(WCHAR *secret)
{
    static const WCHAR format[] = {'%','s',' ','q','m','g','r',' ','%','s', 0};
    WCHAR cmdline[MAX_PATH];
    PROCESS_INFORMATION info;
    STARTUPINFOW startup;

    memset(&startup, 0, sizeof startup);
    startup.cb = sizeof startup;

    wsprintfW(cmdline, format, progname, secret);
    ok(CreateProcessW(NULL, cmdline, NULL, NULL, FALSE, 0L, NULL, NULL, &startup, &info), "CreateProcess\n");
    winetest_wait_child_process(info.hProcess);
    ok(CloseHandle(info.hProcess), "CloseHandle\n");
    ok(CloseHandle(info.hThread), "CloseHandle\n");
}