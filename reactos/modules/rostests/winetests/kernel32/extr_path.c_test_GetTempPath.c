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
typedef  int /*<<< orphan*/  windir ;
typedef  int /*<<< orphan*/  save_TMP ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentDirectoryW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetEnvironmentVariableA (char*,char*,int) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetCurrentDirectoryW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_GetTempPathA (char*) ; 
 int /*<<< orphan*/  test_GetTempPathW (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void test_GetTempPath(void)
{
    char save_TMP[MAX_PATH];
    char windir[MAX_PATH];
    char buf[MAX_PATH];
    WCHAR curdir[MAX_PATH];

    if (!GetEnvironmentVariableA("TMP", save_TMP, sizeof(save_TMP))) save_TMP[0] = 0;

    /* test default configuration */
    trace("TMP=%s\n", save_TMP);
    if (save_TMP[0])
    {
        strcpy(buf,save_TMP);
        if (buf[strlen(buf)-1]!='\\')
            strcat(buf,"\\");
        test_GetTempPathA(buf);
        test_GetTempPathW(buf);
    }

    /* TMP=C:\WINDOWS */
    GetWindowsDirectoryA(windir, sizeof(windir));
    SetEnvironmentVariableA("TMP", windir);
    GetEnvironmentVariableA("TMP", buf, sizeof(buf));
    trace("TMP=%s\n", buf);
    strcat(windir,"\\");
    test_GetTempPathA(windir);
    test_GetTempPathW(windir);

    /* TMP=C:\ */
    GetWindowsDirectoryA(windir, sizeof(windir));
    windir[3] = 0;
    SetEnvironmentVariableA("TMP", windir);
    GetEnvironmentVariableA("TMP", buf, sizeof(buf));
    trace("TMP=%s\n", buf);
    test_GetTempPathA(windir);
    test_GetTempPathW(windir);

    GetCurrentDirectoryW(MAX_PATH, curdir);
    /* TMP=C: i.e. use current working directory of the specified drive */
    GetWindowsDirectoryA(windir, sizeof(windir));
    SetCurrentDirectoryA(windir);
    windir[2] = 0;
    SetEnvironmentVariableA("TMP", windir);
    GetEnvironmentVariableA("TMP", buf, sizeof(buf));
    trace("TMP=%s\n", buf);
    GetWindowsDirectoryA(windir, sizeof(windir));
    strcat(windir,"\\");
    test_GetTempPathA(windir);
    test_GetTempPathW(windir);

    SetEnvironmentVariableA("TMP", save_TMP);
    SetCurrentDirectoryW(curdir);
}