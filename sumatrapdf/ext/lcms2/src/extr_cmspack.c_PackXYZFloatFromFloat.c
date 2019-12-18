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
typedef  int cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 int MAX_ENCODEABLE_XYZ ; 
 size_t PixelSize (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsUInt8Number* PackXYZFloatFromFloat(cmsContext ContextID, _cmsTRANSFORM* Info,
                                      cmsFloat32Number wOut[],
                                      cmsUInt8Number* output,
                                      cmsUInt32Number Stride)
{
    cmsFloat32Number* Out = (cmsFloat32Number*) output;

    if (T_PLANAR(Info -> OutputFormat)) {

        Stride /= PixelSize(Info->OutputFormat);

        Out[0]        = (cmsFloat32Number) (wOut[0] * MAX_ENCODEABLE_XYZ);
        Out[Stride]   = (cmsFloat32Number) (wOut[1] * MAX_ENCODEABLE_XYZ);
        Out[Stride*2] = (cmsFloat32Number) (wOut[2] * MAX_ENCODEABLE_XYZ);

        return output + sizeof(cmsFloat32Number);
    }
    else {

        Out[0] = (cmsFloat32Number) (wOut[0] * MAX_ENCODEABLE_XYZ);
        Out[1] = (cmsFloat32Number) (wOut[1] * MAX_ENCODEABLE_XYZ);
        Out[2] = (cmsFloat32Number) (wOut[2] * MAX_ENCODEABLE_XYZ);

        return output + (sizeof(cmsFloat32Number)*3 + T_EXTRA(Info ->OutputFormat) * sizeof(cmsFloat32Number));
    }

}