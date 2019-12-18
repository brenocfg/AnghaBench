#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  AddIdentityCLUTfloat (int /*<<< orphan*/ *) ; 
 int CheckFloatLUT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateSegmentedCurve () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  _cmsStageAllocLabV2ToV4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageAllocLabV4ToV2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckMPE(cmsInt32Number Pass,  cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsPipeline* Lut, *Pt;
    cmsToneCurve* G[3];
    cmsInt32Number rc;

    switch (Pass) {

        case 1:

            Lut = cmsPipelineAlloc(DbgThread(), 3, 3);

            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_BEGIN, _cmsStageAllocLabV2ToV4(DbgThread()));
            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_END, _cmsStageAllocLabV4ToV2(DbgThread()));
            AddIdentityCLUTfloat(Lut);

            G[0] = G[1] = G[2] = CreateSegmentedCurve();
            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_END, cmsStageAllocToneCurves(DbgThread(), 3, G));
            cmsFreeToneCurve(DbgThread(), G[0]);

            rc = cmsWriteTag(DbgThread(), hProfile, tag, Lut);
            cmsPipelineFree(DbgThread(), Lut);
            return rc;

        case 2:
            Pt = (cmsPipeline *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;
            return CheckFloatLUT(Pt);

        default:
            return 0;
    }
}