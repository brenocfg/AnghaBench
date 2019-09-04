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
 char* _strtime (char*) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int p_strtime_s (char*,int) ; 
 int sscanf (char*,char*,int*,int*,int*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_strtime(void)
{
    char time[16], * result;
    int hour, minute, second, count, len;
    errno_t err;

    result = _strtime(time);
    ok(result == time, "Wrong return value\n");
    len = strlen(time);
    ok(len == 8, "Wrong length: returned %d, should be 8\n", len);
    count = sscanf(time, "%02d:%02d:%02d", &hour, &minute, &second);
    ok(count == 3, "Wrong format: count = %d, should be 3\n", count);

    if(!p_strtime_s) {
        win_skip("Skipping _strtime_s tests\n");
        return;
    }

    errno = 0;
    err = p_strtime_s(NULL, 0);
    ok(err == EINVAL, "err = %d\n", err);
    ok(errno == EINVAL, "errno = %d\n", errno);

    err = p_strtime_s(NULL, 1);
    ok(err == EINVAL, "err = %d\n", err);
    ok(errno == EINVAL, "errno = %d\n", errno);

    time[0] = 'x';
    err = p_strtime_s(time, 8);
    ok(err == ERANGE, "err = %d\n", err);
    ok(errno == ERANGE, "errno = %d\n", errno);
    ok(time[0] == '\0', "time[0] != '\\0'\n");

    err = p_strtime_s(time, 9);
    ok(err == 0, "err = %x\n", err);
}