#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ type_t ;
struct TYPE_3__ {double f_sigma; int i_dim; scalar_t__* pt_distribution; } ;
typedef  TYPE_1__ filter_sys_t ;

/* Variables and functions */
 int M_PI ; 
 int exp (int) ; 
 float sqrt (int) ; 
 scalar_t__* xmalloc (int) ; 

__attribute__((used)) static void gaussianblur_InitDistribution( filter_sys_t *p_sys )
{
    double f_sigma = p_sys->f_sigma;
    int i_dim = (int)(3.*f_sigma);
    type_t *pt_distribution = xmalloc( (2*i_dim+1) * sizeof( type_t ) );

    for( int x = -i_dim; x <= i_dim; x++ )
    {
        const float f_distribution = sqrt( exp(-(x*x)/(f_sigma*f_sigma) ) / (2.*M_PI*f_sigma*f_sigma) );
#ifdef DONT_USE_FLOATS
        const float f_factor = 1 << 8;
#else
        const float f_factor = 1;
#endif

        pt_distribution[i_dim+x] = (type_t)( f_distribution * f_factor );
        //printf("%f\n",(float)pt_distribution[i_dim+x]);
    }
    p_sys->i_dim = i_dim;
    p_sys->pt_distribution = pt_distribution;
}