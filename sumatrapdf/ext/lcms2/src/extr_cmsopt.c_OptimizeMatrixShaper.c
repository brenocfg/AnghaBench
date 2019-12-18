#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  cmsVEC3 ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
struct TYPE_11__ {int /*<<< orphan*/  OutputChannels; int /*<<< orphan*/  InputChannels; } ;
typedef  TYPE_1__ cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsBool ;
struct TYPE_12__ {int /*<<< orphan*/  TheCurves; } ;
typedef  TYPE_2__ _cmsStageToneCurvesData ;
struct TYPE_13__ {int /*<<< orphan*/ * Offset; scalar_t__ Double; } ;
typedef  TYPE_3__ _cmsStageMatrixData ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  OptimizeByJoiningCurves (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetMatShaper (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int T_CHANNELS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsFormatterIs8bit (int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsMAT3isIdentity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsMAT3per (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 TYPE_1__* cmsPipelineAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsPipelineCheckAndRetreiveStages (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,...) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigCurveSetElemType ; 
 int /*<<< orphan*/  cmsSigMatrixElemType ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsStageData (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageDup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static
cmsBool OptimizeMatrixShaper(cmsContext ContextID, cmsPipeline** Lut, cmsUInt32Number Intent, cmsUInt32Number* InputFormat, cmsUInt32Number* OutputFormat, cmsUInt32Number* dwFlags)
{
       cmsStage* Curve1, *Curve2;
       cmsStage* Matrix1, *Matrix2;
       cmsMAT3 res;
       cmsBool IdentityMat;
       cmsPipeline* Dest, *Src;
       cmsFloat64Number* Offset;

       // Only works on RGB to RGB
       if (T_CHANNELS(*InputFormat) != 3 || T_CHANNELS(*OutputFormat) != 3) return FALSE;

       // Only works on 8 bit input
       if (!_cmsFormatterIs8bit(*InputFormat)) return FALSE;

       // Seems suitable, proceed
       Src = *Lut;

       // Check for:
       //
       //    shaper-matrix-matrix-shaper
       //    shaper-matrix-shaper
       //
       // Both of those constructs are possible (first because abs. colorimetric).
       // additionally, In the first case, the input matrix offset should be zero.

       IdentityMat = FALSE;
       if (cmsPipelineCheckAndRetreiveStages(ContextID, Src, 4,
              cmsSigCurveSetElemType, cmsSigMatrixElemType, cmsSigMatrixElemType, cmsSigCurveSetElemType,
              &Curve1, &Matrix1, &Matrix2, &Curve2)) {

              // Get both matrices
              _cmsStageMatrixData* Data1 = (_cmsStageMatrixData*)cmsStageData(ContextID, Matrix1);
              _cmsStageMatrixData* Data2 = (_cmsStageMatrixData*)cmsStageData(ContextID, Matrix2);

              // Input offset should be zero
              if (Data1->Offset != NULL) return FALSE;

              // Multiply both matrices to get the result
              _cmsMAT3per(ContextID, &res, (cmsMAT3*)Data2->Double, (cmsMAT3*)Data1->Double);

              // Only 2nd matrix has offset, or it is zero
              Offset = Data2->Offset;

              // Now the result is in res + Data2 -> Offset. Maybe is a plain identity?
              if (_cmsMAT3isIdentity(ContextID, &res) && Offset == NULL) {

                     // We can get rid of full matrix
                     IdentityMat = TRUE;
              }

       }
       else {

              if (cmsPipelineCheckAndRetreiveStages(ContextID, Src, 3,
                     cmsSigCurveSetElemType, cmsSigMatrixElemType, cmsSigCurveSetElemType,
                     &Curve1, &Matrix1, &Curve2)) {

                     _cmsStageMatrixData* Data = (_cmsStageMatrixData*)cmsStageData(ContextID, Matrix1);

                     // Copy the matrix to our result
                     memcpy(&res, Data->Double, sizeof(res));

                     // Preserve the Odffset (may be NULL as a zero offset)
                     Offset = Data->Offset;

                     if (_cmsMAT3isIdentity(ContextID, &res) && Offset == NULL) {

                            // We can get rid of full matrix
                            IdentityMat = TRUE;
                     }
              }
              else
                     return FALSE; // Not optimizeable this time

       }

      // Allocate an empty LUT
    Dest =  cmsPipelineAlloc(ContextID, Src ->InputChannels, Src ->OutputChannels);
    if (!Dest) return FALSE;

    // Assamble the new LUT
    if (!cmsPipelineInsertStage(ContextID, Dest, cmsAT_BEGIN, cmsStageDup(ContextID, Curve1)))
        goto Error;

    if (!IdentityMat) {

           if (!cmsPipelineInsertStage(ContextID, Dest, cmsAT_END, cmsStageAllocMatrix(ContextID, 3, 3, (const cmsFloat64Number*)&res, Offset)))
                  goto Error;
    }

    if (!cmsPipelineInsertStage(ContextID, Dest, cmsAT_END, cmsStageDup(ContextID, Curve2)))
        goto Error;

    // If identity on matrix, we can further optimize the curves, so call the join curves routine
    if (IdentityMat) {

        OptimizeByJoiningCurves(ContextID, &Dest, Intent, InputFormat, OutputFormat, dwFlags);
    }
    else {
        _cmsStageToneCurvesData* mpeC1 = (_cmsStageToneCurvesData*) cmsStageData(ContextID, Curve1);
        _cmsStageToneCurvesData* mpeC2 = (_cmsStageToneCurvesData*) cmsStageData(ContextID, Curve2);

        // In this particular optimization, cache does not help as it takes more time to deal with
        // the cache that with the pixel handling
        *dwFlags |= cmsFLAGS_NOCACHE;

        // Setup the optimizarion routines
        SetMatShaper(ContextID, Dest, mpeC1 ->TheCurves, &res, (cmsVEC3*) Offset, mpeC2->TheCurves, OutputFormat);
    }

    cmsPipelineFree(ContextID, Src);
    *Lut = Dest;
    return TRUE;
Error:
    // Leave Src unchanged
    cmsPipelineFree(ContextID, Dest);
    return FALSE;
}