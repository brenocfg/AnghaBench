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
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSCMS_basenameA (char*,char*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/ * machine ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int pGetColorDirectoryA (int /*<<< orphan*/ *,char*,int*) ; 
 int pInstallColorProfileA (int /*<<< orphan*/ *,char*) ; 
 int pUninstallColorProfileA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_UninstallColorProfileA( char *testprofile )
{
    BOOL ret;

    /* Parameter checks */

    ret = pUninstallColorProfileA( NULL, NULL, FALSE );
    ok( !ret, "UninstallColorProfileA() succeeded (%d)\n", GetLastError() );

    ret = pUninstallColorProfileA( machine, NULL, FALSE );
    ok( !ret, "UninstallColorProfileA() succeeded (%d)\n", GetLastError() );

    /* Functional checks */

    if (testprofile)
    {
        CHAR dest[MAX_PATH], base[MAX_PATH];
        DWORD size = sizeof(dest);
        CHAR slash[] = "\\";
        HANDLE handle;

        SetLastError(0xdeadbeef);
        ret = pInstallColorProfileA( NULL, testprofile );
        if (!ret && (GetLastError() == ERROR_ACCESS_DENIED))
        {
            skip("Not enough rights for InstallColorProfileA\n");
            return;
        }
        ok( ret, "InstallColorProfileA() failed (%d)\n", GetLastError() );

        ret = pGetColorDirectoryA( NULL, dest, &size );
        ok( ret, "GetColorDirectoryA() failed (%d)\n", GetLastError() );

        MSCMS_basenameA( testprofile, base );

        lstrcatA( dest, slash );
        lstrcatA( dest, base );

        ret = pUninstallColorProfileA( NULL, dest, TRUE );
        ok( ret, "UninstallColorProfileA() failed (%d)\n", GetLastError() );

        /* Check if the profile is really gone */
        handle = CreateFileA( dest, 0 , 0, NULL, OPEN_EXISTING, 0, NULL );
        ok( handle == INVALID_HANDLE_VALUE, "Found the profile (%d)\n", GetLastError() );
        CloseHandle( handle );
    }
}