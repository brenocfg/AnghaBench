#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_9__ {int (* GetInfo ) (TYPE_1__*) ;} ;
struct TYPE_8__ {int fCapabilities; int wVersion; int wRPCID; int cbMaxToken; } ;
typedef  TYPE_1__ SecPkgInfoW ;
typedef  TYPE_2__* PSECPKG_FUNCTION_TABLE ;
typedef  int NTSTATUS ;

/* Variables and functions */
 int LSA_BASE_CAPS ; 
 int SECPKG_FLAG_APPCONTAINER_PASSTHROUGH ; 
 int SEC_E_UNSUPPORTED_FUNCTION ; 
 int STATUS_SUCCESS ; 
 scalar_t__ SUCCEEDED (int) ; 
 TYPE_2__* getNextSecPkgTable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pSpLsaModeInitialize (int /*<<< orphan*/ ,int*,TYPE_2__**,int*) ; 
 int stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void testGetInfo(void)
{
    PSECPKG_FUNCTION_TABLE pTables;
    SecPkgInfoW PackageInfo;
    ULONG cTables, Version;
    NTSTATUS status;

    /* Get the dispatch table */
    status = pSpLsaModeInitialize(0, &Version, &pTables, &cTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);

    /* Passing NULL into ->GetInfo causes a crash. */

    /* First package: Unified */
    status = pTables->GetInfo(&PackageInfo);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(PackageInfo.fCapabilities == LSA_BASE_CAPS ||
       PackageInfo.fCapabilities == (LSA_BASE_CAPS|SECPKG_FLAG_APPCONTAINER_PASSTHROUGH),
       "fCapabilities: 0x%x\n", PackageInfo.fCapabilities);
    ok(PackageInfo.wVersion == 1, "wVersion: %d\n", PackageInfo.wVersion);
    ok(PackageInfo.wRPCID == 14, "wRPCID: %d\n", PackageInfo.wRPCID);
    ok(PackageInfo.cbMaxToken == 0x4000 ||
       PackageInfo.cbMaxToken == 0x6000, /* Vista */
       "cbMaxToken: 0x%x\n",
       PackageInfo.cbMaxToken);

    /* Second package */
    if (cTables == 1)
    {
        win_skip("Second package missing\n");
        return;
    }
    pTables = getNextSecPkgTable(pTables, Version);
    if (!pTables)
        return;
    if (!pTables->GetInfo)
    {
        win_skip("GetInfo function missing\n");
        return;
    }
    status = pTables->GetInfo(&PackageInfo);
    ok(SUCCEEDED(status) ||
       status == SEC_E_UNSUPPORTED_FUNCTION, /* win2k3 */
       "status: 0x%x\n", status);

    if (SUCCEEDED(status))
    {
        ok(PackageInfo.fCapabilities == LSA_BASE_CAPS ||
           PackageInfo.fCapabilities == (LSA_BASE_CAPS|SECPKG_FLAG_APPCONTAINER_PASSTHROUGH),
           "fCapabilities: 0x%x\n", PackageInfo.fCapabilities);
        ok(PackageInfo.wVersion == 1, "wVersion: %d\n", PackageInfo.wVersion);
        ok(PackageInfo.wRPCID == 14, "wRPCID: %d\n", PackageInfo.wRPCID);
        ok(PackageInfo.cbMaxToken == 0x4000 ||
           PackageInfo.cbMaxToken == 0x6000, /* Win7 */
           "cbMaxToken: 0x%x\n",
           PackageInfo.cbMaxToken);
    }
}