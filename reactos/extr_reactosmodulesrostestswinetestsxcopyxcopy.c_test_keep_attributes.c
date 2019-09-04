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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int FILE_ATTRIBUTE_READONLY ; 
 int GetFileAttributesA (char*) ; 
 int /*<<< orphan*/  SetFileAttributesA (char*,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ runcmd (char*) ; 

__attribute__((used)) static void test_keep_attributes(void)
{
    DWORD rc;

    SetFileAttributesA("xcopy1", FILE_ATTRIBUTE_READONLY);

    rc = runcmd("xcopy xcopy1 xcopytest");
    ok(rc == 0, "xcopy failed to copy read only file\n");
    ok((GetFileAttributesA("xcopytest\\xcopy1") & FILE_ATTRIBUTE_READONLY) != FILE_ATTRIBUTE_READONLY,
       "xcopy should not have copied file permissions\n");
    SetFileAttributesA("xcopytest\\xcopy1", FILE_ATTRIBUTE_NORMAL);
    DeleteFileA("xcopytest\\xcopy1");

    rc = runcmd("xcopy /K xcopy1 xcopytest");
    ok(rc == 0, "xcopy failed to copy read only file with /k\n");
    ok((GetFileAttributesA("xcopytest\\xcopy1") & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY,
       "xcopy did not keep file permissions\n");
    SetFileAttributesA("xcopytest\\xcopy1", FILE_ATTRIBUTE_NORMAL);
    DeleteFileA("xcopytest\\xcopy1");

    SetFileAttributesA("xcopy1", FILE_ATTRIBUTE_NORMAL);

    }