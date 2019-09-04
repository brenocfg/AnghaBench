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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_DIRECT ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSummaryInfoPersist (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiSummaryInfoSetPropertyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PID_WORDCOUNT ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void set_admin_summary_info(const WCHAR *name)
{
    MSIHANDLE db, summary;
    UINT r;

    r = MsiOpenDatabaseW(name, MSIDBOPEN_DIRECT, &db);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    r = MsiGetSummaryInformationA(db, NULL, 1, &summary);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    r = MsiSummaryInfoSetPropertyA(summary, PID_WORDCOUNT, VT_I4, 5, NULL, NULL);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    /* write the summary changes back to the stream */
    r = MsiSummaryInfoPersist(summary);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    MsiCloseHandle(summary);

    r = MsiDatabaseCommit(db);
    ok(r == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %u\n", r);

    MsiCloseHandle(db);
}