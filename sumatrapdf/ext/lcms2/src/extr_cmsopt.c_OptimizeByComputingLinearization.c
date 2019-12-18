#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
struct TYPE_41__ {int /*<<< orphan*/ * Table16; } ;
typedef  TYPE_1__ cmsToneCurve ;
struct TYPE_42__ {scalar_t__ Data; } ;
typedef  TYPE_2__ cmsStage ;
struct TYPE_43__ {size_t InputChannels; int /*<<< orphan*/  OutputChannels; } ;
typedef  TYPE_3__ cmsPipeline ;
typedef  size_t cmsFloat64Number ;
typedef  double cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsColorSpaceSignature ;
typedef  size_t cmsBool ;
struct TYPE_44__ {size_t nCurves; TYPE_1__** TheCurves; } ;
typedef  TYPE_4__ _cmsStageToneCurvesData ;
struct TYPE_45__ {int /*<<< orphan*/  Params; } ;
typedef  TYPE_5__ _cmsStageCLutData ;
typedef  int /*<<< orphan*/  TransReverse ;
typedef  int /*<<< orphan*/  Trans ;
typedef  int /*<<< orphan*/  Prelin8Data ;
typedef  int /*<<< orphan*/  Prelin16Data ;

/* Variables and functions */
 size_t FALSE ; 
 int /*<<< orphan*/  FixWhiteMisalignment (int /*<<< orphan*/ ,TYPE_3__*,scalar_t__,scalar_t__) ; 
 size_t INTENT_ABSOLUTE_COLORIMETRIC ; 
 scalar_t__ IsDegenerated (TYPE_1__*) ; 
 size_t PRELINEARIZATION_POINTS ; 
 scalar_t__ PT_RGB ; 
 int /*<<< orphan*/  Prelin16dup ; 
 int /*<<< orphan*/  Prelin8dup ; 
 int /*<<< orphan*/  Prelin8free ; 
 int /*<<< orphan*/  PrelinEval16 ; 
 int /*<<< orphan*/  PrelinEval8 ; 
 int /*<<< orphan*/ * PrelinOpt16alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrelinOpt16free ; 
 int /*<<< orphan*/ * PrelinOpt8alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  SlopeLimiting (int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t TRUE ; 
 scalar_t__ T_COLORSPACE (size_t) ; 
 scalar_t__ T_PLANAR (size_t) ; 
 int /*<<< orphan*/  XFormSampler16 ; 
 scalar_t__ _cmsFormatterIs8bit (size_t) ; 
 scalar_t__ _cmsFormatterIsFloat (size_t) ; 
 scalar_t__ _cmsICCcolorSpace (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsPipelineSetOptimizationParameters (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsQuickSaturateWord (double) ; 
 size_t _cmsReasonableGridpointsByColorspace (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 TYPE_1__** _cmsStageGetPtrToCurveSet (TYPE_2__*) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 TYPE_1__* cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 size_t cmsFLAGS_CLUT_PRE_LINEARIZATION ; 
 size_t cmsFLAGS_NOWHITEONWHITEFIXUP ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsIsToneCurveLinear (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsIsToneCurveMonotonic (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cmsMAXCHANNELS ; 
 TYPE_3__* cmsPipelineAlloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 TYPE_3__* cmsPipelineDup (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cmsPipelineEvalFloat (int /*<<< orphan*/ ,double*,double*,TYPE_3__*) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* cmsPipelineGetPtrToFirstStage (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* cmsPipelineGetPtrToLastStage (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* cmsReverseToneCurveEx (int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 scalar_t__ cmsSigCurveSetElemType ; 
 scalar_t__ cmsSigNamedColorElemType ; 
 TYPE_2__* cmsStageAllocCLut16bit (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* cmsStageAllocToneCurves (int /*<<< orphan*/ ,size_t,TYPE_1__**) ; 
 scalar_t__ cmsStageData (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* cmsStageNext (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsStageType (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsBool OptimizeByComputingLinearization(cmsContext ContextID, cmsPipeline** Lut, cmsUInt32Number Intent, cmsUInt32Number* InputFormat, cmsUInt32Number* OutputFormat, cmsUInt32Number* dwFlags)
{
    cmsPipeline* OriginalLut;
    cmsUInt32Number nGridPoints;
    cmsToneCurve *Trans[cmsMAXCHANNELS], *TransReverse[cmsMAXCHANNELS];
    cmsUInt32Number t, i;
    cmsFloat32Number v, In[cmsMAXCHANNELS], Out[cmsMAXCHANNELS];
    cmsBool lIsSuitable, lIsLinear;
    cmsPipeline* OptimizedLUT = NULL, *LutPlusCurves = NULL;
    cmsStage* OptimizedCLUTmpe;
    cmsColorSpaceSignature ColorSpace, OutputColorSpace;
    cmsStage* OptimizedPrelinMpe;
    cmsStage* mpe;
    cmsToneCurve** OptimizedPrelinCurves;
    _cmsStageCLutData* OptimizedPrelinCLUT;


    // This is a lossy optimization! does not apply in floating-point cases
    if (_cmsFormatterIsFloat(*InputFormat) || _cmsFormatterIsFloat(*OutputFormat)) return FALSE;

    // Only on chunky RGB
    if (T_COLORSPACE(*InputFormat)  != PT_RGB) return FALSE;
    if (T_PLANAR(*InputFormat)) return FALSE;

    if (T_COLORSPACE(*OutputFormat) != PT_RGB) return FALSE;
    if (T_PLANAR(*OutputFormat)) return FALSE;

    // On 16 bits, user has to specify the feature
    if (!_cmsFormatterIs8bit(*InputFormat)) {
        if (!(*dwFlags & cmsFLAGS_CLUT_PRE_LINEARIZATION)) return FALSE;
    }

    OriginalLut = *Lut;

   // Named color pipelines cannot be optimized either
   for (mpe = cmsPipelineGetPtrToFirstStage(ContextID, OriginalLut);
         mpe != NULL;
         mpe = cmsStageNext(ContextID, mpe)) {
            if (cmsStageType(ContextID, mpe) == cmsSigNamedColorElemType) return FALSE;
    }

    ColorSpace       = _cmsICCcolorSpace(ContextID, (int) T_COLORSPACE(*InputFormat));
    OutputColorSpace = _cmsICCcolorSpace(ContextID, (int) T_COLORSPACE(*OutputFormat));

    // Color space must be specified
    if (ColorSpace == (cmsColorSpaceSignature)0 ||
        OutputColorSpace == (cmsColorSpaceSignature)0) return FALSE;

    nGridPoints      = _cmsReasonableGridpointsByColorspace(ContextID, ColorSpace, *dwFlags);

    // Empty gamma containers
    memset(Trans, 0, sizeof(Trans));
    memset(TransReverse, 0, sizeof(TransReverse));

    // If the last stage of the original lut are curves, and those curves are
    // degenerated, it is likely the transform is squeezing and clipping
    // the output from previous CLUT. We cannot optimize this case
    {
        cmsStage* last = cmsPipelineGetPtrToLastStage(ContextID, OriginalLut);

        if (cmsStageType(ContextID, last) == cmsSigCurveSetElemType) {

            _cmsStageToneCurvesData* Data = (_cmsStageToneCurvesData*)cmsStageData(ContextID, last);
            for (i = 0; i < Data->nCurves; i++) {
                if (IsDegenerated(Data->TheCurves[i]))
                    goto Error;
            }
        }
    }

    for (t = 0; t < OriginalLut ->InputChannels; t++) {
        Trans[t] = cmsBuildTabulatedToneCurve16(ContextID, PRELINEARIZATION_POINTS, NULL);
        if (Trans[t] == NULL) goto Error;
    }

    // Populate the curves
    for (i=0; i < PRELINEARIZATION_POINTS; i++) {

        v = (cmsFloat32Number) ((cmsFloat64Number) i / (PRELINEARIZATION_POINTS - 1));

        // Feed input with a gray ramp
        for (t=0; t < OriginalLut ->InputChannels; t++)
            In[t] = v;

        // Evaluate the gray value
        cmsPipelineEvalFloat(ContextID, In, Out, OriginalLut);

        // Store result in curve
        for (t=0; t < OriginalLut ->InputChannels; t++)
            Trans[t] ->Table16[i] = _cmsQuickSaturateWord(Out[t] * 65535.0);
    }

    // Slope-limit the obtained curves
    for (t = 0; t < OriginalLut ->InputChannels; t++)
        SlopeLimiting(ContextID, Trans[t]);

    // Check for validity
    lIsSuitable = TRUE;
    lIsLinear   = TRUE;
    for (t=0; (lIsSuitable && (t < OriginalLut ->InputChannels)); t++) {

        // Exclude if already linear
        if (!cmsIsToneCurveLinear(ContextID, Trans[t]))
            lIsLinear = FALSE;

        // Exclude if non-monotonic
        if (!cmsIsToneCurveMonotonic(ContextID, Trans[t]))
            lIsSuitable = FALSE;

        if (IsDegenerated(Trans[t]))
            lIsSuitable = FALSE;
    }

    // If it is not suitable, just quit
    if (!lIsSuitable) goto Error;

    // Invert curves if possible
    for (t = 0; t < OriginalLut ->InputChannels; t++) {
        TransReverse[t] = cmsReverseToneCurveEx(ContextID, PRELINEARIZATION_POINTS, Trans[t]);
        if (TransReverse[t] == NULL) goto Error;
    }

    // Now inset the reversed curves at the begin of transform
    LutPlusCurves = cmsPipelineDup(ContextID, OriginalLut);
    if (LutPlusCurves == NULL) goto Error;

    if (!cmsPipelineInsertStage(ContextID, LutPlusCurves, cmsAT_BEGIN, cmsStageAllocToneCurves(ContextID, OriginalLut ->InputChannels, TransReverse)))
        goto Error;

    // Create the result LUT
    OptimizedLUT = cmsPipelineAlloc(ContextID, OriginalLut ->InputChannels, OriginalLut ->OutputChannels);
    if (OptimizedLUT == NULL) goto Error;

    OptimizedPrelinMpe = cmsStageAllocToneCurves(ContextID, OriginalLut ->InputChannels, Trans);

    // Create and insert the curves at the beginning
    if (!cmsPipelineInsertStage(ContextID, OptimizedLUT, cmsAT_BEGIN, OptimizedPrelinMpe))
        goto Error;

    // Allocate the CLUT for result
    OptimizedCLUTmpe = cmsStageAllocCLut16bit(ContextID, nGridPoints, OriginalLut ->InputChannels, OriginalLut ->OutputChannels, NULL);

    // Add the CLUT to the destination LUT
    if (!cmsPipelineInsertStage(ContextID, OptimizedLUT, cmsAT_END, OptimizedCLUTmpe))
        goto Error;

    // Resample the LUT
    if (!cmsStageSampleCLut16bit(ContextID, OptimizedCLUTmpe, XFormSampler16, (void*) LutPlusCurves, 0)) goto Error;

    // Free resources
    for (t = 0; t < OriginalLut ->InputChannels; t++) {

        if (Trans[t]) cmsFreeToneCurve(ContextID, Trans[t]);
        if (TransReverse[t]) cmsFreeToneCurve(ContextID, TransReverse[t]);
    }

    cmsPipelineFree(ContextID, LutPlusCurves);


    OptimizedPrelinCurves = _cmsStageGetPtrToCurveSet(OptimizedPrelinMpe);
    OptimizedPrelinCLUT   = (_cmsStageCLutData*) OptimizedCLUTmpe ->Data;

    // Set the evaluator if 8-bit
    if (_cmsFormatterIs8bit(*InputFormat)) {

        Prelin8Data* p8 = PrelinOpt8alloc(ContextID,
                                                OptimizedPrelinCLUT ->Params,
                                                OptimizedPrelinCurves);
        if (p8 == NULL) return FALSE;

        _cmsPipelineSetOptimizationParameters(ContextID, OptimizedLUT, PrelinEval8, (void*) p8, Prelin8free, Prelin8dup);

    }
    else
    {
        Prelin16Data* p16 = PrelinOpt16alloc(ContextID,
            OptimizedPrelinCLUT ->Params,
            3, OptimizedPrelinCurves, 3, NULL);
        if (p16 == NULL) return FALSE;

        _cmsPipelineSetOptimizationParameters(ContextID, OptimizedLUT, PrelinEval16, (void*) p16, PrelinOpt16free, Prelin16dup);

    }

    // Don't fix white on absolute colorimetric
    if (Intent == INTENT_ABSOLUTE_COLORIMETRIC)
        *dwFlags |= cmsFLAGS_NOWHITEONWHITEFIXUP;

    if (!(*dwFlags & cmsFLAGS_NOWHITEONWHITEFIXUP)) {

        if (!FixWhiteMisalignment(ContextID, OptimizedLUT, ColorSpace, OutputColorSpace)) {

            return FALSE;
        }
    }

    // And return the obtained LUT

    cmsPipelineFree(ContextID, OriginalLut);
    *Lut = OptimizedLUT;
    return TRUE;

Error:

    for (t = 0; t < OriginalLut ->InputChannels; t++) {

        if (Trans[t]) cmsFreeToneCurve(ContextID, Trans[t]);
        if (TransReverse[t]) cmsFreeToneCurve(ContextID, TransReverse[t]);
    }

    if (LutPlusCurves != NULL) cmsPipelineFree(ContextID, LutPlusCurves);
    if (OptimizedLUT != NULL) cmsPipelineFree(ContextID, OptimizedLUT);

    return FALSE;

    cmsUNUSED_PARAMETER(Intent);
    cmsUNUSED_PARAMETER(lIsLinear);
}