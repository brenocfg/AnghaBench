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
typedef  int /*<<< orphan*/  cmsFloat32Number ;

/* Variables and functions */
 int const log10 (int const) ; 
 int const pow (int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static
cmsFloat32Number param_7(cmsFloat32Number x, const cmsFloat64Number Params[])
{
    cmsFloat64Number Val;


    Val = Params[1]*log10(Params[2] * pow(x, Params[0]) + Params[3]) + Params[4];

    return (cmsFloat32Number) Val;
}