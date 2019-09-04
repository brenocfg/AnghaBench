#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  startup ;
typedef  int /*<<< orphan*/  originalPath ;
struct TYPE_9__ {int dwMajorVersion; } ;
struct TYPE_8__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_7__ {int cb; void* wShowWindow; void* dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOA ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateProcessA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 int /*<<< orphan*/  RegFlushKey (scalar_t__) ; 
 int /*<<< orphan*/  RegOpenKeyExA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RegQueryValueExA (scalar_t__,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RegSetValueExA (scalar_t__,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 void* STARTF_USESHOWWINDOW ; 
 void* SW_SHOWNORMAL ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pSHFileOperationA ; 
 int /*<<< orphan*/  pSHGetFolderLocation ; 
 int /*<<< orphan*/  pSHGetFolderPathA ; 
 int /*<<< orphan*/  pSHGetSpecialFolderLocation ; 
 int /*<<< orphan*/  pSHGetSpecialFolderPathA ; 
 char* selfname ; 
 TYPE_3__ shellVersion ; 
 int /*<<< orphan*/  skip (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  trace (char*,char*) ; 
 int /*<<< orphan*/  winetest_wait_child_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_NonExistentPath(void)
{
    static const char userShellFolders[] =
     "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders";
    char originalPath[MAX_PATH], modifiedPath[MAX_PATH];
    HKEY key;

    if (!pSHGetFolderPathA) return;
    if (!pSHGetFolderLocation) return;
    if (!pSHGetSpecialFolderPathA) return;
    if (!pSHGetSpecialFolderLocation) return;
    if (!pSHFileOperationA) return;
    if (shellVersion.dwMajorVersion < 5) return;

    if (!RegOpenKeyExA(HKEY_CURRENT_USER, userShellFolders, 0, KEY_ALL_ACCESS,
     &key))
    {
        DWORD len, type;

        len = sizeof(originalPath);
        if (!RegQueryValueExA(key, "Favorites", NULL, &type,
         (LPBYTE)&originalPath, &len))
        {
            size_t len = strlen(originalPath);

            memcpy(modifiedPath, originalPath, len);
            modifiedPath[len++] = '2';
            modifiedPath[len++] = '\0';
            trace("Changing CSIDL_FAVORITES to %s\n", modifiedPath);
            if (!RegSetValueExA(key, "Favorites", 0, type,
             (LPBYTE)modifiedPath, len))
            {
                char buffer[MAX_PATH+20];
                STARTUPINFOA startup;
                PROCESS_INFORMATION info;

                sprintf(buffer, "%s tests/shellpath.c 1", selfname);
                memset(&startup, 0, sizeof(startup));
                startup.cb = sizeof(startup);
                startup.dwFlags = STARTF_USESHOWWINDOW;
                startup.wShowWindow = SW_SHOWNORMAL;
                CreateProcessA(NULL, buffer, NULL, NULL, FALSE, 0L, NULL, NULL,
                 &startup, &info);
                winetest_wait_child_process( info.hProcess );

                /* restore original values: */
                trace("Restoring CSIDL_FAVORITES to %s\n", originalPath);
                RegSetValueExA(key, "Favorites", 0, type, (LPBYTE) originalPath,
                 strlen(originalPath) + 1);
                RegFlushKey(key);

                sprintf(buffer, "%s tests/shellpath.c 2", selfname);
                memset(&startup, 0, sizeof(startup));
                startup.cb = sizeof(startup);
                startup.dwFlags = STARTF_USESHOWWINDOW;
                startup.wShowWindow = SW_SHOWNORMAL;
                CreateProcessA(NULL, buffer, NULL, NULL, FALSE, 0L, NULL, NULL,
                 &startup, &info);
                ok(WaitForSingleObject(info.hProcess, 30000) == WAIT_OBJECT_0,
                 "child process termination\n");
            }
        }
        else skip("RegQueryValueExA(key, Favorites, ...) failed\n");
        if (key)
            RegCloseKey(key);
    }
    else skip("RegOpenKeyExA(HKEY_CURRENT_USER, %s, ...) failed\n", userShellFolders);
}