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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL get_program_files_dir( char *buf, char *buf2 )
{
    HKEY hkey;
    DWORD type, size;

    if (RegOpenKeyA( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", &hkey ))
        return FALSE;

    size = MAX_PATH;
    if (RegQueryValueExA( hkey, "ProgramFilesDir (x86)", 0, &type, (LPBYTE)buf, &size ) &&
        RegQueryValueExA( hkey, "ProgramFilesDir", 0, &type, (LPBYTE)buf, &size ))
    {
        RegCloseKey( hkey );
        return FALSE;
    }
    size = MAX_PATH;
    if (RegQueryValueExA( hkey, "CommonFilesDir", 0, &type, (LPBYTE)buf2, &size ))
    {
        RegCloseKey( hkey );
        return FALSE;
    }
    RegCloseKey( hkey );
    return TRUE;
}