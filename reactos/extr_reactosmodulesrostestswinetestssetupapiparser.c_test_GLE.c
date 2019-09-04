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
typedef  int LONG ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/ * HINF ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_LINE_NOT_FOUND ; 
 int ERROR_SECTION_NOT_FOUND ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int MAX_INF_STRING_LENGTH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseInfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindFirstLineA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupFindNextMatchLineA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetLineByIndexA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int SetupGetLineCountA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SetupGetLineTextA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * test_file_contents (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GLE(void)
{
    static const char *inf =
        "[Version]\n"
        "Signature=\"$Windows NT$\"\n"
        "[Sectionname]\n"
        "Keyname1=Field1,Field2,Field3\n"
        "\n"
        "Keyname2=Field4,Field5\n";
    HINF hinf;
    UINT err;
    INFCONTEXT context;
    BOOL retb;
    LONG retl;
    char buf[MAX_INF_STRING_LENGTH];
    int bufsize = MAX_INF_STRING_LENGTH;
    DWORD retsize;

    hinf = test_file_contents( inf, &err );
    ok( hinf != NULL, "Expected valid INF file\n" );

    SetLastError(0xdeadbeef);
    retb = SetupFindFirstLineA( hinf, "ImNotThere", NULL, &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindFirstLineA( hinf, "ImNotThere", "ImNotThere", &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindFirstLineA( hinf, "Sectionname", NULL, &context );
    ok(retb, "Expected success\n");
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindFirstLineA( hinf, "Sectionname", "ImNotThere", &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindFirstLineA( hinf, "Sectionname", "Keyname1", &context );
    ok(retb, "Expected success\n");
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindNextMatchLineA( &context, "ImNotThere", &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupFindNextMatchLineA( &context, "Keyname2", &context );
    ok(retb, "Expected success\n");
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retl = SetupGetLineCountA( hinf, "ImNotThere");
    ok(retl == -1, "Expected -1, got %d\n", retl);
    ok(GetLastError() == ERROR_SECTION_NOT_FOUND,
        "Expected ERROR_SECTION_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retl = SetupGetLineCountA( hinf, "Sectionname");
    ok(retl == 2, "Expected 2, got %d\n", retl);
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineTextA( NULL, hinf, "ImNotThere", "ImNotThere", buf, bufsize, &retsize);
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineTextA( NULL, hinf, "Sectionname", "ImNotThere", buf, bufsize, &retsize);
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineTextA( NULL, hinf, "Sectionname", "Keyname1", buf, bufsize, &retsize);
    ok(retb, "Expected success\n");
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineByIndexA( hinf, "ImNotThere", 1, &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineByIndexA( hinf, "Sectionname", 1, &context );
    ok(retb, "Expected success\n");
    ok(GetLastError() == ERROR_SUCCESS,
        "Expected ERROR_SUCCESS, got %08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    retb = SetupGetLineByIndexA( hinf, "Sectionname", 3, &context );
    ok(!retb, "Expected failure\n");
    ok(GetLastError() == ERROR_LINE_NOT_FOUND,
        "Expected ERROR_LINE_NOT_FOUND, got %08x\n", GetLastError());

    SetupCloseInfFile( hinf );
}