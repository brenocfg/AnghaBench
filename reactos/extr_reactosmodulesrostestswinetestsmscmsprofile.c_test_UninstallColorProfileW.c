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
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSCMS_basenameW (char*,char*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatW (char*,char*) ; 
 int /*<<< orphan*/ * machineW ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pGetColorDirectoryW (int /*<<< orphan*/ *,char*,int*) ; 
 int pInstallColorProfileW (int /*<<< orphan*/ *,char*) ; 
 int pUninstallColorProfileW (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_UninstallColorProfileW( WCHAR *testprofileW )
{
    BOOL ret;

    /* Parameter checks */

    ret = pUninstallColorProfileW( NULL, NULL, FALSE );
    ok( !ret, "UninstallColorProfileW() succeeded (%d)\n", GetLastError() );

    ret = pUninstallColorProfileW( machineW, NULL, FALSE );
    ok( !ret, "UninstallColorProfileW() succeeded (%d)\n", GetLastError() );

    /* Functional checks */

    if (testprofileW)
    {
        WCHAR dest[MAX_PATH], base[MAX_PATH];
        char destA[MAX_PATH];
        DWORD size = sizeof(dest);
        WCHAR slash[] = { '\\', 0 };
        HANDLE handle;
        int bytes_copied;

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

        ret = pUninstallColorProfileW( NULL, dest, TRUE );
        ok( ret, "UninstallColorProfileW() failed (%d)\n", GetLastError() );

        bytes_copied = WideCharToMultiByte(CP_ACP, 0, dest, -1, destA, MAX_PATH, NULL, NULL);
        ok( bytes_copied > 0 , "WideCharToMultiByte() returns %d\n", bytes_copied);
        /* Check if the profile is really gone */
        handle = CreateFileA( destA, 0 , 0, NULL, OPEN_EXISTING, 0, NULL );
        ok( handle == INVALID_HANDLE_VALUE, "Found the profile (%d)\n", GetLastError() );
        CloseHandle( handle );
    }
}