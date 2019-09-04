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
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  APP_PATH ; 
 scalar_t__ APP_PATH_LEN ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  PROG_FILES ; 
 scalar_t__ PROG_FILES_ROOT ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_STRING1 ; 
 int /*<<< orphan*/  lstrcatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lstrlenA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_progfiles_dir(void)
{
    HKEY hkey;
    DWORD size = MAX_PATH;

    RegOpenKeyA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", &hkey);
    RegQueryValueExA(hkey, "ProgramFilesDir", NULL, NULL, (LPBYTE)PROG_FILES_ROOT, &size);
    RegCloseKey(hkey);

    lstrcpyA(PROG_FILES, PROG_FILES_ROOT + 3); /* skip C:\ */
    lstrcpyA(APP_PATH, PROG_FILES_ROOT);
    lstrcatA(APP_PATH, TEST_STRING1);
    APP_PATH_LEN = lstrlenA(APP_PATH) + 1;
}