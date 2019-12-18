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
 int EDOM ; 
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  NAN ; 
 int almost_equal (double,double) ; 
 int errno ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 double p_atan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_exp (int /*<<< orphan*/ ) ; 
 double p_tanh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_math_functions(void)
{
    double ret;

    errno = 0xdeadbeef;
    p_atan(NAN);
    ok(errno == EDOM, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = p_atan(INFINITY);
    ok(almost_equal(ret, 1.57079632679489661923), "ret = %lf\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = p_atan(-INFINITY);
    ok(almost_equal(ret, -1.57079632679489661923), "ret = %lf\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    p_tanh(NAN);
    ok(errno == EDOM, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    ret = p_tanh(INFINITY);
    ok(almost_equal(ret, 1.0), "ret = %lf\n", ret);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    p_exp(NAN);
    ok(errno == EDOM, "errno = %d\n", errno);

    errno = 0xdeadbeef;
    p_exp(INFINITY);
    ok(errno == 0xdeadbeef, "errno = %d\n", errno);
}