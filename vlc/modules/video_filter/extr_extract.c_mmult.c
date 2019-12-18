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

__attribute__((used)) static void mmult( double *res, double *a, double *b )
{
    for( int i = 0; i < 3; i++ )
    {
        for( int j = 0; j < 3; j++ )
        {
            res[ i*3 + j ] = 0.;
            for( int k = 0; k < 3; k++ )
            {
                res[ i*3 + j ] += a[ i*3 + k ] * b[ k*3 + j ];
            }
        }
    }
}