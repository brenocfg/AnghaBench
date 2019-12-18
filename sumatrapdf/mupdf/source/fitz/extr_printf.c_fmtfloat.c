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
struct fmtbuf {int dummy; } ;

/* Variables and functions */
 float FLT_MAX ; 
 int /*<<< orphan*/  fmtputc (struct fmtbuf*,char) ; 
 int fz_grisu (float,char*,int*) ; 
 scalar_t__ isinf (float) ; 
 scalar_t__ isnan (float) ; 
 scalar_t__ signbit (float) ; 

__attribute__((used)) static void fmtfloat(struct fmtbuf *out, float f)
{
	char digits[40], *s = digits;
	int exp, ndigits, point;

	if (isnan(f)) f = 0;
	if (isinf(f)) f = f < 0 ? -FLT_MAX : FLT_MAX;

	if (signbit(f))
		fmtputc(out, '-');

	if (f == 0)
	{
		fmtputc(out, '0');
		return;
	}

	ndigits = fz_grisu(f, digits, &exp);
	point = exp + ndigits;

	if (point <= 0)
	{
		fmtputc(out, '.');
		while (point++ < 0)
			fmtputc(out, '0');
		while (ndigits-- > 0)
			fmtputc(out, *s++);
	}

	else
	{
		while (ndigits-- > 0)
		{
			fmtputc(out, *s++);
			if (--point == 0 && ndigits > 0)
				fmtputc(out, '.');
		}
		while (point-- > 0)
			fmtputc(out, '0');
	}
}