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
typedef  scalar_t__ cmsFloat64Number ;
struct TYPE_3__ {int LA; scalar_t__ F; } ;
typedef  TYPE_1__ cmsCIECAM02 ;

/* Variables and functions */
 double exp (int) ; 

__attribute__((used)) static
cmsFloat64Number computeD(cmsCIECAM02* pMod)
{
    cmsFloat64Number D;

    D = pMod->F - (1.0/3.6)*(exp(((-pMod ->LA-42) / 92.0)));

    return D;
}