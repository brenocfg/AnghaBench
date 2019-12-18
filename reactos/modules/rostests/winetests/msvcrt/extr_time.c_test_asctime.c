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
typedef  int time_t ;
struct tm {int tm_wday; int tm_yday; int tm_mday; int tm_year; int tm_mon; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ broken (int) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 char* p_asctime (struct tm*) ; 
 struct tm* p_gmtime (int*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_asctime(void)
{
    struct tm* gmt_tm;
    time_t gmt;
    char *ret;

    if(!p_asctime || !p_gmtime)
    {
        win_skip("asctime or gmtime is not available\n");
        return;
    }

    gmt = 0;
    gmt_tm = p_gmtime(&gmt);
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Thu Jan 01 00:00:00 1970\n"), "asctime returned %s\n", ret);

    gmt = 312433121;
    gmt_tm = p_gmtime(&gmt);
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Mon Nov 26 02:58:41 1979\n"), "asctime returned %s\n", ret);

    /* Week day is only checked if it's in 0..6 range */
    gmt_tm->tm_wday = 3;
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Wed Nov 26 02:58:41 1979\n"), "asctime returned %s\n", ret);

    errno = 0xdeadbeef;
    gmt_tm->tm_wday = 7;
    ret = p_asctime(gmt_tm);
    ok(!ret || broken(!ret[0]), "asctime returned %s\n", ret);
    ok(errno==EINVAL || broken(errno==0xdeadbeef), "errno = %d\n", errno);

    /* Year day is ignored */
    gmt_tm->tm_wday = 3;
    gmt_tm->tm_yday = 1300;
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Wed Nov 26 02:58:41 1979\n"), "asctime returned %s\n", ret);

    /* Dates that can't be displayed using 26 characters are broken */
    gmt_tm->tm_mday = 28;
    gmt_tm->tm_year = 8100;
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Wed Nov 28 02:58:41 :000\n"), "asctime returned %s\n", ret);

    gmt_tm->tm_year = 264100;
    ret = p_asctime(gmt_tm);
    ok(!strcmp(ret, "Wed Nov 28 02:58:41 :000\n"), "asctime returned %s\n", ret);

    /* asctime works from year 1900 */
    errno = 0xdeadbeef;
    gmt_tm->tm_year = -1;
    ret = p_asctime(gmt_tm);
    ok(!ret || broken(!strcmp(ret, "Wed Nov 28 02:58:41 190/\n")), "asctime returned %s\n", ret);
    ok(errno==EINVAL || broken(errno == 0xdeadbeef), "errno = %d\n", errno);

    errno = 0xdeadbeef;
    gmt_tm->tm_mon = 1;
    gmt_tm->tm_mday = 30;
    gmt_tm->tm_year = 79;
    ret = p_asctime(gmt_tm);
    ok(!ret || broken(!strcmp(ret, "Wed Feb 30 02:58:41 1979\n")), "asctime returned %s\n", ret);
    ok(errno==EINVAL || broken(errno==0xdeadbeef), "errno = %d\n", errno);
}