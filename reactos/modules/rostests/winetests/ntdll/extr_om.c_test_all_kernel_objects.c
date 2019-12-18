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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int QuadPart; } ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int /*<<< orphan*/  NotificationTimer ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int /*<<< orphan*/  SECTION_MAP_WRITE ; 
 int /*<<< orphan*/  SEC_COMMIT ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateDirectoryObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateIoCompletion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateJobObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtCreateKeyedEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateMutant (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtCreateSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ pNtCreateSymbolicLinkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtCreateTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pNtOpenDirectoryObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenIoCompletion (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenJobObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenKeyedEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenMutant (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenSection (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenSymbolicLinkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pNtOpenTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_all_kernel_objects( UINT line, OBJECT_ATTRIBUTES *attr,
                                     NTSTATUS create_expect, NTSTATUS open_expect )
{
    UNICODE_STRING target;
    LARGE_INTEGER size;
    NTSTATUS status, status2;
    HANDLE ret, ret2;

    pRtlCreateUnicodeStringFromAsciiz( &target, "\\DosDevices" );
    size.QuadPart = 4096;

    status = pNtCreateMutant( &ret, GENERIC_ALL, attr, FALSE );
    ok( status == create_expect, "%u: NtCreateMutant failed %x\n", line, status );
    status2 = pNtOpenMutant( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenMutant failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateSemaphore( &ret, GENERIC_ALL, attr, 1, 2 );
    ok( status == create_expect, "%u: NtCreateSemaphore failed %x\n", line, status );
    status2 = pNtOpenSemaphore( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenSemaphore failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateEvent( &ret, GENERIC_ALL, attr, 1, 0 );
    ok( status == create_expect, "%u: NtCreateEvent failed %x\n", line, status );
    status2 = pNtOpenEvent( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenEvent failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateKeyedEvent( &ret, GENERIC_ALL, attr, 0 );
    ok( status == create_expect, "%u: NtCreateKeyedEvent failed %x\n", line, status );
    status2 = pNtOpenKeyedEvent( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenKeyedEvent failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateTimer( &ret, GENERIC_ALL, attr, NotificationTimer );
    ok( status == create_expect, "%u: NtCreateTimer failed %x\n", line, status );
    status2 = pNtOpenTimer( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenTimer failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateIoCompletion( &ret, GENERIC_ALL, attr, 0 );
    ok( status == create_expect, "%u: NtCreateCompletion failed %x\n", line, status );
    status2 = pNtOpenIoCompletion( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenCompletion failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateJobObject( &ret, GENERIC_ALL, attr );
    ok( status == create_expect, "%u: NtCreateJobObject failed %x\n", line, status );
    status2 = pNtOpenJobObject( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenJobObject failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateDirectoryObject( &ret, GENERIC_ALL, attr );
    ok( status == create_expect, "%u: NtCreateDirectoryObject failed %x\n", line, status );
    status2 = pNtOpenDirectoryObject( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenDirectoryObject failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateSymbolicLinkObject( &ret, GENERIC_ALL, attr, &target );
    ok( status == create_expect, "%u: NtCreateSymbolicLinkObject failed %x\n", line, status );
    status2 = pNtOpenSymbolicLinkObject( &ret2, GENERIC_ALL, attr );
    ok( status2 == open_expect, "%u: NtOpenSymbolicLinkObject failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    status = pNtCreateSection( &ret, SECTION_MAP_WRITE, attr, &size, PAGE_READWRITE, SEC_COMMIT, 0 );
    ok( status == create_expect, "%u: NtCreateSection failed %x\n", line, status );
    status2 = pNtOpenSection( &ret2, SECTION_MAP_WRITE, attr );
    ok( status2 == open_expect, "%u: NtOpenSection failed %x\n", line, status2 );
    if (!status) pNtClose( ret );
    if (!status2) pNtClose( ret2 );
    pRtlFreeUnicodeString( &target );
}