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
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ cmsCIELab ;
struct TYPE_6__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_2__ _cmsTRANSFORM ;

/* Variables and functions */
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsLabEncoded2Float (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* PackLabDoubleFrom16(cmsContext ContextID, register _cmsTRANSFORM* info,
                                    register cmsUInt16Number wOut[],
                                    register cmsUInt8Number* output,
                                    register cmsUInt32Number Stride)
{

    if (T_PLANAR(info -> OutputFormat)) {

        cmsCIELab  Lab;
        cmsFloat64Number* Out = (cmsFloat64Number*) output;
        cmsLabEncoded2Float(ContextID, &Lab, wOut);

        Out[0]        = Lab.L;
        Out[Stride]   = Lab.a;
        Out[Stride*2] = Lab.b;

        return output + sizeof(cmsFloat64Number);
    }
    else {

        cmsLabEncoded2Float(ContextID, (cmsCIELab*) output, wOut);
        return output + (sizeof(cmsCIELab) + T_EXTRA(info ->OutputFormat) * sizeof(cmsFloat64Number));
    }
}