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
typedef  scalar_t__ cmsUInt16Number ;
struct TYPE_3__ {int L; int a; int b; } ;
typedef  TYPE_1__ cmsCIELab ;

/* Variables and functions */
 scalar_t__ floor (double) ; 

__attribute__((used)) static
void Lab2ITU(const cmsCIELab* Lab, cmsUInt16Number Out[3])
{
    Out[0] = (cmsUInt16Number) floor((double) (Lab -> L / 100.)* 65535. );
    Out[1] = (cmsUInt16Number) floor((double) (Lab -> a / 170.)* 65535. + 32768. );
    Out[2] = (cmsUInt16Number) floor((double) (Lab -> b / 200.)* 65535. + 24576. );
}