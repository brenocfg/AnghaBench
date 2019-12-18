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
typedef  int cmsFloat32Number ;

/* Variables and functions */
 int pow (int,int) ; 

__attribute__((used)) static
cmsFloat32Number sigmoidal(cmsFloat32Number x, const cmsFloat64Number Params[])
{
    cmsFloat64Number Val;

    Val = pow(1.0 - pow(1 - x, 1/Params[0]), 1/Params[0]);

    return (cmsFloat32Number) Val;
}