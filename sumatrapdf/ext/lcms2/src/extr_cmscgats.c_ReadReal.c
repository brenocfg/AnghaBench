#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsInt32Number ;
struct TYPE_4__ {double dnum; char ch; } ;
typedef  TYPE_1__ cmsIT8 ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  NextCh (TYPE_1__*) ; 
 scalar_t__ isdigit (char) ; 
 char toupper (char) ; 
 double xpow10 (int) ; 

__attribute__((used)) static
void ReadReal(cmsIT8* it8, cmsInt32Number inum)
{
    it8->dnum = (cmsFloat64Number)inum;

    while (isdigit(it8->ch)) {

        it8->dnum = (cmsFloat64Number)it8->dnum * 10.0 + (cmsFloat64Number)(it8->ch - '0');
        NextCh(it8);
    }

    if (it8->ch == '.') {        // Decimal point

        cmsFloat64Number frac = 0.0;      // fraction
        int prec = 0;                     // precision

        NextCh(it8);               // Eats dec. point

        while (isdigit(it8->ch)) {

            frac = frac * 10.0 + (cmsFloat64Number)(it8->ch - '0');
            prec++;
            NextCh(it8);
        }

        it8->dnum = it8->dnum + (frac / xpow10(prec));
    }

    // Exponent, example 34.00E+20
    if (toupper(it8->ch) == 'E') {

        cmsInt32Number e;
        cmsInt32Number sgn;

        NextCh(it8); sgn = 1;

        if (it8->ch == '-') {

            sgn = -1; NextCh(it8);
        }
        else
            if (it8->ch == '+') {

                sgn = +1;
                NextCh(it8);
            }

        e = 0;
        while (isdigit(it8->ch)) {

            cmsInt32Number digit = (it8->ch - '0');

            if ((cmsFloat64Number)e * 10.0 + (cmsFloat64Number)digit < (cmsFloat64Number)+2147483647.0)
                e = e * 10 + digit;

            NextCh(it8);
        }

        e = sgn*e;
        it8->dnum = it8->dnum * xpow10(e);
    }
}