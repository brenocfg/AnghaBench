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
typedef  int /*<<< orphan*/  guid ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  GUID_DATABASE_DRIVERS ; 
 int /*<<< orphan*/  GUID_DATABASE_MSI ; 
 int /*<<< orphan*/  GUID_DATABASE_SHIM ; 
 int /*<<< orphan*/  GUID_NULL ; 
 int /*<<< orphan*/  IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  pSdbGetStandardDatabaseGUID (int,int /*<<< orphan*/ *) ; 
 scalar_t__ pSdbIsNullGUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_UserAssist ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GuidFunctions(void)
{
    GUID guid;
    ok(pSdbIsNullGUID(&GUID_NULL), "expected GUID_NULL to be recognized as NULL GUID\n");
    ok(pSdbIsNullGUID(NULL), "expected NULL to be recognized as NULL GUID\n");
    ok(pSdbIsNullGUID(&test_UserAssist) == 0, "expected a set GUID not to be recognized as NULL GUID\n");

    memset(&guid, 0, sizeof(guid));
    ok(pSdbGetStandardDatabaseGUID(0, &guid) == 0,"Expected SdbGetStandardDatabaseGUID to fail\n");
    ok(IsEqualGUID(&GUID_NULL, &guid), "Expected guid not to be changed\n");

    ok(pSdbGetStandardDatabaseGUID(0x80020000, NULL),"Expected SdbGetStandardDatabaseGUID to succeed\n");

    memset(&guid, 0, sizeof(guid));
    ok(pSdbGetStandardDatabaseGUID(0x80020000, &guid),"Expected SdbGetStandardDatabaseGUID to succeed\n");
    ok(IsEqualGUID(&GUID_DATABASE_MSI, &guid), "Expected guid to equal GUID_DATABASE_MSI, was: %s\n", wine_dbgstr_guid(&guid));

    memset(&guid, 0, sizeof(guid));
    ok(pSdbGetStandardDatabaseGUID(0x80030000, &guid),"Expected SdbGetStandardDatabaseGUID to succeed\n");
    ok(IsEqualGUID(&GUID_DATABASE_SHIM, &guid), "Expected guid to equal GUID_DATABASE_SHIM, was: %s\n", wine_dbgstr_guid(&guid));

    memset(&guid, 0, sizeof(guid));
    ok(pSdbGetStandardDatabaseGUID(0x80040000, &guid),"Expected SdbGetStandardDatabaseGUID to succeed\n");
    ok(IsEqualGUID(&GUID_DATABASE_DRIVERS, &guid), "Expected guid to equal GUID_DATABASE_DRIVERS, was: %s\n", wine_dbgstr_guid(&guid));
}