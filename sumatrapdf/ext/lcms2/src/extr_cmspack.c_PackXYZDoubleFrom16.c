#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_5__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ cmsCIEXYZ ;
struct TYPE_6__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_2__ _cmsTRANSFORM ;

/* Variables and functions */
 size_t PixelSize (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsXYZEncoded2Float (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* PackXYZDoubleFrom16(cmsContext ContextID, register _cmsTRANSFORM* Info,
                                    register cmsUInt16Number wOut[],
                                    register cmsUInt8Number* output,
                                    register cmsUInt32Number Stride)
{
    if (T_PLANAR(Info -> OutputFormat)) {

        cmsCIEXYZ XYZ;
        cmsFloat64Number* Out = (cmsFloat64Number*) output;
        cmsXYZEncoded2Float(ContextID, &XYZ, wOut);

        Stride /= PixelSize(Info->OutputFormat);

        Out[0]        = XYZ.X;
        Out[Stride]   = XYZ.Y;
        Out[Stride*2] = XYZ.Z;

        return output + sizeof(cmsFloat64Number);

    }
    else {

        cmsXYZEncoded2Float(ContextID, (cmsCIEXYZ*) output, wOut);

        return output + (sizeof(cmsCIEXYZ) + T_EXTRA(Info ->OutputFormat) * sizeof(cmsFloat64Number));
    }
}