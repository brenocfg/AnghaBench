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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 scalar_t__ CheckFloatLUT (int /*<<< orphan*/ *) ; 
 scalar_t__ CheckStagesLUT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  _cmsStageAllocLab2XYZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageAllocXYZ2Lab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number CheckXYZ2XYZLUT(void)
{
    cmsPipeline* lut = cmsPipelineAlloc(DbgThread(), 3, 3);
    cmsInt32Number rc;

    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, _cmsStageAllocXYZ2Lab(DbgThread()));
    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, _cmsStageAllocLab2XYZ(DbgThread()));

    rc = CheckFloatLUT(lut) && CheckStagesLUT(lut, 2);

    cmsPipelineFree(DbgThread(), lut);

    return rc;
}