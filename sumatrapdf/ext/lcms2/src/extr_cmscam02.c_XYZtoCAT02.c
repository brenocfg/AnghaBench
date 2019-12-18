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
struct TYPE_4__ {double* RGB; double* XYZ; } ;
typedef  TYPE_1__ CAM02COLOR ;

/* Variables and functions */

__attribute__((used)) static
CAM02COLOR XYZtoCAT02(CAM02COLOR clr)
{
    clr.RGB[0] = (clr.XYZ[0] *  0.7328) + (clr.XYZ[1] *  0.4296) + (clr.XYZ[2] * -0.1624);
    clr.RGB[1] = (clr.XYZ[0] * -0.7036) + (clr.XYZ[1] *  1.6975) + (clr.XYZ[2] *  0.0061);
    clr.RGB[2] = (clr.XYZ[0] *  0.0030) + (clr.XYZ[1] *  0.0136) + (clr.XYZ[2] *  0.9834);

    return clr;
}