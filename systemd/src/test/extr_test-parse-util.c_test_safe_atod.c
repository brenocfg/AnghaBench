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
 int EINVAL ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ errno ; 
 double fabs (double) ; 
 int safe_atod (char*,double*) ; 
 int setlocale (int /*<<< orphan*/ ,char*) ; 
 double strtod (char*,char**) ; 

__attribute__((used)) static void test_safe_atod(void) {
        int r;
        double d;
        char *e;

        r = safe_atod("junk", &d);
        assert_se(r == -EINVAL);

        r = safe_atod("0.2244", &d);
        assert_se(r == 0);
        assert_se(fabs(d - 0.2244) < 0.000001);

        r = safe_atod("0,5", &d);
        assert_se(r == -EINVAL);

        errno = 0;
        strtod("0,5", &e);
        assert_se(*e == ',');

        r = safe_atod("", &d);
        assert_se(r == -EINVAL);

        /* Check if this really is locale independent */
        if (setlocale(LC_NUMERIC, "de_DE.utf8")) {

                r = safe_atod("0.2244", &d);
                assert_se(r == 0);
                assert_se(fabs(d - 0.2244) < 0.000001);

                r = safe_atod("0,5", &d);
                assert_se(r == -EINVAL);

                errno = 0;
                assert_se(fabs(strtod("0,5", &e) - 0.5) < 0.00001);

                r = safe_atod("", &d);
                assert_se(r == -EINVAL);
        }

        /* And check again, reset */
        assert_se(setlocale(LC_NUMERIC, "C"));

        r = safe_atod("0.2244", &d);
        assert_se(r == 0);
        assert_se(fabs(d - 0.2244) < 0.000001);

        r = safe_atod("0,5", &d);
        assert_se(r == -EINVAL);

        errno = 0;
        strtod("0,5", &e);
        assert_se(*e == ',');

        r = safe_atod("", &d);
        assert_se(r == -EINVAL);
}