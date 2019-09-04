#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ WCHAR ;
struct TYPE_6__ {scalar_t__* Buffer; int MaximumLength; int Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTORY_QUERY ; 
 int /*<<< orphan*/  DIR_TEST_CREATE_OPEN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_ALL ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_ACCESS_VIOLATION ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_INVALID ; 
 int /*<<< orphan*/  STATUS_OBJECT_NAME_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_OBJECT_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_OBJECT_PATH_SYNTAX_BAD ; 
 int /*<<< orphan*/  STATUS_OBJECT_TYPE_MISMATCH ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SYMBOLIC_LINK_QUERY ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pNtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateDirectoryObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtCreateMutant (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pNtOpenDirectoryObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtOpenEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtOpenSymbolicLinkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pNtQuerySymbolicLinkObject (int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pRtlCreateUnicodeStringFromAsciiz (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pRtlFreeUnicodeString (TYPE_1__*) ; 

__attribute__((used)) static void test_directory(void)
{
    NTSTATUS status;
    UNICODE_STRING str;
    OBJECT_ATTRIBUTES attr;
    HANDLE dir, dir1, h, h2;
    BOOL is_nt4;

    /* No name and/or no attributes */
    status = pNtCreateDirectoryObject(NULL, DIRECTORY_QUERY, &attr);
    ok(status == STATUS_ACCESS_VIOLATION || status == STATUS_INVALID_PARAMETER,
        "NtCreateDirectoryObject should have failed with STATUS_ACCESS_VIOLATION got(%08x)\n", status);
    status = pNtOpenDirectoryObject(NULL, DIRECTORY_QUERY, &attr);
    ok(status == STATUS_ACCESS_VIOLATION || status == STATUS_INVALID_PARAMETER,
        "NtOpenDirectoryObject should have failed with STATUS_ACCESS_VIOLATION got(%08x)\n", status);

    status = pNtCreateDirectoryObject(&h, DIRECTORY_QUERY, NULL);
    ok(status == STATUS_SUCCESS, "Failed to create Directory without attributes(%08x)\n", status);
    pNtClose(h);
    status = pNtOpenDirectoryObject(&h, DIRECTORY_QUERY, NULL);
    ok(status == STATUS_INVALID_PARAMETER,
        "NtOpenDirectoryObject should have failed with STATUS_INVALID_PARAMETER got(%08x)\n", status);

    InitializeObjectAttributes(&attr, NULL, 0, 0, NULL);
    status = pNtCreateDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_PATH_SYNTAX_BAD, "NtOpenDirectoryObject got %08x\n", status );

    /* Bad name */
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);

    pRtlCreateUnicodeStringFromAsciiz(&str, "");
    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    pNtClose(h);
    status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_PATH_SYNTAX_BAD, "NtOpenDirectoryObject got %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pNtClose(dir);

    DIR_TEST_CREATE_OPEN( "BaseNamedObjects", STATUS_OBJECT_PATH_SYNTAX_BAD );
    DIR_TEST_CREATE_OPEN( "\\BaseNamedObjects\\", STATUS_OBJECT_NAME_INVALID );
    DIR_TEST_CREATE_OPEN( "\\\\BaseNamedObjects", STATUS_OBJECT_NAME_INVALID );
    DIR_TEST_CREATE_OPEN( "\\BaseNamedObjects\\\\om.c-test", STATUS_OBJECT_NAME_INVALID );
    DIR_TEST_CREATE_OPEN( "\\BaseNamedObjects\\om.c-test\\", STATUS_OBJECT_PATH_NOT_FOUND );

    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\om.c-test");
    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    status = pNtOpenDirectoryObject( &dir1, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to open directory %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pNtClose(h);
    pNtClose(dir1);


    /* Use of root directory */

    /* Can't use symlinks as a directory */
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\Local");
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtOpenSymbolicLinkObject(&dir, SYMBOLIC_LINK_QUERY, &attr);
    is_nt4 = (status == STATUS_OBJECT_NAME_NOT_FOUND);  /* nt4 doesn't have Local\\ symlink */
    if (!is_nt4)
    {
        WCHAR buffer[256];
        ULONG len, full_len;

        ok(status == STATUS_SUCCESS, "Failed to open SymbolicLink(%08x)\n", status);
        pRtlFreeUnicodeString(&str);
        InitializeObjectAttributes(&attr, &str, 0, dir, NULL);
        pRtlCreateUnicodeStringFromAsciiz(&str, "one more level");
        status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_OBJECT_TYPE_MISMATCH, "NtCreateDirectoryObject got %08x\n", status );
        pRtlFreeUnicodeString(&str);

        pRtlCreateUnicodeStringFromAsciiz( &str, "\\BaseNamedObjects\\Local\\om.c-test" );
        InitializeObjectAttributes( &attr, &str, 0, 0, NULL );
        status = pNtCreateDirectoryObject( &dir1, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
        pRtlFreeUnicodeString( &str );
        pRtlCreateUnicodeStringFromAsciiz( &str, "om.c-test" );
        InitializeObjectAttributes( &attr, &str, 0, dir, NULL );
        status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_OBJECT_TYPE_MISMATCH, "Failed to open directory %08x\n", status );
        if (!status) pNtClose(h);
        pRtlFreeUnicodeString( &str );

        pRtlCreateUnicodeStringFromAsciiz( &str, "om.c-event" );
        InitializeObjectAttributes( &attr, &str, 0, dir1, NULL );
        status = pNtCreateEvent( &h, GENERIC_ALL, &attr, 1, 0 );
        ok( status == STATUS_SUCCESS, "NtCreateEvent failed %x\n", status );
        status = pNtOpenEvent( &h2, GENERIC_ALL, &attr );
        ok( status == STATUS_SUCCESS, "NtOpenEvent failed %x\n", status );
        pNtClose( h2 );
        pRtlFreeUnicodeString( &str );
        pRtlCreateUnicodeStringFromAsciiz( &str, "om.c-test\\om.c-event" );
        InitializeObjectAttributes( &attr, &str, 0, dir, NULL );
        status = pNtOpenEvent( &h2, GENERIC_ALL, &attr );
        ok( status == STATUS_OBJECT_TYPE_MISMATCH, "NtOpenEvent failed %x\n", status );
        pRtlFreeUnicodeString( &str );
        pRtlCreateUnicodeStringFromAsciiz( &str, "\\BasedNamedObjects\\Local\\om.c-test\\om.c-event" );
        InitializeObjectAttributes( &attr, &str, 0, 0, NULL );
        status = pNtOpenEvent( &h2, GENERIC_ALL, &attr );
        ok( status == STATUS_OBJECT_PATH_NOT_FOUND, "NtOpenEvent failed %x\n", status );
        pRtlFreeUnicodeString( &str );
        pNtClose( h );
        pNtClose( dir1 );

        str.Buffer = buffer;
        str.MaximumLength = sizeof(buffer);
        len = 0xdeadbeef;
        memset( buffer, 0xaa, sizeof(buffer) );
        status = pNtQuerySymbolicLinkObject( dir, &str, &len );
        ok( status == STATUS_SUCCESS, "NtQuerySymbolicLinkObject failed %08x\n", status );
        if (status != STATUS_SUCCESS)
            goto error;
        full_len = str.Length + sizeof(WCHAR);
        ok( len == full_len, "bad length %u/%u\n", len, full_len );
        if (len == full_len)
            ok( buffer[len / sizeof(WCHAR) - 1] == 0, "no terminating null\n" );

        str.MaximumLength = str.Length;
        len = 0xdeadbeef;
        status = pNtQuerySymbolicLinkObject( dir, &str, &len );
        ok( status == STATUS_BUFFER_TOO_SMALL, "NtQuerySymbolicLinkObject failed %08x\n", status );
        ok( len == full_len, "bad length %u/%u\n", len, full_len );

        str.MaximumLength = 0;
        len = 0xdeadbeef;
        status = pNtQuerySymbolicLinkObject( dir, &str, &len );
        ok( status == STATUS_BUFFER_TOO_SMALL, "NtQuerySymbolicLinkObject failed %08x\n", status );
        ok( len == full_len, "bad length %u/%u\n", len, full_len );

        str.MaximumLength = str.Length + sizeof(WCHAR);
        len = 0xdeadbeef;
        status = pNtQuerySymbolicLinkObject( dir, &str, &len );
        ok( status == STATUS_SUCCESS, "NtQuerySymbolicLinkObject failed %08x\n", status );
        ok( len == full_len, "bad length %u/%u\n", len, full_len );

error:
        pNtClose(dir);
    }

    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects");
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtOpenDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to open directory %08x\n", status );
    pRtlFreeUnicodeString(&str);

    InitializeObjectAttributes(&attr, NULL, 0, dir, NULL);
    status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_NAME_INVALID, "NtOpenDirectoryObject got %08x\n", status );

    InitializeObjectAttributes(&attr, &str, 0, dir, NULL);
    DIR_TEST_CREATE_OPEN( "", STATUS_SUCCESS );
    DIR_TEST_CREATE_OPEN( "\\", STATUS_OBJECT_PATH_SYNTAX_BAD );
    DIR_TEST_CREATE_OPEN( "\\om.c-test", STATUS_OBJECT_PATH_SYNTAX_BAD );
    DIR_TEST_CREATE_OPEN( "\\om.c-test\\", STATUS_OBJECT_PATH_SYNTAX_BAD );
    DIR_TEST_CREATE_OPEN( "om.c-test\\", STATUS_OBJECT_PATH_NOT_FOUND );

    pRtlCreateUnicodeStringFromAsciiz(&str, "om.c-test");
    status = pNtCreateDirectoryObject( &dir1, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to open directory %08x\n", status );
    pRtlFreeUnicodeString(&str);

    pNtClose(h);
    pNtClose(dir1);
    pNtClose(dir);

    /* Nested directories */
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\");
    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    status = pNtOpenDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to open directory %08x\n", status );
    InitializeObjectAttributes(&attr, &str, 0, dir, NULL);
    status = pNtOpenDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_OBJECT_PATH_SYNTAX_BAD, "NtOpenDirectoryObject got %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pNtClose(dir);

    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\om.c-test");
    status = pNtCreateDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\om.c-test\\one more level");
    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pNtClose(h);
    InitializeObjectAttributes(&attr, &str, 0, dir, NULL);
    pRtlCreateUnicodeStringFromAsciiz(&str, "one more level");
    status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
    pRtlFreeUnicodeString(&str);
    pNtClose(h);

    pNtClose(dir);

    if (!is_nt4)
    {
        InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
        pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\Global\\om.c-test");
        status = pNtCreateDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
        pRtlFreeUnicodeString(&str);
        pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects\\Local\\om.c-test\\one more level");
        status = pNtCreateDirectoryObject( &h, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
        pRtlFreeUnicodeString(&str);
        pNtClose(h);
        InitializeObjectAttributes(&attr, &str, 0, dir, NULL);
        pRtlCreateUnicodeStringFromAsciiz(&str, "one more level");
        status = pNtCreateDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
        ok( status == STATUS_SUCCESS, "Failed to create directory %08x\n", status );
        pRtlFreeUnicodeString(&str);
        pNtClose(h);
        pNtClose(dir);
    }

    /* Create other objects using RootDirectory */

    InitializeObjectAttributes(&attr, &str, 0, 0, NULL);
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\BaseNamedObjects");
    status = pNtOpenDirectoryObject( &dir, DIRECTORY_QUERY, &attr );
    ok( status == STATUS_SUCCESS, "Failed to open directory %08x\n", status );
    pRtlFreeUnicodeString(&str);
    InitializeObjectAttributes(&attr, &str, 0, dir, NULL);

    /* Test invalid paths */
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\om.c-mutant");
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_PATH_SYNTAX_BAD,
        "NtCreateMutant should have failed with STATUS_OBJECT_PATH_SYNTAX_BAD got(%08x)\n", status);
    pRtlFreeUnicodeString(&str);
    pRtlCreateUnicodeStringFromAsciiz(&str, "\\om.c-mutant\\");
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_PATH_SYNTAX_BAD,
        "NtCreateMutant should have failed with STATUS_OBJECT_PATH_SYNTAX_BAD got(%08x)\n", status);
    pRtlFreeUnicodeString(&str);

    pRtlCreateUnicodeStringFromAsciiz(&str, "om.c\\-mutant");
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_OBJECT_PATH_NOT_FOUND,
        "NtCreateMutant should have failed with STATUS_OBJECT_PATH_NOT_FOUND got(%08x)\n", status);
    pRtlFreeUnicodeString(&str);

    pRtlCreateUnicodeStringFromAsciiz(&str, "om.c-mutant");
    status = pNtCreateMutant(&h, GENERIC_ALL, &attr, FALSE);
    ok(status == STATUS_SUCCESS, "Failed to create Mutant(%08x)\n", status);
    pRtlFreeUnicodeString(&str);
    pNtClose(h);

    pNtClose(dir);
}