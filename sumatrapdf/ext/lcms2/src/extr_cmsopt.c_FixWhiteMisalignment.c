#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsStage ;
struct TYPE_5__ {scalar_t__ InputChannels; scalar_t__ OutputChannels; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PatchLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WhitesAreEqual (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsEndPointsBySpace (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ ** _cmsStageGetPtrToCurveSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsEvalToneCurve16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsPipelineCheckAndRetreiveStages (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,...) ; 
 int /*<<< orphan*/  cmsPipelineEval16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * cmsReverseToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigCLutElemType ; 
 int /*<<< orphan*/  cmsSigCurveSetElemType ; 

__attribute__((used)) static
cmsBool FixWhiteMisalignment(cmsContext ContextID, cmsPipeline* Lut, cmsColorSpaceSignature EntryColorSpace, cmsColorSpaceSignature ExitColorSpace)
{
    cmsUInt16Number *WhitePointIn, *WhitePointOut;
    cmsUInt16Number  WhiteIn[cmsMAXCHANNELS], WhiteOut[cmsMAXCHANNELS], ObtainedOut[cmsMAXCHANNELS];
    cmsUInt32Number i, nOuts, nIns;
    cmsStage *PreLin = NULL, *CLUT = NULL, *PostLin = NULL;

    if (!_cmsEndPointsBySpace(EntryColorSpace,
        &WhitePointIn, NULL, &nIns)) return FALSE;

    if (!_cmsEndPointsBySpace(ExitColorSpace,
        &WhitePointOut, NULL, &nOuts)) return FALSE;

    // It needs to be fixed?
    if (Lut ->InputChannels != nIns) return FALSE;
    if (Lut ->OutputChannels != nOuts) return FALSE;

    cmsPipelineEval16(ContextID, WhitePointIn, ObtainedOut, Lut);

    if (WhitesAreEqual(nOuts, WhitePointOut, ObtainedOut)) return TRUE; // whites already match

    // Check if the LUT comes as Prelin, CLUT or Postlin. We allow all combinations
    if (!cmsPipelineCheckAndRetreiveStages(ContextID, Lut, 3, cmsSigCurveSetElemType, cmsSigCLutElemType, cmsSigCurveSetElemType, &PreLin, &CLUT, &PostLin))
        if (!cmsPipelineCheckAndRetreiveStages(ContextID, Lut, 2, cmsSigCurveSetElemType, cmsSigCLutElemType, &PreLin, &CLUT))
            if (!cmsPipelineCheckAndRetreiveStages(ContextID, Lut, 2, cmsSigCLutElemType, cmsSigCurveSetElemType, &CLUT, &PostLin))
                if (!cmsPipelineCheckAndRetreiveStages(ContextID, Lut, 1, cmsSigCLutElemType, &CLUT))
                    return FALSE;

    // We need to interpolate white points of both, pre and post curves
    if (PreLin) {

        cmsToneCurve** Curves = _cmsStageGetPtrToCurveSet(PreLin);

        for (i=0; i < nIns; i++) {
            WhiteIn[i] = cmsEvalToneCurve16(ContextID, Curves[i], WhitePointIn[i]);
        }
    }
    else {
        for (i=0; i < nIns; i++)
            WhiteIn[i] = WhitePointIn[i];
    }

    // If any post-linearization, we need to find how is represented white before the curve, do
    // a reverse interpolation in this case.
    if (PostLin) {

        cmsToneCurve** Curves = _cmsStageGetPtrToCurveSet(PostLin);

        for (i=0; i < nOuts; i++) {

            cmsToneCurve* InversePostLin = cmsReverseToneCurve(ContextID, Curves[i]);
            if (InversePostLin == NULL) {
                WhiteOut[i] = WhitePointOut[i];

            } else {

                WhiteOut[i] = cmsEvalToneCurve16(ContextID, InversePostLin, WhitePointOut[i]);
                cmsFreeToneCurve(ContextID, InversePostLin);
            }
        }
    }
    else {
        for (i=0; i < nOuts; i++)
            WhiteOut[i] = WhitePointOut[i];
    }

    // Ok, proceed with patching. May fail and we don't care if it fails
    PatchLUT(ContextID, CLUT, WhiteIn, WhiteOut, nOuts, nIns);

    return TRUE;
}