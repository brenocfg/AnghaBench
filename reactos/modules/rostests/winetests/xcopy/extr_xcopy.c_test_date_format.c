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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int runcmd (char*) ; 

__attribute__((used)) static void test_date_format(void)
{
    DWORD rc;

    rc = runcmd("xcopy /D:20-01-2000 xcopy1 xcopytest");
    ok(rc == 4, "xcopy /D:d-m-y test returned rc=%u\n", rc);
    ok(GetFileAttributesA("xcopytest\\xcopy1") == INVALID_FILE_ATTRIBUTES,
       "xcopy should not have created xcopytest\\xcopy1\n");

    rc = runcmd("xcopy /D:01-20-2000 xcopy1 xcopytest");
    ok(rc == 0, "xcopy /D:m-d-y test failed rc=%u\n", rc);
    ok(GetFileAttributesA("xcopytest\\xcopy1") != INVALID_FILE_ATTRIBUTES,
       "xcopy did not create xcopytest\\xcopy1\n");
    DeleteFileA("xcopytest\\xcopy1");

    rc = runcmd("xcopy /D:1-20-2000 xcopy1 xcopytest");
    ok(rc == 0, "xcopy /D:m-d-y test failed rc=%u\n", rc);
    ok(GetFileAttributesA("xcopytest\\xcopy1") != INVALID_FILE_ATTRIBUTES,
       "xcopy did not create xcopytest\\xcopy1\n");
    DeleteFileA("xcopytest\\xcopy1");
}