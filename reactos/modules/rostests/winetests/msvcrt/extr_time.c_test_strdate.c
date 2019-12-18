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
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 char* _strdate (char*) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_strdate_s (char*,int) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strdate(void)
{
    char date[16], * result;
    int month, day, year, count, len;
    errno_t err;

    result = _strdate(date);
    ok(result == date, "Wrong return value\n");
    len = strlen(date);
    ok(len == 8, "Wrong length: returned %d, should be 8\n", len);
    count = sscanf(date, "%02d/%02d/%02d", &month, &day, &year);
    ok(count == 3, "Wrong format: count = %d, should be 3\n", count);

    if(!p_strdate_s) {
        win_skip("Skipping _strdate_s tests\n");
        return;
    }

    errno = 0;
    err = p_strdate_s(NULL, 1);
    ok(err == EINVAL, "err = %d\n", err);
    ok(errno == EINVAL, "errno = %d\n", errno);

    date[0] = 'x';
    date[1] = 'x';
    err = p_strdate_s(date, 8);
    ok(err == ERANGE, "err = %d\n", err);
    ok(errno == ERANGE, "errno = %d\n", errno);
    ok(date[0] == '\0', "date[0] != '\\0'\n");
    ok(date[1] == 'x', "date[1] != 'x'\n");

    err = p_strdate_s(date, 9);
    ok(err == 0, "err = %x\n", err);
}