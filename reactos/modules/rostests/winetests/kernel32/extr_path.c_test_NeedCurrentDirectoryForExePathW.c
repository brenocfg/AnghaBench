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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int pNeedCurrentDirectoryForExePathW (char const*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_NeedCurrentDirectoryForExePathW(void)
{
    const WCHAR thispath[] = {'.', 0};
    const WCHAR fullpath[] = {'c', ':', '\\', 0};
    const WCHAR cmdname[] = {'c', 'm', 'd', '.', 'e', 'x', 'e', 0};

    if (!pNeedCurrentDirectoryForExePathW)
    {
        win_skip("NeedCurrentDirectoryForExePathW is not available\n");
        return;
    }

    /* Crashes in Windows */
    if (0)
        pNeedCurrentDirectoryForExePathW(NULL);

    SetEnvironmentVariableA("NoDefaultCurrentDirectoryInExePath", NULL);
    ok(pNeedCurrentDirectoryForExePathW(thispath), "returned FALSE for \".\"\n");
    ok(pNeedCurrentDirectoryForExePathW(fullpath), "returned FALSE for \"c:\\\"\n");
    ok(pNeedCurrentDirectoryForExePathW(cmdname), "returned FALSE for \"cmd.exe\"\n");

    SetEnvironmentVariableA("NoDefaultCurrentDirectoryInExePath", "nya");
    ok(!pNeedCurrentDirectoryForExePathW(thispath), "returned TRUE for \".\"\n");
    ok(pNeedCurrentDirectoryForExePathW(fullpath), "returned FALSE for \"c:\\\"\n");
    ok(!pNeedCurrentDirectoryForExePathW(cmdname), "returned TRUE for \"cmd.exe\"\n");
}