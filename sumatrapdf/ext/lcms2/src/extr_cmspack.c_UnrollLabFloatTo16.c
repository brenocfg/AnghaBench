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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  void* cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_5__ {void* b; void* a; void* L; } ;
typedef  TYPE_1__ cmsCIELab ;
struct TYPE_6__ {int /*<<< orphan*/  InputFormat; } ;
typedef  TYPE_2__ _cmsTRANSFORM ;

/* Variables and functions */
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFloat2LabEncoded (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollLabFloatTo16(cmsContext ContextID, register _cmsTRANSFORM* info,
                                    register cmsUInt16Number wIn[],
                                    register cmsUInt8Number* accum,
                                    register cmsUInt32Number  Stride)
{
    cmsCIELab Lab;

    if (T_PLANAR(info -> InputFormat)) {

        cmsUInt8Number* pos_L;
        cmsUInt8Number* pos_a;
        cmsUInt8Number* pos_b;

        pos_L = accum;
        pos_a = accum + Stride;
        pos_b = accum + Stride * 2;

        Lab.L = *(cmsFloat32Number*)pos_L;
        Lab.a = *(cmsFloat32Number*)pos_a;
        Lab.b = *(cmsFloat32Number*)pos_b;

        cmsFloat2LabEncoded(ContextID, wIn, &Lab);
        return accum + sizeof(cmsFloat32Number);
    }
    else {

        Lab.L = ((cmsFloat32Number*) accum)[0];
        Lab.a = ((cmsFloat32Number*) accum)[1];
        Lab.b = ((cmsFloat32Number*) accum)[2];

        cmsFloat2LabEncoded(ContextID, wIn, &Lab);
        accum += (3 + T_EXTRA(info ->InputFormat)) * sizeof(cmsFloat32Number);
        return accum;
    }
}