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
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  acl ;
struct TYPE_3__ {int nLength; int bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;
typedef  int /*<<< orphan*/  ACL ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_REVISION ; 
 int CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventA (TYPE_1__*,int,int,char*) ; 
 int ERROR_ALREADY_EXISTS ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int FALSE ; 
 int GetLastError () ; 
 scalar_t__ HighMemoryResourceNotification ; 
 int /*<<< orphan*/  InitializeAcl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LowMemoryResourceNotification ; 
 int /*<<< orphan*/ * OpenEventA (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * OpenEventW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetSecurityDescriptorDacl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int TRUE ; 
 int WAIT_OBJECT_0 ; 
 int WAIT_TIMEOUT ; 
 int WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pCreateMemoryResourceNotification (scalar_t__) ; 
 int pQueryMemoryResourceNotification (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_event(void)
{
    HANDLE handle, handle2;
    SECURITY_ATTRIBUTES sa;
    SECURITY_DESCRIPTOR sd;
    ACL acl;
    DWORD ret;
    BOOL val;

    /* no sd */
    handle = CreateEventA(NULL, FALSE, FALSE, __FILE__ ": Test Event");
    ok(handle != NULL, "CreateEventW with blank sd failed with error %d\n", GetLastError());
    CloseHandle(handle);

    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;

    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);

    /* blank sd */
    handle = CreateEventA(&sa, FALSE, FALSE, __FILE__ ": Test Event");
    ok(handle != NULL, "CreateEventW with blank sd failed with error %d\n", GetLastError());
    CloseHandle(handle);

    /* sd with NULL dacl */
    SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
    handle = CreateEventA(&sa, FALSE, FALSE, __FILE__ ": Test Event");
    ok(handle != NULL, "CreateEventW with blank sd failed with error %d\n", GetLastError());
    CloseHandle(handle);

    /* sd with empty dacl */
    InitializeAcl(&acl, sizeof(acl), ACL_REVISION);
    SetSecurityDescriptorDacl(&sd, TRUE, &acl, FALSE);
    handle = CreateEventA(&sa, FALSE, FALSE, __FILE__ ": Test Event");
    ok(handle != NULL, "CreateEventW with blank sd failed with error %d\n", GetLastError());
    CloseHandle(handle);

    /* test case sensitivity */

    SetLastError(0xdeadbeef);
    handle = CreateEventA(NULL, FALSE, FALSE, __FILE__ ": Test Event");
    ok( handle != NULL, "CreateEvent failed with error %u\n", GetLastError());
    ok( GetLastError() == 0, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = CreateEventA(NULL, FALSE, FALSE, __FILE__ ": Test Event");
    ok( handle2 != NULL, "CreateEvent failed with error %d\n", GetLastError());
    ok( GetLastError() == ERROR_ALREADY_EXISTS, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = CreateEventA(NULL, FALSE, FALSE, __FILE__ ": TEST EVENT");
    ok( handle2 != NULL, "CreateEvent failed with error %d\n", GetLastError());
    ok( GetLastError() == 0, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenEventA( EVENT_ALL_ACCESS, FALSE, __FILE__ ": Test Event");
    ok( handle2 != NULL, "OpenEvent failed with error %d\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenEventA( EVENT_ALL_ACCESS, FALSE, __FILE__ ": TEST EVENT");
    ok( !handle2, "OpenEvent succeeded\n");
    ok( GetLastError() == ERROR_FILE_NOT_FOUND, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenEventA( EVENT_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenEvent succeeded\n");
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenEventW( EVENT_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenEvent succeeded\n");
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    CloseHandle( handle );

    /* resource notifications are events too */

    if (!pCreateMemoryResourceNotification || !pQueryMemoryResourceNotification)
    {
        trace( "memory resource notifications not supported\n" );
        return;
    }
    handle = pCreateMemoryResourceNotification( HighMemoryResourceNotification + 1 );
    ok( !handle, "CreateMemoryResourceNotification succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );
    ret = pQueryMemoryResourceNotification( handle, &val );
    ok( !ret, "QueryMemoryResourceNotification succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    handle = pCreateMemoryResourceNotification( LowMemoryResourceNotification );
    ok( handle != 0, "CreateMemoryResourceNotification failed err %u\n", GetLastError() );
    ret = WaitForSingleObject( handle, 10 );
    ok( ret == WAIT_OBJECT_0 || ret == WAIT_TIMEOUT, "WaitForSingleObject wrong ret %u\n", ret );

    val = ~0;
    ret = pQueryMemoryResourceNotification( handle, &val );
    ok( ret, "QueryMemoryResourceNotification failed err %u\n", GetLastError() );
    ok( val == FALSE || val == TRUE, "wrong value %u\n", val );
    ret = CloseHandle( handle );
    ok( ret, "CloseHandle failed err %u\n", GetLastError() );

    handle = CreateEventA(NULL, FALSE, FALSE, __FILE__ ": Test Event");
    val = ~0;
    ret = pQueryMemoryResourceNotification( handle, &val );
    ok( ret, "QueryMemoryResourceNotification failed err %u\n", GetLastError() );
    ok( val == FALSE || val == TRUE, "wrong value %u\n", val );
    CloseHandle( handle );
}