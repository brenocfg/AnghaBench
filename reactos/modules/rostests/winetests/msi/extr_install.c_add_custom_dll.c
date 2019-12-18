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

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSIDBOPEN_TRANSACT ; 
 int /*<<< orphan*/  MsiCloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsiCreateRecord (int) ; 
 scalar_t__ MsiDatabaseCommit (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiRecordSetStreamA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  customdll ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ run_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void add_custom_dll(void)
{
    MSIHANDLE hdb = 0, record;
    UINT res;

    res = MsiOpenDatabaseW(msifileW, MSIDBOPEN_TRANSACT, &hdb);
    ok(res == ERROR_SUCCESS, "failed to open db: %u\n", res);

    res = run_query(hdb, 0, "CREATE TABLE `Binary` (`Name` CHAR(72) NOT NULL, `Data` OBJECT NOT NULL PRIMARY KEY `Name`)");
    ok(res == ERROR_SUCCESS, "failed to create Binary table: %u\n", res);

    record = MsiCreateRecord(1);
    res = MsiRecordSetStreamA(record, 1, customdll);
    ok(res == ERROR_SUCCESS, "failed to add %s to stream: %u\n", customdll, res);

    res = run_query(hdb, record, "INSERT INTO `Binary` (`Name`, `Data`) VALUES ('custom.dll', ?)");
    ok(res == ERROR_SUCCESS, "failed to insert into Binary table: %u\n", res);

    res = MsiDatabaseCommit(hdb);
    ok(res == ERROR_SUCCESS, "failed to commit database: %u\n", res);

    MsiCloseHandle(record);
    MsiCloseHandle(hdb);
}