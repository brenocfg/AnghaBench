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
typedef  double cmsInt32Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 
 char toupper (char const) ; 
 double xpow10 (int) ; 

__attribute__((used)) static
cmsFloat64Number ParseFloatNumber(const char *Buffer)
{
    cmsFloat64Number dnum = 0.0;
    int sign = 1;

    // keep safe
    if (Buffer == NULL) return 0.0;

    if (*Buffer == '-' || *Buffer == '+') {

        sign = (*Buffer == '-') ? -1 : 1;
        Buffer++;
    }


    while (*Buffer && isdigit((int)*Buffer)) {

        dnum = dnum * 10.0 + (*Buffer - '0');
        if (*Buffer) Buffer++;
    }

    if (*Buffer == '.') {

        cmsFloat64Number frac = 0.0;      // fraction
        int prec = 0;                     // precision

        if (*Buffer) Buffer++;

        while (*Buffer && isdigit((int)*Buffer)) {

            frac = frac * 10.0 + (*Buffer - '0');
            prec++;
            if (*Buffer) Buffer++;
        }

        dnum = dnum + (frac / xpow10(prec));
    }

    // Exponent, example 34.00E+20
    if (*Buffer && toupper(*Buffer) == 'E') {

        int e;
        int sgn;

        if (*Buffer) Buffer++;
        sgn = 1;

        if (*Buffer == '-') {

            sgn = -1;
            if (*Buffer) Buffer++;
        }
        else
            if (*Buffer == '+') {

                sgn = +1;
                if (*Buffer) Buffer++;
            }

        e = 0;
        while (*Buffer && isdigit((int)*Buffer)) {

            cmsInt32Number digit = (*Buffer - '0');

            if ((cmsFloat64Number)e * 10.0 + digit < (cmsFloat64Number)+2147483647.0)
                e = e * 10 + digit;

            if (*Buffer) Buffer++;
        }

        e = sgn*e;
        dnum = dnum * xpow10(e);
    }

    return sign * dnum;
}