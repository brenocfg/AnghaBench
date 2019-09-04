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
typedef  int INT ;

/* Variables and functions */
 int ERROR_SUCCESS ; 
 int MSI_NULL_INTEGER ; 
 int /*<<< orphan*/  MsiCloseHandle (scalar_t__) ; 
 scalar_t__ MsiCreateRecord (int) ; 
 int MsiRecordGetInteger (scalar_t__,int) ; 
 int MsiRecordSetStringA (scalar_t__,int,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_MsiRecordGetInteger(void)
{
    MSIHANDLE rec;
    INT val;
    UINT r;

    rec = MsiCreateRecord(1);
    ok(rec != 0, "Expected a valid handle\n");

    r = MsiRecordSetStringA(rec, 1, "5");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(rec, 1);
    ok(val == 5, "Expected 5, got %d\n", val);

    r = MsiRecordSetStringA(rec, 1, "-5");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(rec, 1);
    ok(val == -5, "Expected -5, got %d\n", val);

    r = MsiRecordSetStringA(rec, 1, "5apple");
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", r);

    val = MsiRecordGetInteger(rec, 1);
    ok(val == MSI_NULL_INTEGER, "Expected MSI_NULL_INTEGER, got %d\n", val);

    MsiCloseHandle(rec);
}