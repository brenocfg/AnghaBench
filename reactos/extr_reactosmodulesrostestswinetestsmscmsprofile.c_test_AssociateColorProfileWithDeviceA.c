#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  profile ;
struct TYPE_3__ {int cb; int /*<<< orphan*/ * DeviceID; int /*<<< orphan*/ * DeviceName; } ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DISPLAY_DEVICEA ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_NOT_SUPPORTED ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSCMS_basenameA (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pAssociateColorProfileWithDeviceA (char*,char*,int /*<<< orphan*/ *) ; 
 int pDisassociateColorProfileFromDeviceA (char*,char*,int /*<<< orphan*/ *) ; 
 int pEnumDisplayDevicesA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pGetColorDirectoryA (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int pInstallColorProfileA (int /*<<< orphan*/ *,char*) ; 
 int pUninstallColorProfileA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_AssociateColorProfileWithDeviceA( char *testprofile )
{
    BOOL ret;
    char profile[MAX_PATH], basename[MAX_PATH];
    DWORD error, size = sizeof(profile);
    DISPLAY_DEVICEA display, monitor;
    BOOL res;

    if (testprofile && pEnumDisplayDevicesA)
    {
        display.cb = sizeof( DISPLAY_DEVICEA );
        res = pEnumDisplayDevicesA( NULL, 0, &display, 0 );
        ok( res, "Can't get display info\n" );

        monitor.cb = sizeof( DISPLAY_DEVICEA );
        res = pEnumDisplayDevicesA( display.DeviceName, 0, &monitor, 0 );
        if (res)
        {
            SetLastError(0xdeadbeef);
            ret = pAssociateColorProfileWithDeviceA( "machine", testprofile, NULL );
            error = GetLastError();
            ok( !ret, "AssociateColorProfileWithDevice() succeeded\n" );
            ok( error == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", error );

            SetLastError(0xdeadbeef);
            ret = pAssociateColorProfileWithDeviceA( "machine", NULL, monitor.DeviceID );
            error = GetLastError();
            ok( !ret, "AssociateColorProfileWithDevice() succeeded\n" );
            ok( error == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", error );

            SetLastError(0xdeadbeef);
            ret = pAssociateColorProfileWithDeviceA( "machine", testprofile, monitor.DeviceID );
            error = GetLastError();
            ok( !ret, "AssociateColorProfileWithDevice() succeeded\n" );
            ok( error == ERROR_NOT_SUPPORTED, "expected ERROR_NOT_SUPPORTED, got %u\n", error );

            ret = pInstallColorProfileA( NULL, testprofile );
            ok( ret, "InstallColorProfileA() failed (%u)\n", GetLastError() );

            ret = pGetColorDirectoryA( NULL, profile, &size );
            ok( ret, "GetColorDirectoryA() failed (%d)\n", GetLastError() );

            MSCMS_basenameA( testprofile, basename );
            lstrcatA( profile, "\\" );
            lstrcatA( profile, basename );

            ret = pAssociateColorProfileWithDeviceA( NULL, profile, monitor.DeviceID );
            ok( ret, "AssociateColorProfileWithDevice() failed (%u)\n", GetLastError() );

            SetLastError(0xdeadbeef);
            ret = pDisassociateColorProfileFromDeviceA( "machine", profile, NULL );
            error = GetLastError();
            ok( !ret, "DisassociateColorProfileFromDeviceA() succeeded\n" );
            ok( error == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", error );

            SetLastError(0xdeadbeef);
            ret = pDisassociateColorProfileFromDeviceA( "machine", NULL, monitor.DeviceID );
            error = GetLastError();
            ok( !ret, "DisassociateColorProfileFromDeviceA() succeeded\n" );
            ok( error == ERROR_INVALID_PARAMETER, "expected ERROR_INVALID_PARAMETER, got %u\n", error );

            SetLastError(0xdeadbeef);
            ret = pDisassociateColorProfileFromDeviceA( "machine", profile, monitor.DeviceID );
            error = GetLastError();
            ok( !ret, "DisassociateColorProfileFromDeviceA() succeeded\n" );
            ok( error == ERROR_NOT_SUPPORTED, "expected ERROR_NOT_SUPPORTED, got %u\n", error );

            ret = pDisassociateColorProfileFromDeviceA( NULL, profile, monitor.DeviceID );
            ok( ret, "DisassociateColorProfileFromDeviceA() failed (%u)\n", GetLastError() );

            ret = pUninstallColorProfileA( NULL, profile, TRUE );
            ok( ret, "UninstallColorProfileA() failed (%d)\n", GetLastError() );
        }
        else
            skip("Unable to obtain monitor name\n");
    }
}