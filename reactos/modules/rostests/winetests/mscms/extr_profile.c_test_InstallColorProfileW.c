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
typedef  int /*<<< orphan*/  dest ;
typedef  char WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSCMS_basenameW (char*,char*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 char* machineW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int pGetColorDirectoryW (int /*<<< orphan*/ *,char*,int*) ; 
 int pInstallColorProfileW (char*,char*) ; 
 int pUninstallColorProfileW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_InstallColorProfileW( WCHAR *standardprofileW, WCHAR *testprofileW )
{
    BOOL ret;

    /* Parameter checks */

    ret = pInstallColorProfileW( NULL, NULL );
    ok( !ret, "InstallColorProfileW() succeeded (%d)\n", GetLastError() );

    ret = pInstallColorProfileW( machineW, NULL );
    ok( !ret, "InstallColorProfileW() succeeded (%d)\n", GetLastError() );

    ret = pInstallColorProfileW( NULL, machineW );
    ok( !ret, "InstallColorProfileW() failed (%d)\n", GetLastError() );

    if (standardprofileW)
    {
        ret = pInstallColorProfileW( NULL, standardprofileW );
        ok( ret, "InstallColorProfileW() failed (%d)\n", GetLastError() );
    }

    /* Functional checks */

    if (testprofileW)
    {
        WCHAR dest[MAX_PATH], base[MAX_PATH];
        DWORD size = sizeof(dest);
        WCHAR slash[] = { '\\', 0 };
        HANDLE handle;

        SetLastError(0xdeadbeef);
        ret = pInstallColorProfileW( NULL, testprofileW );
        if (!ret && (GetLastError() == ERROR_ACCESS_DENIED))
        {
            skip("Not enough rights for InstallColorProfileW\n");
            return;
        }
        ok( ret, "InstallColorProfileW() failed (%d)\n", GetLastError() );

        ret = pGetColorDirectoryW( NULL, dest, &size );
        ok( ret, "GetColorDirectoryW() failed (%d)\n", GetLastError() );

        MSCMS_basenameW( testprofileW, base );

        lstrcatW( dest, slash );
        lstrcatW( dest, base );

        /* Check if the profile is really there */
        handle = CreateFileW( dest, 0 , 0, NULL, OPEN_EXISTING, 0, NULL );
        ok( handle != INVALID_HANDLE_VALUE, "Couldn't find the profile (%d)\n", GetLastError() );
        CloseHandle( handle );

        ret = pUninstallColorProfileW( NULL, dest, TRUE );
        ok( ret, "UninstallColorProfileW() failed (%d)\n", GetLastError() );
    }
}