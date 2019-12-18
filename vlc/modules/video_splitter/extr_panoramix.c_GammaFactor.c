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
struct TYPE_3__ {float f_black_crush; float f_black_level; double f_gamma; float f_white_crush; double f_white_level; } ;
typedef  TYPE_1__ panoramix_gamma_t ;

/* Variables and functions */
 double pow (float,double) ; 

__attribute__((used)) static double GammaFactor( const panoramix_gamma_t *g, float f_value )
{
    if( f_value <= g->f_black_crush )
    {
        float f_input = f_value * g->f_black_level / g->f_black_crush + (1.0 - g->f_black_level);

        return pow( f_input, 1.0 / g->f_gamma );
    }
    else if( f_value >= g->f_white_crush )
    {
        float f_input = (f_value * (1.0 - (g->f_white_level + 1.0)) + (g->f_white_level + 1.0) * g->f_white_crush - 1.0) / (g->f_white_crush - 1.0);
        return pow( f_input, 1.0 / g->f_gamma );
    }
    return 1.0;
}