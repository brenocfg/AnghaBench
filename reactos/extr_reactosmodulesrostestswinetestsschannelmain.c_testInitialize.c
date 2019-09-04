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
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * PSECPKG_USER_FUNCTION_TABLE ;
typedef  int /*<<< orphan*/ * PSECPKG_FUNCTION_TABLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int SECPKG_INTERFACE_VERSION ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pSpLsaModeInitialize (int,int*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  pSpUserModeInitialize (int,int*,int /*<<< orphan*/ **,int*) ; 

__attribute__((used)) static void testInitialize(void)
{
    PSECPKG_USER_FUNCTION_TABLE pUserTables, pUserTables2;
    PSECPKG_FUNCTION_TABLE pTables, pTables2;
    ULONG cTables = 0, cUserTables = 0, Version = 0;
    NTSTATUS status;

    /* Passing NULL into one of the parameters of SpLsaModeInitialize or
       SpUserModeInitialize causes a crash. */

    /* SpLsaModeInitialize does not care about the LSA version. */
    status = pSpLsaModeInitialize(0, &Version, &pTables2, &cTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(cTables == 2 ||
       broken(cTables == 1), /* Win2k */
       "cTables: %d\n", cTables);
    ok(pTables2 != NULL,"pTables: %p\n", pTables2);

    /* We can call it as many times we want. */
    status = pSpLsaModeInitialize(0x10000, &Version, &pTables, &cTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(cTables == 2 ||
       broken(cTables == 1), /* Win2k */
       "cTables: %d\n", cTables);
    ok(pTables != NULL, "pTables: %p\n", pTables);
    /* It will always return the same pointer. */
    ok(pTables == pTables2, "pTables: %p, pTables2: %p\n", pTables, pTables2);

    status = pSpLsaModeInitialize(0x23456, &Version, &pTables, &cTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(cTables == 2 ||
       broken(cTables == 1), /* Win2k */
       "cTables: %d\n", cTables);
    ok(pTables != NULL, "pTables: %p\n", pTables);
    ok(pTables == pTables2, "pTables: %p, pTables2: %p\n", pTables, pTables2);

    /* Bad versions to SpUserModeInitialize. Parameters unchanged */
    Version = 0xdead;
    cUserTables = 0xdead;
    pUserTables = NULL;
    status = pSpUserModeInitialize(0, &Version, &pUserTables, &cUserTables);
    ok(status == STATUS_INVALID_PARAMETER, "status: 0x%x\n", status);
    ok(Version == 0xdead, "Version: 0x%x\n", Version);
    ok(cUserTables == 0xdead, "cTables: %d\n", cUserTables);
    ok(pUserTables == NULL, "pUserTables: %p\n", pUserTables);

    status = pSpUserModeInitialize(0x20000, &Version, &pUserTables,
                                   &cUserTables);
    ok(status == STATUS_INVALID_PARAMETER, "status: 0x%x\n", status);
    ok(Version == 0xdead, "Version: 0x%x\n", Version);
    ok(cUserTables == 0xdead, "cTables: %d\n", cUserTables);
    ok(pUserTables == NULL, "pUserTables: %p\n", pUserTables);

    /* Good version to SpUserModeInitialize */
    status = pSpUserModeInitialize(SECPKG_INTERFACE_VERSION, &Version,
                                   &pUserTables, &cUserTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(Version == SECPKG_INTERFACE_VERSION, "Version: 0x%x\n", Version);
    ok(cUserTables == 2 ||
       broken(cUserTables == 4), /* Win2k */
       "cUserTables: %d\n", cUserTables);
    ok(pUserTables != NULL, "pUserTables: %p\n", pUserTables);

    /* Initializing user again */
    status = pSpUserModeInitialize(SECPKG_INTERFACE_VERSION, &Version,
                                   &pUserTables2, &cTables);
    ok(status == STATUS_SUCCESS, "status: 0x%x\n", status);
    ok(pUserTables == pUserTables2, "pUserTables: %p, pUserTables2: %p\n",
       pUserTables, pUserTables2);
}