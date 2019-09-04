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
typedef  int /*<<< orphan*/  UINT ;
typedef  int MSIHANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_INSTALL_PACKAGE_REJECTED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  MsiCloseHandle (int) ; 
 int MsiCreateRecord (int) ; 
 int /*<<< orphan*/  MsiFormatRecordA (int,int,char*,int*) ; 
 int /*<<< orphan*/  MsiRecordSetStringA (int,int,char*) ; 
 int /*<<< orphan*/  MsiSetPropertyA (int,char*,char*) ; 
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  create_package_db () ; 
 int /*<<< orphan*/  msifile ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  package_from_db (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_formatrecord2(void)
{
    MSIHANDLE hpkg, hrec ;
    char buffer[0x100];
    DWORD sz;
    UINT r;

    r = package_from_db(create_package_db(), &hpkg);
    if (r == ERROR_INSTALL_PACKAGE_REJECTED)
    {
        skip("Not enough rights to perform tests\n");
        DeleteFileA(msifile);
        return;
    }
    ok( r == ERROR_SUCCESS, "failed to create package %u\n", r);

    r = MsiSetPropertyA(hpkg, "Manufacturer", " " );
    ok( r == ERROR_SUCCESS, "set property failed\n");

    hrec = MsiCreateRecord(2);
    ok(hrec, "create record failed\n");

    r = MsiRecordSetStringA( hrec, 0, "[ProgramFilesFolder][Manufacturer]\\asdf");
    ok( r == ERROR_SUCCESS, "format record failed\n");

    buffer[0] = 0;
    sz = sizeof buffer;
    r = MsiFormatRecordA( hpkg, hrec, buffer, &sz );
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);

    r = MsiRecordSetStringA(hrec, 0, "[foo][1]");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    r = MsiRecordSetStringA(hrec, 1, "hoo");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 3, "size wrong\n");
    ok( 0 == strcmp(buffer,"hoo"), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    r = MsiRecordSetStringA(hrec, 0, "x[~]x");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 3, "size wrong\n");
    ok( 0 == strcmp(buffer,"x"), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    r = MsiRecordSetStringA(hrec, 0, "[foo.$%}][1]");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    r = MsiRecordSetStringA(hrec, 1, "hoo");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 3, "size wrong\n");
    ok( 0 == strcmp(buffer,"hoo"), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    r = MsiRecordSetStringA(hrec, 0, "[\\[]");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 1, "size wrong\n");
    ok( 0 == strcmp(buffer,"["), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    SetEnvironmentVariableA("FOO", "BAR");
    r = MsiRecordSetStringA(hrec, 0, "[%FOO]");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 3, "size wrong\n");
    ok( 0 == strcmp(buffer,"BAR"), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    r = MsiRecordSetStringA(hrec, 0, "[[1]]");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    r = MsiRecordSetStringA(hrec, 1, "%FOO");
    ok( r == ERROR_SUCCESS, "Expected ERROR_SUCCESS got %d\n", r);
    sz = sizeof buffer;
    r = MsiFormatRecordA(hpkg, hrec, buffer, &sz);
    ok( sz == 3, "size wrong\n");
    ok( 0 == strcmp(buffer,"BAR"), "wrong output %s\n",buffer);
    ok( r == ERROR_SUCCESS, "format failed\n");

    MsiCloseHandle( hrec );
    MsiCloseHandle( hpkg );
    DeleteFileA(msifile);
}