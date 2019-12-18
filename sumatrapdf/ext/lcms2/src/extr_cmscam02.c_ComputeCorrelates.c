#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsFloat64Number ;
struct TYPE_7__ {double A; } ;
struct TYPE_8__ {double Nc; double Ncb; double c; double z; double FL; double n; TYPE_1__ adoptedWhite; } ;
typedef  TYPE_2__ cmsCIECAM02 ;
struct TYPE_9__ {double* RGBpa; int h; int H; double J; double A; double Q; double C; double M; double s; } ;
typedef  TYPE_3__ CAM02COLOR ;

/* Variables and functions */
 int atan (int) ; 
 double cos (int) ; 
 double pow (double,double) ; 

__attribute__((used)) static
CAM02COLOR ComputeCorrelates(CAM02COLOR clr, cmsCIECAM02* pMod)
{
    cmsFloat64Number a, b, temp, e, t, r2d, d2r;

    a = clr.RGBpa[0] - (12.0 * clr.RGBpa[1] / 11.0) + (clr.RGBpa[2] / 11.0);
    b = (clr.RGBpa[0] + clr.RGBpa[1] - (2.0 * clr.RGBpa[2])) / 9.0;

    r2d = (180.0 / 3.141592654);
    if (a == 0) {
        if (b == 0)     clr.h = 0;
        else if (b > 0) clr.h = 90;
        else            clr.h = 270;
    }
    else if (a > 0) {
        temp = b / a;
        if (b > 0)       clr.h = (r2d * atan(temp));
        else if (b == 0) clr.h = 0;
        else             clr.h = (r2d * atan(temp)) + 360;
    }
    else {
        temp = b / a;
        clr.h = (r2d * atan(temp)) + 180;
    }

    d2r = (3.141592654 / 180.0);
    e = ((12500.0 / 13.0) * pMod->Nc * pMod->Ncb) *
        (cos((clr.h * d2r + 2.0)) + 3.8);

    if (clr.h < 20.14) {
        temp = ((clr.h + 122.47)/1.2) + ((20.14 - clr.h)/0.8);
        clr.H = 300 + (100*((clr.h + 122.47)/1.2)) / temp;
    }
    else if (clr.h < 90.0) {
        temp = ((clr.h - 20.14)/0.8) + ((90.00 - clr.h)/0.7);
        clr.H = (100*((clr.h - 20.14)/0.8)) / temp;
    }
    else if (clr.h < 164.25) {
        temp = ((clr.h - 90.00)/0.7) + ((164.25 - clr.h)/1.0);
        clr.H = 100 + ((100*((clr.h - 90.00)/0.7)) / temp);
    }
    else if (clr.h < 237.53) {
        temp = ((clr.h - 164.25)/1.0) + ((237.53 - clr.h)/1.2);
        clr.H = 200 + ((100*((clr.h - 164.25)/1.0)) / temp);
    }
    else {
        temp = ((clr.h - 237.53)/1.2) + ((360 - clr.h + 20.14)/0.8);
        clr.H = 300 + ((100*((clr.h - 237.53)/1.2)) / temp);
    }

    clr.J = 100.0 * pow((clr.A / pMod->adoptedWhite.A),
        (pMod->c * pMod->z));

    clr.Q = (4.0 / pMod->c) * pow((clr.J / 100.0), 0.5) *
        (pMod->adoptedWhite.A + 4.0) * pow(pMod->FL, 0.25);

    t = (e * pow(((a * a) + (b * b)), 0.5)) /
        (clr.RGBpa[0] + clr.RGBpa[1] +
        ((21.0 / 20.0) * clr.RGBpa[2]));

    clr.C = pow(t, 0.9) * pow((clr.J / 100.0), 0.5) *
        pow((1.64 - pow(0.29, pMod->n)), 0.73);

    clr.M = clr.C * pow(pMod->FL, 0.25);
    clr.s = 100.0 * pow((clr.M / clr.Q), 0.5);

    return clr;
}