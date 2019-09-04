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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DRIVE_FIXED ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 scalar_t__ GetDriveTypeA (char*) ; 
 int GetFileAttributesA (char*) ; 
 int GetLogicalDrives () ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,int /*<<< orphan*/ ,int) ; 
 int lstrlenA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void search_absolute_directory(LPSTR absolute, LPCSTR relative)
{
    int i, size;
    DWORD attr, drives;

    size = lstrlenA(relative);
    drives = GetLogicalDrives();
    lstrcpyA(absolute, "A:\\");
    for (i = 0; i < 26; absolute[0] = '\0', i++)
    {
        if (!(drives & (1 << i)))
            continue;

        absolute[0] = 'A' + i;
        if (GetDriveTypeA(absolute) != DRIVE_FIXED)
            continue;

        lstrcpynA(absolute + 3, relative, size + 1);
        attr = GetFileAttributesA(absolute);
        if (attr != INVALID_FILE_ATTRIBUTES &&
            (attr & FILE_ATTRIBUTE_DIRECTORY))
        {
            if (absolute[3 + size - 1] != '\\')
                lstrcatA(absolute, "\\");
            break;
        }
        absolute[3] = '\0';
    }
}