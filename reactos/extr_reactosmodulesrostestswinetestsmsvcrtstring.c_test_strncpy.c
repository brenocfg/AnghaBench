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
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char* strncpy (char*,char*,int) ; 

__attribute__((used)) static void test_strncpy(void)
{
#define TEST_STRNCPY_LEN 10
    char *ret;
    char dst[TEST_STRNCPY_LEN + 1];
    char not_null_terminated[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    /* strlen(src) > TEST_STRNCPY_LEN */
    ret = strncpy(dst, "01234567890123456789", TEST_STRNCPY_LEN);
    ok(ret == dst, "ret != dst\n");
    ok(!strncmp(dst, "0123456789", TEST_STRNCPY_LEN), "dst != 0123456789\n");

    /* without null-terminated */
    ret = strncpy(dst, not_null_terminated, TEST_STRNCPY_LEN);
    ok(ret == dst, "ret != dst\n");
    ok(!strncmp(dst, "0123456789", TEST_STRNCPY_LEN), "dst != 0123456789\n");

    /* strlen(src) < TEST_STRNCPY_LEN */
    strcpy(dst, "0123456789");
    ret = strncpy(dst, "012345", TEST_STRNCPY_LEN);
    ok(ret == dst, "ret != dst\n");
    ok(!strcmp(dst, "012345"), "dst != 012345\n");
    ok(dst[TEST_STRNCPY_LEN - 1] == '\0', "dst[TEST_STRNCPY_LEN - 1] != 0\n");

    /* strlen(src) == TEST_STRNCPY_LEN */
    ret = strncpy(dst, "0123456789", TEST_STRNCPY_LEN);
    ok(ret == dst, "ret != dst\n");
    ok(!strncmp(dst, "0123456789", TEST_STRNCPY_LEN), "dst != 0123456789\n");
}