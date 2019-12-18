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
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  create_inf_file (char*) ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pLaunchINFSection (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ winetest_interactive ; 

__attribute__((used)) static void test_LaunchINFSection(void)
{
    HRESULT hr;
    char cmdline[MAX_PATH];
    static char file[] = "test.inf,DefaultInstall,4,0";
    static char file2[] = "test.inf,,1,0";

    /* The 'No UI' flag seems to have no effect whatsoever on Windows.
     * So only do this test in interactive mode.
     */
    if (winetest_interactive)
    {
        /* try an invalid cmdline */
        hr = pLaunchINFSection(NULL, NULL, NULL, 0);
        ok(hr == 1, "Expected 1, got %d\n", hr);
    }

    CreateDirectoryA("one", NULL);
    create_inf_file("one\\test.inf");

    /* try a full path to the INF */
    lstrcpyA(cmdline, CURR_DIR);
    lstrcatA(cmdline, "\\");
    lstrcatA(cmdline, "one\\test.inf,DefaultInstall,,4");
    hr = pLaunchINFSection(NULL, NULL, cmdline, 0);
    ok(hr == 0, "Expected 0, got %d\n", hr);

    DeleteFileA("one\\test.inf");
    RemoveDirectoryA("one");

    create_inf_file("test.inf");

    /* try just the INF filename */
    hr = pLaunchINFSection(NULL, NULL, file, 0);
    ok(hr == 0, "Expected 0, got %d\n", hr);

    hr = pLaunchINFSection(NULL, NULL, file2, 0);
    ok(hr == 0, "Expected 0, got %d\n", hr);

    DeleteFileA("test.inf");
}