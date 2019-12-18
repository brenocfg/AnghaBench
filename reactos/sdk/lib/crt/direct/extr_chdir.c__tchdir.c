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
typedef  int /*<<< orphan*/  _TCHAR ;
typedef  int WCHAR ;

/* Variables and functions */
 int GetCurrentDirectoryW (int,int*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetCurrentDirectory (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SetEnvironmentVariableW (int*,int*) ; 
 int /*<<< orphan*/  _dosmaperr (int /*<<< orphan*/ ) ; 
 int towupper (int) ; 

int _tchdir(const _TCHAR* _path)
{
    WCHAR newdir[MAX_PATH];

    if (!SetCurrentDirectory(_path))
    {
        _dosmaperr(_path ? GetLastError() : 0);
        return -1;
    }

    /* Update the drive-specific current directory variable */
    if (GetCurrentDirectoryW(MAX_PATH, newdir) >= 2)
    {
        if (newdir[1] == L':')
        {
            WCHAR envvar[4] = { L'=', towupper(newdir[0]), L':', L'\0' };
            SetEnvironmentVariableW(envvar, newdir);
        }
    }

    return 0;
}