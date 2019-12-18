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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIHANDLE ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiGetSummaryInformationA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiSummaryInfoPersist (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiSummaryInfoSetPropertyA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int PID_REVNUMBER ; 
 int /*<<< orphan*/  VT_I4 ; 
 int /*<<< orphan*/  VT_LPSTR ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static UINT set_summary_info(MSIHANDLE hdb, LPSTR prodcode)
{
    UINT res;
    MSIHANDLE suminfo;

    /* build summary info */
    res = MsiGetSummaryInformationA(hdb, NULL, 7, &suminfo);
    ok(res == ERROR_SUCCESS, "Failed to open summaryinfo\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 2, VT_LPSTR, 0, NULL,
                                    "Installation Database");
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 3, VT_LPSTR, 0, NULL,
                                    "Installation Database");
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 4, VT_LPSTR, 0, NULL,
                                    "Wine Hackers");
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 7, VT_LPSTR, 0, NULL,
                                    ";1033");
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, PID_REVNUMBER, VT_LPSTR, 0, NULL,
                                    "{A2078D65-94D6-4205-8DEE-F68D6FD622AA}");
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 14, VT_I4, 100, NULL, NULL);
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoSetPropertyA(suminfo, 15, VT_I4, 0, NULL, NULL);
    ok(res == ERROR_SUCCESS, "Failed to set summary info\n");

    res = MsiSummaryInfoPersist(suminfo);
    ok(res == ERROR_SUCCESS, "Failed to make summary info persist\n");

    res = MsiCloseHandle(suminfo);
    ok(res == ERROR_SUCCESS, "Failed to close suminfo\n");

    return res;
}