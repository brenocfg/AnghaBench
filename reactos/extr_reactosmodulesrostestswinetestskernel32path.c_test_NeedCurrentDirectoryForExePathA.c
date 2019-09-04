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

/* Variables and functions */
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int pNeedCurrentDirectoryForExePathA (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_NeedCurrentDirectoryForExePathA(void)
{
    if (!pNeedCurrentDirectoryForExePathA)
    {
        win_skip("NeedCurrentDirectoryForExePathA is not available\n");
        return;
    }

    /* Crashes in Windows */
    if (0)
        pNeedCurrentDirectoryForExePathA(NULL);

    SetEnvironmentVariableA("NoDefaultCurrentDirectoryInExePath", NULL);
    ok(pNeedCurrentDirectoryForExePathA("."), "returned FALSE for \".\"\n");
    ok(pNeedCurrentDirectoryForExePathA("c:\\"), "returned FALSE for \"c:\\\"\n");
    ok(pNeedCurrentDirectoryForExePathA("cmd.exe"), "returned FALSE for \"cmd.exe\"\n");

    SetEnvironmentVariableA("NoDefaultCurrentDirectoryInExePath", "nya");
    ok(!pNeedCurrentDirectoryForExePathA("."), "returned TRUE for \".\"\n");
    ok(pNeedCurrentDirectoryForExePathA("c:\\"), "returned FALSE for \"c:\\\"\n");
    ok(!pNeedCurrentDirectoryForExePathA("cmd.exe"), "returned TRUE for \"cmd.exe\"\n");
}