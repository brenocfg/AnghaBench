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
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static
void Add3GammaCurves(cmsPipeline* lut, cmsFloat64Number Curve)
{
    cmsToneCurve* id = cmsBuildGamma(DbgThread(), Curve);
    cmsToneCurve* id3[3];

    id3[0] = id;
    id3[1] = id;
    id3[2] = id;

    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, cmsStageAllocToneCurves(DbgThread(), 3, id3));

    cmsFreeToneCurve(DbgThread(), id);
}