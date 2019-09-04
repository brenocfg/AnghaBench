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
 char* _fcvt (double,int,int*,int*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void test_fcvt(void)
{
    char *str;
    int dec=100, sign=100;

    /* Numbers less than 1.0 with different precisions */
    str = _fcvt(0.0001, 1, &dec, &sign );
    ok( 0 == strcmp(str,""), "bad return '%s'\n", str);
    ok( -3 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.0001, -10, &dec, &sign );
    ok( 0 == strcmp(str,""), "bad return '%s'\n", str);
    ok( -3 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.0001, 10, &dec, &sign );
    ok( 0 == strcmp(str,"1000000"), "bad return '%s'\n", str);
    ok( -3 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    /* Basic sign test */
    str = _fcvt(-111.0001, 5, &dec, &sign );
    ok( 0 == strcmp(str,"11100010"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 1 == sign, "sign wrong\n");

    str = _fcvt(111.0001, 5, &dec, &sign );
    ok( 0 == strcmp(str,"11100010"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong\n");
    ok( 0 == sign, "sign wrong\n");

    /* 0.0 with different precisions */
    str = _fcvt(0.0, 5, &dec, &sign );
    ok( 0 == strcmp(str,"00000"), "bad return '%s'\n", str);
    ok( 0 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.0, 0, &dec, &sign );
    ok( 0 == strcmp(str,""), "bad return '%s'\n", str);
    ok( 0 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.0, -1, &dec, &sign );
    ok( 0 == strcmp(str,""), "bad return '%s'\n", str);
    ok( 0 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    /* Numbers > 1.0 with 0 or -ve precision */
    str = _fcvt(-123.0001, 0, &dec, &sign );
    ok( 0 == strcmp(str,"123"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 1 == sign, "sign wrong\n");

    str = _fcvt(-123.0001, -1, &dec, &sign );
    ok( 0 == strcmp(str,"12"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 1 == sign, "sign wrong\n");

    str = _fcvt(-123.0001, -2, &dec, &sign );
    ok( 0 == strcmp(str,"1"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 1 == sign, "sign wrong\n");

    str = _fcvt(-123.0001, -3, &dec, &sign );
    ok( 0 == strcmp(str,""), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 1 == sign, "sign wrong\n");

    /* Numbers > 1.0, but with rounding at the point of precision */
    str = _fcvt(99.99, 1, &dec, &sign );
    ok( 0 == strcmp(str,"1000"), "bad return '%s'\n", str);
    ok( 3 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    /* Numbers < 1.0 where rounding occurs at the point of precision */
    str = _fcvt(0.00636, 2, &dec, &sign );
    ok( 0 == strcmp(str,"1"), "bad return '%s'\n", str);
    ok( -1 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.00636, 3, &dec, &sign );
    ok( 0 == strcmp(str,"6"), "bad return '%s'\n", str);
    ok( -2 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.09999999996, 2, &dec, &sign );
    ok( 0 == strcmp(str,"10"), "bad return '%s'\n", str);
    ok( 0 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");

    str = _fcvt(0.6, 0, &dec, &sign );
    ok( 0 == strcmp(str,"1"), "bad return '%s'\n", str);
    ok( 1 == dec, "dec wrong %d\n", dec);
    ok( 0 == sign, "sign wrong\n");
}