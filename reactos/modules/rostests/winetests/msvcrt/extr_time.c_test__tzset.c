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
 int /*<<< orphan*/  _putenv (char*) ; 
 int /*<<< orphan*/  _snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  _tzset () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int* p___p__daylight () ; 
 int* p___p__dstbias () ; 
 int* p___p__timezone () ; 
 int* p__dstbias () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__tzset(void)
{
    char TZ_env[256];
    int ret;

    if(!p___p__daylight || !p___p__timezone || !p___p__dstbias) {
        skip("__p__daylight, __p__timezone or __p__dstbias is not available\n");
        return;
    }

    if (p__dstbias) {
        ret = *p__dstbias();
        ok(ret == -3600, "*__dstbias() = %d\n", ret);
        ret = *p___p__dstbias();
        ok(ret == -3600, "*__p__dstbias() = %d\n", ret);
    }
    else
        win_skip("__dstbias() is not available.\n");

    _snprintf(TZ_env,255,"TZ=%s",(getenv("TZ")?getenv("TZ"):""));

    ret = *p___p__daylight();
    ok(ret == 1, "*__p__daylight() = %d\n", ret);
    ret = *p___p__timezone();
    ok(ret == 28800, "*__p__timezone() = %d\n", ret);
    ret = *p___p__dstbias();
    ok(ret == -3600, "*__p__dstbias() = %d\n", ret);

    _putenv("TZ=xxx+1yyy");
    _tzset();
    ret = *p___p__daylight();
    ok(ret == 121, "*__p__daylight() = %d\n", ret);
    ret = *p___p__timezone();
    ok(ret == 3600, "*__p__timezone() = %d\n", ret);
    ret = *p___p__dstbias();
    ok(ret == -3600, "*__p__dstbias() = %d\n", ret);

    *p___p__dstbias() = 0;
    _putenv("TZ=xxx+1:3:5zzz");
    _tzset();
    ret = *p___p__daylight();
    ok(ret == 122, "*__p__daylight() = %d\n", ret);
    ret = *p___p__timezone();
    ok(ret == 3785, "*__p__timezone() = %d\n", ret);
    ret = *p___p__dstbias();
    ok(ret == 0, "*__p__dstbias() = %d\n", ret);

    _putenv(TZ_env);
}