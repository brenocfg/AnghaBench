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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
typedef  double cmsFloat64Number ;
typedef  scalar_t__ cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  InputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 size_t PixelSize (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollLabDoubleToFloat(cmsContext ContextID, _cmsTRANSFORM* info,
                                       cmsFloat32Number wIn[],
                                       cmsUInt8Number* accum,
                                       cmsUInt32Number Stride)
{
    cmsFloat64Number* Pt = (cmsFloat64Number*) accum;

    if (T_PLANAR(info -> InputFormat)) {

        Stride /= PixelSize(info->InputFormat);

        wIn[0] = (cmsFloat32Number) (Pt[0] / 100.0);                 // from 0..100 to 0..1
        wIn[1] = (cmsFloat32Number) ((Pt[Stride] + 128) / 255.0);    // form -128..+127 to 0..1
        wIn[2] = (cmsFloat32Number) ((Pt[Stride*2] + 128) / 255.0);

        return accum + sizeof(cmsFloat64Number);
    }
    else {

        wIn[0] = (cmsFloat32Number) (Pt[0] / 100.0);            // from 0..100 to 0..1
        wIn[1] = (cmsFloat32Number) ((Pt[1] + 128) / 255.0);    // form -128..+127 to 0..1
        wIn[2] = (cmsFloat32Number) ((Pt[2] + 128) / 255.0);

        accum += sizeof(cmsFloat64Number)*(3 + T_EXTRA(info ->InputFormat));
        return accum;
    }
}