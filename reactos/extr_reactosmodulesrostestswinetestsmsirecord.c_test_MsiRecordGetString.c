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
typedef  int UINT ;
typedef  scalar_t__ MSIHANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiRecordGetStringA (scalar_t__,int,int /*<<< orphan*/ *,int*) ; 
 int MsiRecordSetInteger (scalar_t__,int,int) ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_MsiRecordGetString(void)
{
    MSIHANDLE rec;
    CHAR buf[MAX_PATH];
    DWORD sz;
    UINT r;

    rec = MsiCreateRecord(2);
    ok(rec != 0, "Expected a valid handle\n");

    sz = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, NULL, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n",r);
    ok(sz == 0, "Expected 0, got %d\n",sz);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, ""), "Expected \"\", got \"%s\"\n", buf);
    ok(sz == 0, "Expected 0, got %d\n", sz);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 10, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, ""), "Expected \"\", got \"%s\"\n", buf);
    ok(sz == 0, "Expected 0, got %d\n", sz);

    MsiCloseHandle(rec);

    rec = MsiCreateRecord(1);
    ok(rec != 0, "Expected a valid handle\n");

    r = MsiRecordSetInteger(rec, 1, 5);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    r = MsiRecordGetStringA(rec, 1, NULL, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n",r);
    ok(sz == 1, "Expected 1, got %d\n",sz);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "5"), "Expected \"5\", got \"%s\"\n", buf);
    ok(sz == 1, "Expected 1, got %d\n", sz);

    r = MsiRecordSetInteger(rec, 1, -5);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    sz = MAX_PATH;
    lstrcpyA(buf, "apple");
    r = MsiRecordGetStringA(rec, 1, buf, &sz);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);
    ok(!lstrcmpA(buf, "-5"), "Expected \"-5\", got \"%s\"\n", buf);
    ok(sz == 2, "Expected 2, got %d\n", sz);

    MsiCloseHandle(rec);
}