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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CopyFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_dll_path ; 

__attribute__((used)) static BOOL copy_dll_file(void)
{
    char sys_dir[MAX_PATH+15];
    char temp_path[MAX_PATH];

    if (GetSystemDirectoryA(sys_dir, MAX_PATH) == 0)
    {
        skip("Failed to get system directory. Skipping certificate/PE image tests.\n");
        return FALSE;
    }

    if (sys_dir[lstrlenA(sys_dir) - 1] != '\\')
        lstrcatA(sys_dir, "\\");

    lstrcatA(sys_dir, "imagehlp.dll");

    /* Copy DLL to a temp file */
    GetTempPathA(MAX_PATH, temp_path);
    GetTempFileNameA(temp_path, "img", 0, test_dll_path);

    if (CopyFileA(sys_dir, test_dll_path, FALSE) == 0)
    {
        skip("Unable to create copy of imagehlp.dll for tests.\n");
        return FALSE;
    }

    return TRUE;
}