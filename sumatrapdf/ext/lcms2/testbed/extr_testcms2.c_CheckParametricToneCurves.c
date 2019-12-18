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
typedef  int cmsInt32Number ;
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  CIE122 ; 
 int /*<<< orphan*/  CheckSingleParametric (char*,int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  Gamma ; 
 int /*<<< orphan*/  IEC61966_21 ; 
 int /*<<< orphan*/  IEC61966_3 ; 
 int /*<<< orphan*/  param_5 ; 
 int /*<<< orphan*/  param_6 ; 
 int /*<<< orphan*/  param_7 ; 
 int /*<<< orphan*/  param_8 ; 
 int /*<<< orphan*/  sigmoidal ; 

__attribute__((used)) static
cmsInt32Number CheckParametricToneCurves(void)
{
    cmsFloat64Number Params[10];

     // 1) X = Y ^ Gamma

     Params[0] = 2.2;

     if (!CheckSingleParametric("Gamma", Gamma, 1, Params)) return 0;

     // 2) CIE 122-1966
     // Y = (aX + b)^Gamma  | X >= -b/a
     // Y = 0               | else

     Params[0] = 2.2;
     Params[1] = 1.5;
     Params[2] = -0.5;

     if (!CheckSingleParametric("CIE122-1966", CIE122, 2, Params)) return 0;

     // 3) IEC 61966-3
     // Y = (aX + b)^Gamma | X <= -b/a
     // Y = c              | else

     Params[0] = 2.2;
     Params[1] = 1.5;
     Params[2] = -0.5;
     Params[3] = 0.3;


     if (!CheckSingleParametric("IEC 61966-3", IEC61966_3, 3, Params)) return 0;

     // 4) IEC 61966-2.1 (sRGB)
     // Y = (aX + b)^Gamma | X >= d
     // Y = cX             | X < d

     Params[0] = 2.4;
     Params[1] = 1. / 1.055;
     Params[2] = 0.055 / 1.055;
     Params[3] = 1. / 12.92;
     Params[4] = 0.04045;

     if (!CheckSingleParametric("IEC 61966-2.1", IEC61966_21, 4, Params)) return 0;


     // 5) Y = (aX + b)^Gamma + e | X >= d
     // Y = cX + f             | else

     Params[0] = 2.2;
     Params[1] = 0.7;
     Params[2] = 0.2;
     Params[3] = 0.3;
     Params[4] = 0.1;
     Params[5] = 0.5;
     Params[6] = 0.2;

     if (!CheckSingleParametric("param_5", param_5, 5, Params)) return 0;

     // 6) Y = (aX + b) ^ Gamma + c

     Params[0] = 2.2;
     Params[1] = 0.7;
     Params[2] = 0.2;
     Params[3] = 0.3;

     if (!CheckSingleParametric("param_6", param_6, 6, Params)) return 0;

     // 7) Y = a * log (b * X^Gamma + c) + d

     Params[0] = 2.2;
     Params[1] = 0.9;
     Params[2] = 0.9;
     Params[3] = 0.02;
     Params[4] = 0.1;

     if (!CheckSingleParametric("param_7", param_7, 7, Params)) return 0;

     // 8) Y = a * b ^ (c*X+d) + e

     Params[0] = 0.9;
     Params[1] = 0.9;
     Params[2] = 1.02;
     Params[3] = 0.1;
     Params[4] = 0.2;

     if (!CheckSingleParametric("param_8", param_8, 8, Params)) return 0;

     // 108: S-Shaped: (1 - (1-x)^1/g)^1/g

     Params[0] = 1.9;
     if (!CheckSingleParametric("sigmoidal", sigmoidal, 108, Params)) return 0;

     // All OK

     return 1;
}