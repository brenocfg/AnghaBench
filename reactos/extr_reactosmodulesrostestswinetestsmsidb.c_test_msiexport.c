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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  DeleteFileW (int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSIDBOPEN_CREATE ; 
 scalar_t__ MsiCloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiDatabaseExportA (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ MsiDatabaseOpenViewA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiOpenDatabaseW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MsiViewClose (int /*<<< orphan*/ ) ; 
 scalar_t__ MsiViewExecute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char const*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* msifile ; 
 int /*<<< orphan*/  msifileW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void test_msiexport(void)
{
    MSIHANDLE hdb = 0, hview = 0;
    UINT r;
    const char *query;
    char path[MAX_PATH];
    const char file[] = "phone.txt";
    HANDLE handle;
    char buffer[0x100];
    DWORD length;
    const char expected[] =
        "id\tname\tnumber\r\n"
        "I2\tS32\tS32\r\n"
        "phone\tid\r\n"
        "1\tAbe\t8675309\r\n";

    DeleteFileW(msifileW);

    /* just MsiOpenDatabase should not create a file */
    r = MsiOpenDatabaseW(msifileW, MSIDBOPEN_CREATE, &hdb);
    ok(r == ERROR_SUCCESS, "MsiOpenDatabase failed\n");

    /* create a table */
    query = "CREATE TABLE `phone` ( "
            "`id` INT, `name` CHAR(32), `number` CHAR(32) "
            "PRIMARY KEY `id`)";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    /* insert a value into it */
    query = "INSERT INTO `phone` ( `id`, `name`, `number` )"
        "VALUES('1', 'Abe', '8675309')";
    r = MsiDatabaseOpenViewA(hdb, query, &hview);
    ok(r == ERROR_SUCCESS, "MsiDatabaseOpenView failed\n");
    r = MsiViewExecute(hview, 0);
    ok(r == ERROR_SUCCESS, "MsiViewExecute failed\n");
    r = MsiViewClose(hview);
    ok(r == ERROR_SUCCESS, "MsiViewClose failed\n");
    r = MsiCloseHandle(hview);
    ok(r == ERROR_SUCCESS, "MsiCloseHandle failed\n");

    GetCurrentDirectoryA(MAX_PATH, path);

    r = MsiDatabaseExportA(hdb, "phone", path, file);
    ok(r == ERROR_SUCCESS, "MsiDatabaseExport failed\n");

    MsiCloseHandle(hdb);

    lstrcatA(path, "\\");
    lstrcatA(path, file);

    /* check the data that was written */
    length = 0;
    memset(buffer, 0, sizeof buffer);
    handle = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (handle != INVALID_HANDLE_VALUE)
    {
        ReadFile(handle, buffer, sizeof buffer, &length, NULL);
        CloseHandle(handle);
        DeleteFileA(path);
    }
    else
        ok(0, "failed to open file %s\n", path);

    ok( length == strlen(expected), "length of data wrong\n");
    ok( !lstrcmpA(buffer, expected), "data doesn't match\n");
    DeleteFileA(msifile);
}