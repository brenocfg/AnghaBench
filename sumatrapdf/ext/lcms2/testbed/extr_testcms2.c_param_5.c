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
typedef  int cmsFloat64Number ;
typedef  int const cmsFloat32Number ;

/* Variables and functions */
 int const pow (int,int const) ; 

__attribute__((used)) static
cmsFloat32Number param_5(cmsFloat32Number x, const cmsFloat64Number Params[])
{
    cmsFloat64Number e, Val;
    // Y = (aX + b)^Gamma + e | X >= d
    // Y = cX + f             | else
    if (x >= Params[4]) {

        e = Params[1]*x + Params[2];
        if (e > 0)
            Val = pow(e, Params[0]) + Params[5];
        else
            Val = 0;
    }
    else
        Val = x*Params[3] + Params[6];

    return (cmsFloat32Number) Val;
}