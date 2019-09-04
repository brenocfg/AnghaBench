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
typedef  int /*<<< orphan*/  DWORDLONG ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_PATH_NOT_FOUND ; 
 int GetDiskInfoA (char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ old_ie ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void test_GetDiskInfoA(void)
{
    BOOL ret;
    DWORD error, cluster_size;
    DWORDLONG free, total;
    char path[MAX_PATH], *p;

    GetSystemDirectoryA(path, MAX_PATH);
    if ((p = strchr(path, '\\'))) *++p = 0;

    ret = GetDiskInfoA(path, &cluster_size, &free, &total);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, &cluster_size, &free, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, &cluster_size, NULL, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    ret = GetDiskInfoA(path, NULL, NULL, NULL);
    ok(ret, "GetDiskInfoA failed %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    strcpy(p, "\\non\\existing\\path");
    ret = GetDiskInfoA(path, NULL, NULL, NULL);
    error = GetLastError();
    ok(!ret ||
       broken(old_ie && ret), /* < IE7 */
       "GetDiskInfoA succeeded\n");
    ok(error == ERROR_PATH_NOT_FOUND ||
       broken(old_ie && error == 0xdeadbeef), /* < IE7 */
       "got %u expected ERROR_PATH_NOT_FOUND\n", error);

    SetLastError(0xdeadbeef);
    ret = GetDiskInfoA(NULL, NULL, NULL, NULL);
    error = GetLastError();
    ok(!ret, "GetDiskInfoA succeeded\n");
    ok(error == ERROR_INVALID_PARAMETER, "got %u expected ERROR_INVALID_PARAMETER\n", error);
}