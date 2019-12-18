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
typedef  int UINT ;

/* Variables and functions */
 int GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 scalar_t__ lstrcmpA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_GetWindowsDirectoryA(void)
{
    UINT len, len_with_null;
    char buf[MAX_PATH];

    len_with_null = GetWindowsDirectoryA(NULL, 0);
    ok(len_with_null <= MAX_PATH, "should fit into MAX_PATH\n");

    lstrcpyA(buf, "foo");
    len_with_null = GetWindowsDirectoryA(buf, 1);
    ok(lstrcmpA(buf, "foo") == 0, "should not touch the buffer\n");

    lstrcpyA(buf, "foo");
    len = GetWindowsDirectoryA(buf, len_with_null - 1);
    ok(lstrcmpA(buf, "foo") == 0, "should not touch the buffer\n");
    ok(len == len_with_null, "GetWindowsDirectoryW returned %d, expected %d\n",
       len, len_with_null);

    lstrcpyA(buf, "foo");
    len = GetWindowsDirectoryA(buf, len_with_null);
    ok(lstrcmpA(buf, "foo") != 0, "should touch the buffer\n");
    ok(len == strlen(buf), "returned length should be equal to the length of string\n");
    ok(len == len_with_null-1, "GetWindowsDirectoryA returned %d, expected %d\n",
       len, len_with_null-1);
}