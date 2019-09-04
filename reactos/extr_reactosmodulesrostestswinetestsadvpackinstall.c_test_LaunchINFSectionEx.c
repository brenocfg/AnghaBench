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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 char* CURR_DIR ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ E_INVALIDARG ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  create_inf_file (char*) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pLaunchINFSectionEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_LaunchINFSectionEx(void)
{
    HRESULT hr;
    char cmdline[MAX_PATH];

    create_inf_file("test.inf");

    /* try an invalid CAB filename with an absolute INF name */
    lstrcpyA(cmdline, CURR_DIR);
    lstrcatA(cmdline, "\\");
    lstrcatA(cmdline, "test.inf,DefaultInstall,c:imacab.cab,4");
    hr = pLaunchINFSectionEx(NULL, NULL, cmdline, 0);
    ok(hr == 0, "Expected 0, got %d\n", hr);

    /* try quoting the parameters */
    lstrcpyA(cmdline, "\"");
    lstrcatA(cmdline, CURR_DIR);
    lstrcatA(cmdline, "\\test.inf\",\"DefaultInstall\",\"c:,imacab.cab\",\"4\"");
    hr = pLaunchINFSectionEx(NULL, NULL, cmdline, 0);
    ok(hr == 0, "Expected 0, got %d\n", hr);

    /* The 'No UI' flag seems to have no effect whatsoever on Windows.
     * So only do this test in interactive mode.
     */
    if (winetest_interactive)
    {
        /* try an invalid CAB filename with a relative INF name */
        lstrcpyA(cmdline, "test.inf,DefaultInstall,c:imacab.cab,4");
        hr = pLaunchINFSectionEx(NULL, NULL, cmdline, 0);
        ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %d\n", hr);
    }

    DeleteFileA("test.inf");
}