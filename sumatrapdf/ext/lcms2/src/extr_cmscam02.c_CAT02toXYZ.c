#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* XYZ; double* RGB; } ;
typedef  TYPE_1__ CAM02COLOR ;

/* Variables and functions */

__attribute__((used)) static
CAM02COLOR CAT02toXYZ(CAM02COLOR clr)
{
    clr.XYZ[0] = (clr.RGB[0] *  1.096124) + (clr.RGB[1] * -0.278869) + (clr.RGB[2] *  0.182745);
    clr.XYZ[1] = (clr.RGB[0] *  0.454369) + (clr.RGB[1] *  0.473533) + (clr.RGB[2] *  0.072098);
    clr.XYZ[2] = (clr.RGB[0] * -0.009628) + (clr.RGB[1] * -0.005698) + (clr.RGB[2] *  1.015326);

    return clr;
}