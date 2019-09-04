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
typedef  int /*<<< orphan*/  path_x86 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILESX86 ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES_COMMON ; 
 int /*<<< orphan*/  CSIDL_PROGRAM_FILES_COMMONX86 ; 
 int /*<<< orphan*/  E_FAIL ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegOpenKeyA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  SHGFP_TYPE_CURRENT ; 
 int /*<<< orphan*/  SHGetFolderPathA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pIsWow64Process (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHGetFolderPathA(void)
{
    static const BOOL is_win64 = sizeof(void *) > sizeof(int);
    BOOL is_wow64;
    char path[MAX_PATH];
    char path_x86[MAX_PATH];
    char path_key[MAX_PATH];
    HRESULT hr;
    HKEY key;

    if (!pIsWow64Process || !pIsWow64Process( GetCurrentProcess(), &is_wow64 )) is_wow64 = FALSE;

    hr = SHGetFolderPathA( 0, CSIDL_PROGRAM_FILES, 0, SHGFP_TYPE_CURRENT, path );
    ok( hr == S_OK, "SHGetFolderPathA failed %x\n", hr );
    hr = SHGetFolderPathA( 0, CSIDL_PROGRAM_FILESX86, 0, SHGFP_TYPE_CURRENT, path_x86 );
    if (hr == E_FAIL)
    {
        win_skip( "Program Files (x86) not supported\n" );
        return;
    }
    ok( hr == S_OK, "SHGetFolderPathA failed %x\n", hr );
    if (is_win64)
    {
        ok( lstrcmpiA( path, path_x86 ), "paths are identical '%s'\n", path );
        ok( strstr( path, "x86" ) == NULL, "64-bit path '%s' contains x86\n", path );
        ok( strstr( path_x86, "x86" ) != NULL, "32-bit path '%s' doesn't contain x86\n", path_x86 );
    }
    else
    {
        ok( !lstrcmpiA( path, path_x86 ), "paths differ '%s' != '%s'\n", path, path_x86 );
        if (is_wow64)
            ok( strstr( path, "x86" ) != NULL, "32-bit path '%s' doesn't contain x86\n", path );
        else
            ok( strstr( path, "x86" ) == NULL, "32-bit path '%s' contains x86\n", path );
    }
    if (!RegOpenKeyA( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", &key ))
    {
        DWORD type, count = sizeof(path_x86);
        if (!RegQueryValueExA( key, "ProgramFilesDir (x86)", NULL, &type, (BYTE *)path_key, &count ))
        {
            ok( is_win64 || is_wow64, "ProgramFilesDir (x86) exists on 32-bit setup\n" );
            ok( !lstrcmpiA( path_key, path_x86 ), "paths differ '%s' != '%s'\n", path_key, path_x86 );
        }
        else ok( !is_win64 && !is_wow64, "ProgramFilesDir (x86) should exist on 64-bit setup\n" );
        RegCloseKey( key );
    }

    hr = SHGetFolderPathA( 0, CSIDL_PROGRAM_FILES_COMMON, 0, SHGFP_TYPE_CURRENT, path );
    ok( hr == S_OK, "SHGetFolderPathA failed %x\n", hr );
    hr = SHGetFolderPathA( 0, CSIDL_PROGRAM_FILES_COMMONX86, 0, SHGFP_TYPE_CURRENT, path_x86 );
    if (hr == E_FAIL)
    {
        win_skip( "Common Files (x86) not supported\n" );
        return;
    }
    ok( hr == S_OK, "SHGetFolderPathA failed %x\n", hr );
    if (is_win64)
    {
        ok( lstrcmpiA( path, path_x86 ), "paths are identical '%s'\n", path );
        ok( strstr( path, "x86" ) == NULL, "64-bit path '%s' contains x86\n", path );
        ok( strstr( path_x86, "x86" ) != NULL, "32-bit path '%s' doesn't contain x86\n", path_x86 );
    }
    else
    {
        ok( !lstrcmpiA( path, path_x86 ), "paths differ '%s' != '%s'\n", path, path_x86 );
        if (is_wow64)
            ok( strstr( path, "x86" ) != NULL, "32-bit path '%s' doesn't contain x86\n", path );
        else
            ok( strstr( path, "x86" ) == NULL, "32-bit path '%s' contains x86\n", path );
    }
    if (!RegOpenKeyA( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion", &key ))
    {
        DWORD type, count = sizeof(path_x86);
        if (!RegQueryValueExA( key, "CommonFilesDir (x86)", NULL, &type, (BYTE *)path_key, &count ))
        {
            ok( is_win64 || is_wow64, "CommonFilesDir (x86) exists on 32-bit setup\n" );
            ok( !lstrcmpiA( path_key, path_x86 ), "paths differ '%s' != '%s'\n", path_key, path_x86 );
        }
        else ok( !is_win64 && !is_wow64, "CommonFilesDir (x86) should exist on 64-bit setup\n" );
    }
}