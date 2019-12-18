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
typedef  int /*<<< orphan*/  UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DPROMPT_BUFFERTOOSMALL ; 
 int /*<<< orphan*/  DPROMPT_SUCCESS ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  IDF_CHECKFIRST ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetupPromptForDiskA (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_SetupPromptForDiskA(void)
{
    char file[] = "kernel32.dll";
    char path[MAX_PATH];
    char buffer[MAX_PATH];
    UINT ret;
    DWORD length;

    GetSystemDirectoryA(path, MAX_PATH);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskA(0, "Test", "Testdisk", path, file, 0, IDF_CHECKFIRST, buffer, sizeof(buffer) - 1, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %u\n", ret);
    ok(length == strlen(path)+1, "Expect length %u, got %u\n", (DWORD)strlen(path) + 1, length);
    ok(strcmp(path, buffer) == 0, "Expected path %s, got %s\n", path, buffer);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskA(0, "Test", "Testdisk", path, file, 0, IDF_CHECKFIRST, 0, 0, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %d\n", ret);
    ok(length == strlen(path)+1, "Expect length %u, got %u\n", (DWORD)strlen(path) + 1, length);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskA(0, "Test", "Testdisk", path, file, 0, IDF_CHECKFIRST, buffer, 1, &length);
    ok(ret == DPROMPT_BUFFERTOOSMALL, "Expected DPROMPT_BUFFERTOOSMALL, got %u\n", ret);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskA(0, "Test", "Testdisk", path, file, 0, IDF_CHECKFIRST, buffer, strlen(path), &length);
    ok(ret == DPROMPT_BUFFERTOOSMALL, "Expected DPROMPT_BUFFERTOOSMALL, got %u\n", ret);

    memset(buffer, 0, sizeof(buffer));
    ret = SetupPromptForDiskA(0, "Test", "Testdisk", path, file, 0, IDF_CHECKFIRST, buffer, strlen(path)+1, &length);
    ok(ret == DPROMPT_SUCCESS, "Expected DPROMPT_SUCCESS, got %u\n", ret);
    ok(length == strlen(path)+1, "Expect length %u, got %u\n", (DWORD)strlen(path) + 1, length);
    ok(strcmp(path, buffer) == 0, "Expected path %s, got %s\n", path, buffer);
}