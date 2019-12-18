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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckOne4D (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Sampler4D ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bitGranular (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number Check4DinterpGranular(void)
{
    cmsPipeline* lut;
    cmsStage* mpe;
    cmsUInt32Number Dimensions[] = { 9, 8, 7, 6 };

    lut = cmsPipelineAlloc(DbgThread(), 4, 3);
    mpe = cmsStageAllocCLut16bitGranular(DbgThread(), Dimensions, 4, 3, NULL);
    cmsStageSampleCLut16bit(DbgThread(), mpe, Sampler4D, NULL, 0);
    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_BEGIN, mpe);

    // Check accuracy

    if (!CheckOne4D(lut, 0, 0, 0, 0)) return 0;
    if (!CheckOne4D(lut, 0xffff, 0xffff, 0xffff, 0xffff)) return 0;

    if (!CheckOne4D(lut, 0x8080, 0x8080, 0x8080, 0x8080)) return 0;
    if (!CheckOne4D(lut, 0x0000, 0xFE00, 0x80FF, 0x8888)) return 0;
    if (!CheckOne4D(lut, 0x1111, 0x2222, 0x3333, 0x4444)) return 0;
    if (!CheckOne4D(lut, 0x0000, 0x0012, 0x0013, 0x0014)) return 0;
    if (!CheckOne4D(lut, 0x3141, 0x1415, 0x1592, 0x9261)) return 0;
    if (!CheckOne4D(lut, 0xFF00, 0xFF01, 0xFF12, 0xFF13)) return 0;

    cmsPipelineFree(DbgThread(), lut);

    return 1;
}