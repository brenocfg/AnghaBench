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
typedef  double cmsFloat64Number ;
struct TYPE_3__ {double n; } ;
typedef  TYPE_1__ cmsCIECAM02 ;

/* Variables and functions */
 double pow (double,double) ; 

__attribute__((used)) static
cmsFloat64Number computeNbb(cmsCIECAM02* pMod)
{
    return (0.725 * pow((1.0 / pMod -> n), 0.2));
}