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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
struct TYPE_5__ {TYPE_1__* v; } ;
typedef  TYPE_2__ cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_4__ {int /*<<< orphan*/ * n; } ;

/* Variables and functions */
 int /*<<< orphan*/  InpAdj ; 
 int /*<<< orphan*/  ReadICCMatrixRGB2XYZ (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageAllocXYZ2Lab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigBlueTRCTag ; 
 int /*<<< orphan*/  cmsSigGreenTRCTag ; 
 scalar_t__ cmsSigLabData ; 
 int /*<<< orphan*/  cmsSigRedTRCTag ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static
cmsPipeline* BuildRGBInputMatrixShaper(cmsContext ContextID, cmsHPROFILE hProfile)
{
    cmsPipeline* Lut;
    cmsMAT3 Mat;
    cmsToneCurve *Shapes[3];
    int i, j;

    if (!ReadICCMatrixRGB2XYZ(ContextID, &Mat, hProfile)) return NULL;

    // XYZ PCS in encoded in 1.15 format, and the matrix output comes in 0..0xffff range, so
    // we need to adjust the output by a factor of (0x10000/0xffff) to put data in
    // a 1.16 range, and then a >> 1 to obtain 1.15. The total factor is (65536.0)/(65535.0*2)

    for (i=0; i < 3; i++)
        for (j=0; j < 3; j++)
            Mat.v[i].n[j] *= InpAdj;


    Shapes[0] = (cmsToneCurve *) cmsReadTag(ContextID, hProfile, cmsSigRedTRCTag);
    Shapes[1] = (cmsToneCurve *) cmsReadTag(ContextID, hProfile, cmsSigGreenTRCTag);
    Shapes[2] = (cmsToneCurve *) cmsReadTag(ContextID, hProfile, cmsSigBlueTRCTag);

    if (!Shapes[0] || !Shapes[1] || !Shapes[2])
        return NULL;

    Lut = cmsPipelineAlloc(ContextID, 3, 3);
    if (Lut != NULL) {

        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, 3, Shapes)) ||
            !cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocMatrix(ContextID, 3, 3, (cmsFloat64Number*) &Mat, NULL)))
            goto Error;

        // Note that it is certainly possible a single profile would have a LUT based
        // tag for output working in lab and a matrix-shaper for the fallback cases.
        // This is not allowed by the spec, but this code is tolerant to those cases
        if (cmsGetPCS(ContextID, hProfile) == cmsSigLabData) {

            if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, _cmsStageAllocXYZ2Lab(ContextID)))
                goto Error;
        }

    }

    return Lut;

Error:
    cmsPipelineFree(ContextID, Lut);
    return NULL;
}