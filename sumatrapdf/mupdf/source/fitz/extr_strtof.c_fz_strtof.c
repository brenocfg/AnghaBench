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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 float INFINITY ; 
 scalar_t__ NAN ; 
 int /*<<< orphan*/  SET_TAILPTR (char**,char const*) ; 
 int /*<<< orphan*/  errno ; 
 float scale_integer_to_float (int,int,int) ; 
 scalar_t__ starts_with (char const**,char*) ; 

float
fz_strtof(const char *string, char **tailptr)
{
	/* FIXME: error (1/2 + 1/256) ulp  */
	const char *s;
	uint32_t M = 0;
	int N = 0;
	/* If decimal_digits gets 9 we truncate all following digits.  */
	int decimal_digits = 0;
	int negative = 0;
	const char *number_start = 0;

	/* Skip leading whitespace (isspace in "C" locale).  */
	s = string;
	while (*s == ' ' || *s == '\f' || *s == '\n' || *s == '\r' || *s ==  '\t' || *s == '\v')
		++s;

	/* Parse sign.  */
	if (*s == '+')
		++s;
	if (*s == '-')
	{
		negative = 1;
		++s;
	}
	number_start = s;
	/* Parse digits before decimal point.  */
	while (*s >= '0' && *s <= '9')
	{
		if (decimal_digits)
		{
			if (decimal_digits < 9)
			{
				++decimal_digits;
				M = M * 10 + *s - '0';
			}
			/* Really arcane strings might overflow N.  */
			else if (N < 1000)
				++N;
		}
		else if (*s > '0')
		{
			M = *s - '0';
			++decimal_digits;
		}
		++s;
	}

	/* Parse decimal point.  */
	if (*s == '.')
		++s;

	/* Parse digits after decimal point. */
	while (*s >= '0' && *s <= '9')
	{
		if (decimal_digits < 9)
		{
			if (decimal_digits || *s > '0')
			{
				++decimal_digits;
				M = M * 10 + *s - '0';
			}
			--N;
		}
		++s;
	}
	if ((s  == number_start + 1 && *number_start == '.') || number_start == s)
	{
		/* No Number. Check for INF and NAN strings.  */
		s = number_start;
		if (starts_with(&s, "INFINITY") || starts_with(&s, "INF"))
		{
			errno = ERANGE;
			SET_TAILPTR(tailptr, s);
			return negative ? -INFINITY : +INFINITY;
		}
		else if (starts_with(&s, "NAN"))
		{
			SET_TAILPTR(tailptr, s);
			return (float)NAN;
		}
		else
		{
			SET_TAILPTR(tailptr, string);
			return 0.f;
		}
	}

	/* Parse exponent. */
	if (*s == 'e' || *s == 'E')
	{
		int exp_negative = 0;
		int exp = 0;
		const char *int_start;
		const char *exp_start = s;

		++s;
		if (*s == '+')
			++s;
		else if (*s == '-')
		{
			++s;
			exp_negative = 1;
		}
		int_start = s;
		/* Parse integer.  */
		while (*s >= '0' && *s <= '9')
		{
			/* Make sure exp does not get overflowed.  */
			if (exp < 100)
				exp = exp * 10 + *s - '0';
			++s;
		}
		if (exp_negative)
			exp = -exp;
		if (s == int_start)
			/* No Number.  */
			s = exp_start;
		else
			N += exp;
	}

	SET_TAILPTR(tailptr, s);
	return scale_integer_to_float(M, N, negative);
}