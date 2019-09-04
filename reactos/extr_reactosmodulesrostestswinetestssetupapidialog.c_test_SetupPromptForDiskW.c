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
typedef  int /*<<< orphan*/  buffer ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DPROMPT_BUFFERTOOSMALL ; 
 scalar_t__ DPROMPT_SUCCESS ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int) ; 
 int /*<<< orphan*/  IDF_CHECKFIRST ; 
 int MAX_PATH ; 
 scalar_t__ SetupPromptForDiskW (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 scalar_t__ lstrcmpW (char*,char*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_SetupPromptForDiskW(void)
{
    WCHAR file[] = {'k','e','r','n','e','l','3','2','.','d','l','l','\0'};
    WCHAR title[] = {'T','e','s','t','\0'};
    WCHAR disk[] = {'T','e','s','t','d','i','s','k','\0'};
    WCHAR path[MAX_PATH];
    WCHAR buffer[MAX_PATH];
    UINT ret;
    DWORD length;

    GetSystemDirectoryW(path, MAX_PATH);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskW(0, title, disk, path, file, 0, IDF_CHECKFIRST, buffer, MAX_PATH-1, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %u\n", ret);
    ok(length == lstrlenW(path)+1, "Expect length %u, got %u\n", lstrlenW(path)+1, length);
    ok(lstrcmpW(path, buffer) == 0, "Expected path %s, got %s\n", wine_dbgstr_w(path), wine_dbgstr_w(buffer));

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskW(0, title, disk, path, file, 0, IDF_CHECKFIRST, 0, 0, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %d\n", ret);
    ok(length == lstrlenW(path)+1, "Expect length %u, got %u\n", lstrlenW(path)+1, length);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskW(0, title, disk, path, file, 0, IDF_CHECKFIRST, buffer, 1, &length);
    ok(ret == DPROMPT_BUFFERTOOSMALL, "Expected DPROMPT_BUFFERTOOSMALL, got %u\n", ret);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskW(0, title, disk, path, file, 0, IDF_CHECKFIRST, buffer, lstrlenW(path), &length);
    ok(ret == DPROMPT_BUFFERTOOSMALL, "Expected DPROMPT_BUFFERTOOSMALL, got %u\n", ret);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskW(0, title, disk, path, file, 0, IDF_CHECKFIRST, buffer, lstrlenW(path)+1, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %u\n", ret);
    ok(length == lstrlenW(path)+1, "Expect length %u, got %u\n", lstrlenW(path)+1, length);
    ok(lstrcmpW(path, buffer) == 0, "Expected path %s, got %s\n", wine_dbgstr_w(path), wine_dbgstr_w(buffer));
}