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
struct TYPE_6__ {double FL; double Nbb; } ;
typedef  TYPE_1__ cmsCIECAM02 ;
struct TYPE_7__ {double* RGBp; double* RGBpa; double A; } ;
typedef  TYPE_2__ CAM02COLOR ;

/* Variables and functions */
 double pow (double,double) ; 

__attribute__((used)) static
CAM02COLOR NonlinearCompression(CAM02COLOR clr, cmsCIECAM02* pMod)
{
    cmsUInt32Number i;
    cmsFloat64Number temp;

    for (i = 0; i < 3; i++) {
        if (clr.RGBp[i] < 0) {

            temp = pow((-1.0 * pMod->FL * clr.RGBp[i] / 100.0), 0.42);
            clr.RGBpa[i] = (-1.0 * 400.0 * temp) / (temp + 27.13) + 0.1;
        }
        else {
            temp = pow((pMod->FL * clr.RGBp[i] / 100.0), 0.42);
            clr.RGBpa[i] = (400.0 * temp) / (temp + 27.13) + 0.1;
        }
    }

    clr.A = (((2.0 * clr.RGBpa[0]) + clr.RGBpa[1] +
        (clr.RGBpa[2] / 20.0)) - 0.305) * pMod->Nbb;

    return clr;
}