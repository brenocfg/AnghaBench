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
 double exp (float) ; 
 float fabsf (float) ; 
 double sqrt (float) ; 

__attribute__((used)) static float bessi0( float x )
{
    float ax, ans;
    double y; /* Accumulate polynomials in double precision. */
    if( ( ax = fabsf( x ) ) < 3.75f ) /* Polynomial fit. */
    {
        y = x / 3.75;
        y *= y;
        ans = 1.0 + y * ( 3.5156229 + y * ( 3.0899424 + y * ( 1.2067492
                  + y * ( 0.2659732 + y * ( 0.360768e-1
                  + y * 0.45813e-2 ) ) ) ) );
    }
    else
    {
        y = 3.75 / ax;
        ans = ( exp( ax ) / sqrt( ax ) ) * ( 0.39894228 + y * ( 0.1328592e-1
            + y * ( 0.225319e-2 + y * ( -0.157565e-2 + y * ( 0.916281e-2
            + y * ( -0.2057706e-1 + y * ( 0.2635537e-1 + y * ( -0.1647633e-1
            + y * 0.392377e-2 ) ) ) ) ) ) ) );
    }
    return ans;
}