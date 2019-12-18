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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 double INT_MAX ; 
 double INT_MIN ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  js_fmtexp (char*,int) ; 
 int js_grisu2 (double,char*,int*) ; 
 char const* js_itoa (char*,int) ; 
 scalar_t__ signbit (double) ; 

const char *jsV_numbertostring(js_State *J, char buf[32], double f)
{
	char digits[32], *p = buf, *s = digits;
	int exp, ndigits, point;

	if (f == 0) return "0";
	if (isnan(f)) return "NaN";
	if (isinf(f)) return f < 0 ? "-Infinity" : "Infinity";

	/* Fast case for integers. This only works assuming all integers can be
	 * exactly represented by a float. This is true for 32-bit integers and
	 * 64-bit floats. */
	if (f >= INT_MIN && f <= INT_MAX) {
		int i = (int)f;
		if ((double)i == f)
			return js_itoa(buf, i);
	}

	ndigits = js_grisu2(f, digits, &exp);
	point = ndigits + exp;

	if (signbit(f))
		*p++ = '-';

	if (point < -5 || point > 21) {
		*p++ = *s++;
		if (ndigits > 1) {
			int n = ndigits - 1;
			*p++ = '.';
			while (n--)
				*p++ = *s++;
		}
		js_fmtexp(p, point - 1);
	}

	else if (point <= 0) {
		*p++ = '0';
		*p++ = '.';
		while (point++ < 0)
			*p++ = '0';
		while (ndigits-- > 0)
			*p++ = *s++;
		*p = 0;
	}

	else {
		while (ndigits-- > 0) {
			*p++ = *s++;
			if (--point == 0 && ndigits > 0)
				*p++ = '.';
		}
		while (point-- > 0)
			*p++ = '0';
		*p = 0;
	}

	return buf;
}