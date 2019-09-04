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
 int EBADF ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  LC_ALL ; 
 int almost_equal (double,long double) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 double p__strtod_l (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 double strtod (char const*,char**) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__strtod(void)
{
    const char double1[] = "12.1";
    const char double2[] = "-13.721";
    const char double3[] = "INF";
    const char double4[] = ".21e12";
    const char double5[] = "214353e-3";
    const char double6[] = "NAN";
    const char overflow[] = "1d9999999999999999999";
    const char white_chars[] = "  d10";

    char *end;
    double d;

    d = strtod(double1, &end);
    ok(almost_equal(d, 12.1), "d = %lf\n", d);
    ok(end == double1+4, "incorrect end (%d)\n", (int)(end-double1));

    d = strtod(double2, &end);
    ok(almost_equal(d, -13.721), "d = %lf\n", d);
    ok(end == double2+7, "incorrect end (%d)\n", (int)(end-double2));

    d = strtod(double3, &end);
    ok(almost_equal(d, 0), "d = %lf\n", d);
    ok(end == double3, "incorrect end (%d)\n", (int)(end-double3));

    d = strtod(double4, &end);
    ok(almost_equal(d, 210000000000.0), "d = %lf\n", d);
    ok(end == double4+6, "incorrect end (%d)\n", (int)(end-double4));

    d = strtod(double5, &end);
    ok(almost_equal(d, 214.353), "d = %lf\n", d);
    ok(end == double5+9, "incorrect end (%d)\n", (int)(end-double5));

    d = strtod(double6, &end);
    ok(almost_equal(d, 0), "d = %lf\n", d);
    ok(end == double6, "incorrect end (%d)\n", (int)(end-double6));

    d = strtod("12.1d2", NULL);
    ok(almost_equal(d, 12.1e2), "d = %lf\n", d);

    d = strtod(white_chars, &end);
    ok(almost_equal(d, 0), "d = %lf\n", d);
    ok(end == white_chars, "incorrect end (%d)\n", (int)(end-white_chars));

    if (!p__strtod_l)
        win_skip("_strtod_l not found\n");
    else
    {
        errno = EBADF;
        d = strtod(NULL, NULL);
        ok(almost_equal(d, 0.0), "d = %lf\n", d);
        ok(errno == EINVAL, "errno = %x\n", errno);

        errno = EBADF;
        end = (char *)0xdeadbeef;
        d = strtod(NULL, &end);
        ok(almost_equal(d, 0.0), "d = %lf\n", d);
        ok(errno == EINVAL, "errno = %x\n", errno);
        ok(!end, "incorrect end ptr %p\n", end);

        errno = EBADF;
        d = p__strtod_l(NULL, NULL, NULL);
        ok(almost_equal(d, 0.0), "d = %lf\n", d);
        ok(errno == EINVAL, "errno = %x\n", errno);
    }

    /* Set locale with non '.' decimal point (',') */
    if(!setlocale(LC_ALL, "Polish")) {
        win_skip("system with limited locales\n");
        return;
    }

    d = strtod("12.1", NULL);
    ok(almost_equal(d, 12.0), "d = %lf\n", d);

    d = strtod("12,1", NULL);
    ok(almost_equal(d, 12.1), "d = %lf\n", d);

    setlocale(LC_ALL, "C");

    /* Precision tests */
    d = strtod("0.1", NULL);
    ok(almost_equal(d, 0.1), "d = %lf\n", d);
    d = strtod("-0.1", NULL);
    ok(almost_equal(d, -0.1), "d = %lf\n", d);
    d = strtod("0.1281832188491894198128921", NULL);
    ok(almost_equal(d, 0.1281832188491894198128921), "d = %lf\n", d);
    d = strtod("0.82181281288121", NULL);
    ok(almost_equal(d, 0.82181281288121), "d = %lf\n", d);
    d = strtod("21921922352523587651128218821", NULL);
    ok(almost_equal(d, 21921922352523587651128218821.0), "d = %lf\n", d);
    d = strtod("0.1d238", NULL);
    ok(almost_equal(d, 0.1e238L), "d = %lf\n", d);
    d = strtod("0.1D-4736", NULL);
    ok(almost_equal(d, 0.1e-4736L), "d = %lf\n", d);

    errno = 0xdeadbeef;
    strtod(overflow, &end);
    ok(errno == ERANGE, "errno = %x\n", errno);
    ok(end == overflow+21, "incorrect end (%d)\n", (int)(end-overflow));

    errno = 0xdeadbeef;
    strtod("-1d309", NULL);
    ok(errno == ERANGE, "errno = %x\n", errno);
}