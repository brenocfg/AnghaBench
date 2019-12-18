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
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int Check16LUT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  _cmsStageAllocIdentityCLut (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsStageAllocIdentityCurves (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckLUT(cmsInt32Number Pass,  cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsPipeline* Lut, *Pt;
    cmsInt32Number rc;


    switch (Pass) {

        case 1:

            Lut = cmsPipelineAlloc(DbgThread(), 3, 3);
            if (Lut == NULL) return 0;

            // Create an identity LUT
            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_BEGIN, _cmsStageAllocIdentityCurves(DbgThread(), 3));
            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_END, _cmsStageAllocIdentityCLut(DbgThread(), 3));
            cmsPipelineInsertStage(DbgThread(), Lut, cmsAT_END, _cmsStageAllocIdentityCurves(DbgThread(), 3));

            rc =  cmsWriteTag(DbgThread(), hProfile, tag, Lut);
            cmsPipelineFree(DbgThread(), Lut);
            return rc;

        case 2:
            Pt = (cmsPipeline *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;

            // Transform values, check for identity
            return Check16LUT(Pt);

        default:
            return 0;
    }
}