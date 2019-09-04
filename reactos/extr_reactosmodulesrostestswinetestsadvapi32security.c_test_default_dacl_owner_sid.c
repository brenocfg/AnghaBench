#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  SidStart; } ;
struct TYPE_4__ {int nLength; int /*<<< orphan*/ * lpSecurityDescriptor; void* bInheritHandle; } ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  TYPE_1__ SECURITY_ATTRIBUTES ;
typedef  void* PSID ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;
typedef  void ACL ;
typedef  TYPE_2__ ACCESS_ALLOWED_ACE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateEventA (TYPE_1__*,int,int,char*) ; 
 int DACL_SECURITY_INFORMATION ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ EqualSid (int /*<<< orphan*/ *,void*) ; 
 void* FALSE ; 
 int GetKernelObjectSecurity (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetSecurityDescriptorDacl (int /*<<< orphan*/ *,int*,void**,int*) ; 
 int GetSecurityDescriptorOwner (int /*<<< orphan*/ *,void**,int*) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OWNER_SECURITY_INFORMATION ; 
 scalar_t__ SECURITY_DESCRIPTOR_MIN_LENGTH ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetAce (void*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void test_default_dacl_owner_sid(void)
{
    HANDLE handle;
    BOOL ret, defaulted, present, found;
    DWORD size, index;
    SECURITY_DESCRIPTOR *sd;
    SECURITY_ATTRIBUTES sa;
    PSID owner;
    ACL *dacl;
    ACCESS_ALLOWED_ACE *ace;

    sd = HeapAlloc( GetProcessHeap(), 0, SECURITY_DESCRIPTOR_MIN_LENGTH );
    ret = InitializeSecurityDescriptor( sd, SECURITY_DESCRIPTOR_REVISION );
    ok( ret, "error %u\n", GetLastError() );

    sa.nLength              = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = sd;
    sa.bInheritHandle       = FALSE;
    handle = CreateEventA( &sa, TRUE, TRUE, "test_event" );
    ok( handle != NULL, "error %u\n", GetLastError() );

    size = 0;
    ret = GetKernelObjectSecurity( handle, OWNER_SECURITY_INFORMATION|DACL_SECURITY_INFORMATION, NULL, 0, &size );
    ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER, "error %u\n", GetLastError() );

    sd = HeapAlloc( GetProcessHeap(), 0, size );
    ret = GetKernelObjectSecurity( handle, OWNER_SECURITY_INFORMATION|DACL_SECURITY_INFORMATION, sd, size, &size );
    ok( ret, "error %u\n", GetLastError() );

    owner = (void *)0xdeadbeef;
    defaulted = TRUE;
    ret = GetSecurityDescriptorOwner( sd, &owner, &defaulted );
    ok( ret, "error %u\n", GetLastError() );
    ok( owner != (void *)0xdeadbeef, "owner not set\n" );
    ok( !defaulted, "owner defaulted\n" );

    dacl = (void *)0xdeadbeef;
    present = FALSE;
    defaulted = TRUE;
    ret = GetSecurityDescriptorDacl( sd, &present, &dacl, &defaulted );
    ok( ret, "error %u\n", GetLastError() );
    ok( present, "dacl not present\n" );
    ok( dacl != (void *)0xdeadbeef, "dacl not set\n" );
    ok( !defaulted, "dacl defaulted\n" );

    index = 0;
    found = FALSE;
    while (pGetAce( dacl, index++, (void **)&ace ))
    {
        if (EqualSid( &ace->SidStart, owner )) found = TRUE;
    }
    ok( found, "owner sid not found in dacl\n" );

    HeapFree( GetProcessHeap(), 0, sa.lpSecurityDescriptor );
    HeapFree( GetProcessHeap(), 0, sd );
    CloseHandle( handle );
}