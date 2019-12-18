#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  double cmsFloat64Number ;
struct TYPE_6__ {double FL; } ;
typedef  TYPE_1__ cmsCIECAM02 ;
struct TYPE_7__ {double* RGBpa; double* RGBp; } ;
typedef  TYPE_2__ CAM02COLOR ;

/* Variables and functions */
 double fabs (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static
CAM02COLOR InverseNonlinearity(CAM02COLOR clr, cmsCIECAM02* pMod)
{
    cmsUInt32Number i;
    cmsFloat64Number c1;

    for (i = 0; i < 3; i++) {
        if ((clr.RGBpa[i] - 0.1) < 0) c1 = -1;
        else                               c1 = 1;
        clr.RGBp[i] = c1 * (100.0 / pMod->FL) *
            pow(((27.13 * fabs(clr.RGBpa[i] - 0.1)) /
            (400.0 - fabs(clr.RGBpa[i] - 0.1))),
            (1.0 / 0.42));
    }

    return clr;
}