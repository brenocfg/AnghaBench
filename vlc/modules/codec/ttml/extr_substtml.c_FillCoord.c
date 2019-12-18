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
struct TYPE_3__ {float i_value; scalar_t__ unit; } ;
typedef  TYPE_1__ ttml_length_t ;

/* Variables and functions */
 scalar_t__ TTML_UNIT_PERCENT ; 

__attribute__((used)) static void FillCoord( ttml_length_t v, int i_flag, float *p_val, int *pi_flags )
{
    *p_val = v.i_value;
    if( v.unit == TTML_UNIT_PERCENT )
    {
        *p_val /= 100.0;
        *pi_flags |= i_flag;
    }
    else *pi_flags &= ~i_flag;
}