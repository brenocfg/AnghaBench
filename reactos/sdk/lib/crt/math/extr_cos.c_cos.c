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
 int M_PI ; 
 scalar_t__* cos_off_tbl ; 
 double* cos_sign_tbl ; 

double
cos(double x)
{
    int quadrant;
    double x2, result;

    /* Calculate the quadrant */
    quadrant = (int)(x * (2./M_PI));

    /* Get offset inside quadrant */
    x = x - quadrant * (M_PI/2.);

    /* Normalize quadrant to [0..3] */
    quadrant = quadrant & 0x3;

    /* Fixup value for the generic function */
    x += cos_off_tbl[quadrant];

    /* Calculate the negative of the square of x */
    x2 = - (x * x);

    /* This is an unrolled taylor series using <PRECISION> iterations
     * Example with 4 iterations:
     * result = 1 - x^2/2! + x^4/4! - x^6/6! + x^8/8!
     * To save multiplications and to keep the precision high, it's performed
     * like this:
     * result = 1 - x^2 * (1/2! - x^2 * (1/4! - x^2 * (1/6! - x^2 * (1/8!))))
     */

    /* Start with 0, compiler will optimize this away */
    result = 0;

#if (PRECISION >= 10)
    result += 1./(1.*2*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18*19*20);
    result *= x2;
#endif
#if (PRECISION >= 9)
    result += 1./(1.*2*3*4*5*6*7*8*9*10*11*12*13*14*15*16*17*18);
    result *= x2;
#endif
#if (PRECISION >= 8)
    result += 1./(1.*2*3*4*5*6*7*8*9*10*11*12*13*14*15*16);
    result *= x2;
#endif
#if (PRECISION >= 7)
    result += 1./(1.*2*3*4*5*6*7*8*9*10*11*12*13*14);
    result *= x2;
#endif
#if (PRECISION >= 6)
    result += 1./(1.*2*3*4*5*6*7*8*9*10*11*12);
    result *= x2;
#endif
#if (PRECISION >= 5)
    result += 1./(1.*2*3*4*5*6*7*8*9*10);
    result *= x2;
#endif
    result += 1./(1.*2*3*4*5*6*7*8);
    result *= x2;

    result += 1./(1.*2*3*4*5*6);
    result *= x2;

    result += 1./(1.*2*3*4);
    result *= x2;

    result += 1./(1.*2);
    result *= x2;

    result += 1;

    /* Apply correct sign */
    result *= cos_sign_tbl[quadrant];

    return result;
}