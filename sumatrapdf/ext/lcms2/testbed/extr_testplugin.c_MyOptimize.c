#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_2__ {int nCurves; int /*<<< orphan*/ * TheCurves; } ;
typedef  TYPE_1__ _cmsStageToneCurvesData ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FastEvaluateCurves ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsPipelineSetOptimizationParameters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double cmsEstimateGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 int /*<<< orphan*/ * cmsPipelineGetPtrToFirstStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSigCurveSetElemType ; 
 scalar_t__ cmsStageData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsStageNext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsStageType (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsBool MyOptimize(cmsContext ContextID, cmsPipeline** Lut,
                   cmsUInt32Number  Intent,
                   cmsUInt32Number* InputFormat,
                   cmsUInt32Number* OutputFormat,
                   cmsUInt32Number* dwFlags)
{
    cmsStage* mpe;
     _cmsStageToneCurvesData* Data;

    //  Only curves in this LUT? All are identities?
    for (mpe = cmsPipelineGetPtrToFirstStage(ContextID, *Lut);
         mpe != NULL;
         mpe = cmsStageNext(ContextID, mpe)) {

            if (cmsStageType(ContextID, mpe) != cmsSigCurveSetElemType) return FALSE;

            // Check for identity
            Data = (_cmsStageToneCurvesData*) cmsStageData(ContextID, mpe);
            if (Data ->nCurves != 1) return FALSE;
            if (cmsEstimateGamma(ContextID, Data->TheCurves[0], 0.1) > 1.0) return FALSE;

    }

    *dwFlags |= cmsFLAGS_NOCACHE;
    _cmsPipelineSetOptimizationParameters(ContextID, *Lut, FastEvaluateCurves, NULL, NULL, NULL);

    return TRUE;
}