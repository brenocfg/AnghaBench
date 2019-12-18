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
typedef  int /*<<< orphan*/  si ;
struct TYPE_6__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_5__ {int cb; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcessA (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  winetest_get_mainargs (char***) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_child_process(void)
{
    char cmdline[MAX_PATH];
    char path[MAX_PATH];
    char **argv;
    PROCESS_INFORMATION pi;
    STARTUPINFOA si = { 0 };
    BOOL ret;

    GetModuleFileNameA(NULL, path, MAX_PATH);

    si.cb = sizeof(si);
    winetest_get_mainargs(&argv);
    sprintf(cmdline, "\"%s\" %s domain_tests", argv[0], argv[1]);
    ret = CreateProcessA(argv[0], cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
    ok(ret, "Failed to spawn child process: %u\n", GetLastError());
    winetest_wait_child_process(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
}