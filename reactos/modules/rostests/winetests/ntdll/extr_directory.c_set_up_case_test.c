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
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryA (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,char const*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 

__attribute__((used)) static void set_up_case_test(const char *testdir)
{
    BOOL ret;
    char buf[MAX_PATH];
    HANDLE h;

    ret = CreateDirectoryA(testdir, NULL);
    ok(ret, "couldn't create dir '%s', error %d\n", testdir, GetLastError());

    sprintf(buf, "%s\\%s", testdir, "TesT");
    h = CreateFileA(buf, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL, 0);
    ok(h != INVALID_HANDLE_VALUE, "failed to create temp file '%s'\n", buf);
    CloseHandle(h);
}