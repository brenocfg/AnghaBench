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
 int /*<<< orphan*/  ERANGE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  errno ; 
 int maxExponent ; 
 double* powersOf10 ; 

double
js_strtod(const char *string, char **endPtr)
{
	int sign, expSign = FALSE;
	double fraction, dblExp, *d;
	register const char *p;
	register int c;

	/* Exponent read from "EX" field. */
	int exp = 0;

	/* Exponent that derives from the fractional part. Under normal
	 * circumstances, it is the negative of the number of digits in F.
	 * However, if I is very long, the last digits of I get dropped
	 * (otherwise a long I with a large negative exponent could cause an
	 * unnecessary overflow on I alone). In this case, fracExp is
	 * incremented one for each dropped digit.
	 */
	int fracExp = 0;

	/* Number of digits in mantissa. */
	int mantSize;

	/* Number of mantissa digits BEFORE decimal point. */
	int decPt;

	/* Temporarily holds location of exponent in string. */
	const char *pExp;

	/*
	 * Strip off leading blanks and check for a sign.
	 */

	p = string;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
		p += 1;
	}
	if (*p == '-') {
		sign = TRUE;
		p += 1;
	} else {
		if (*p == '+') {
			p += 1;
		}
		sign = FALSE;
	}

	/*
	 * Count the number of digits in the mantissa (including the decimal
	 * point), and also locate the decimal point.
	 */

	decPt = -1;
	for (mantSize = 0; ; mantSize += 1)
	{
		c = *p;
		if (!(c>='0'&&c<='9')) {
			if ((c != '.') || (decPt >= 0)) {
				break;
			}
			decPt = mantSize;
		}
		p += 1;
	}

	/*
	 * Now suck up the digits in the mantissa. Use two integers to
	 * collect 9 digits each (this is faster than using floating-point).
	 * If the mantissa has more than 18 digits, ignore the extras, since
	 * they can't affect the value anyway.
	 */

	pExp = p;
	p -= mantSize;
	if (decPt < 0) {
		decPt = mantSize;
	} else {
		mantSize -= 1;			/* One of the digits was the point. */
	}
	if (mantSize > 18) {
		fracExp = decPt - 18;
		mantSize = 18;
	} else {
		fracExp = decPt - mantSize;
	}
	if (mantSize == 0) {
		fraction = 0.0;
		p = string;
		goto done;
	} else {
		int frac1, frac2;
		frac1 = 0;
		for ( ; mantSize > 9; mantSize -= 1)
		{
			c = *p;
			p += 1;
			if (c == '.') {
				c = *p;
				p += 1;
			}
			frac1 = 10*frac1 + (c - '0');
		}
		frac2 = 0;
		for (; mantSize > 0; mantSize -= 1)
		{
			c = *p;
			p += 1;
			if (c == '.') {
				c = *p;
				p += 1;
			}
			frac2 = 10*frac2 + (c - '0');
		}
		fraction = (1.0e9 * frac1) + frac2;
	}

	/*
	 * Skim off the exponent.
	 */

	p = pExp;
	if ((*p == 'E') || (*p == 'e')) {
		p += 1;
		if (*p == '-') {
			expSign = TRUE;
			p += 1;
		} else {
			if (*p == '+') {
				p += 1;
			}
			expSign = FALSE;
		}
		while ((*p >= '0') && (*p <= '9')) {
			exp = exp * 10 + (*p - '0');
			p += 1;
		}
	}
	if (expSign) {
		exp = fracExp - exp;
	} else {
		exp = fracExp + exp;
	}

	/*
	 * Generate a floating-point number that represents the exponent.
	 * Do this by processing the exponent one bit at a time to combine
	 * many powers of 2 of 10. Then combine the exponent with the
	 * fraction.
	 */

	if (exp < -maxExponent) {
		exp = maxExponent;
		expSign = TRUE;
		errno = ERANGE;
	} else if (exp > maxExponent) {
		exp = maxExponent;
		expSign = FALSE;
		errno = ERANGE;
	} else if (exp < 0) {
		expSign = TRUE;
		exp = -exp;
	} else {
		expSign = FALSE;
	}
	dblExp = 1.0;
	for (d = powersOf10; exp != 0; exp >>= 1, d += 1) {
		if (exp & 01) {
			dblExp *= *d;
		}
	}
	if (expSign) {
		fraction /= dblExp;
	} else {
		fraction *= dblExp;
	}

done:
	if (endPtr != NULL) {
		*endPtr = (char *) p;
	}

	if (sign) {
		return -fraction;
	}
	return fraction;
}