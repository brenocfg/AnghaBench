#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_4__ {int nSegments; TYPE_2__* Segments; } ;
typedef  TYPE_1__ cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsFloat32Number ;
struct TYPE_5__ {int Type; int nGridPoints; scalar_t__* Params; int /*<<< orphan*/ * SampledPoints; int /*<<< orphan*/  x1; } ;
typedef  TYPE_2__ cmsCurveSegment ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsWriteFloat32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cmsSigFormulaCurveSeg ; 
 scalar_t__ cmsSigSampledCurveSeg ; 
 int cmsSigSegmentedCurve ; 

__attribute__((used)) static
cmsBool WriteSegmentedCurve(cmsContext ContextID, cmsIOHANDLER* io, cmsToneCurve* g)
{
    cmsUInt32Number i, j;
    cmsCurveSegment* Segments = g ->Segments;
    cmsUInt32Number nSegments = g ->nSegments;

    if (!_cmsWriteUInt32Number(ContextID, io, cmsSigSegmentedCurve)) goto Error;
    if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;
    if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) nSegments)) goto Error;
    if (!_cmsWriteUInt16Number(ContextID, io, 0)) goto Error;

    // Write the break-points
    for (i=0; i < nSegments - 1; i++) {
        if (!_cmsWriteFloat32Number(ContextID, io, Segments[i].x1)) goto Error;
    }

    // Write the segments
    for (i=0; i < g ->nSegments; i++) {

        cmsCurveSegment* ActualSeg = Segments + i;

        if (ActualSeg -> Type == 0) {

            // This is a sampled curve
            if (!_cmsWriteUInt32Number(ContextID, io, (cmsUInt32Number) cmsSigSampledCurveSeg)) goto Error;
            if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;
            if (!_cmsWriteUInt32Number(ContextID, io, ActualSeg -> nGridPoints)) goto Error;

            for (j=0; j < g ->Segments[i].nGridPoints; j++) {
                if (!_cmsWriteFloat32Number(ContextID, io, ActualSeg -> SampledPoints[j])) goto Error;
            }

        }
        else {
            int Type;
            cmsUInt32Number ParamsByType[] = { 4, 5, 5 };

            // This is a formula-based
            if (!_cmsWriteUInt32Number(ContextID, io, (cmsUInt32Number) cmsSigFormulaCurveSeg)) goto Error;
            if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;

            // We only allow 1, 2 and 3 as types
            Type = ActualSeg ->Type - 6;
            if (Type > 2 || Type < 0) goto Error;

            if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) Type)) goto Error;
            if (!_cmsWriteUInt16Number(ContextID, io, 0)) goto Error;

            for (j=0; j < ParamsByType[Type]; j++) {
                if (!_cmsWriteFloat32Number(ContextID, io, (cmsFloat32Number) ActualSeg ->Params[j])) goto Error;
            }
        }

        // It seems there is no need to align. Code is here, and for safety commented out
        // if (!_cmsWriteAlignment(ContextID, io)) goto Error;
    }

    return TRUE;

Error:
    return FALSE;
}