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

/* Variables and functions */
 int DeleteFileA (char*) ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 

__attribute__((used)) static void tear_down_case_test(const char *testdir)
{
    int ret;
    char buf[MAX_PATH];

    sprintf(buf, "%s\\%s", testdir, "TesT");
    ret = DeleteFileA(buf);
    ok(ret || (GetLastError() == ERROR_PATH_NOT_FOUND),
       "Failed to rm %s, error %d\n", buf, GetLastError());
    RemoveDirectoryA(testdir);
}