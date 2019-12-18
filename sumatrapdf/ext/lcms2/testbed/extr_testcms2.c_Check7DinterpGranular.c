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
 int /*<<< orphan*/  CheckOne7D (int /*<<< orphan*/ *,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Sampler7D ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bitGranular (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number Check7DinterpGranular(void)
{
    cmsPipeline* lut;
    cmsStage* mpe;
    cmsUInt32Number Dimensions[] = { 4, 3, 3, 2, 2, 2, 2 };

    lut = cmsPipelineAlloc(DbgThread(), 7, 3);
    mpe = cmsStageAllocCLut16bitGranular(DbgThread(), Dimensions, 7, 3, NULL);
    cmsStageSampleCLut16bit(DbgThread(), mpe, Sampler7D, NULL, 0);
    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_BEGIN, mpe);

    // Check accuracy

    if (!CheckOne7D(lut, 0, 0, 0, 0, 0, 0, 0)) return 0;
    if (!CheckOne7D(lut, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff)) return 0;

    if (!CheckOne7D(lut, 0x8080, 0x8080, 0x8080, 0x8080, 0x1234, 0x1122, 0x0056)) return 0;
    if (!CheckOne7D(lut, 0x0000, 0xFE00, 0x80FF, 0x8888, 0x8078, 0x2233, 0x0088)) return 0;
    if (!CheckOne7D(lut, 0x1111, 0x2222, 0x3333, 0x4444, 0x1455, 0x3344, 0x1987)) return 0;
    if (!CheckOne7D(lut, 0x0000, 0x0012, 0x0013, 0x0014, 0x2333, 0x4455, 0x9988)) return 0;
    if (!CheckOne7D(lut, 0x3141, 0x1415, 0x1592, 0x9261, 0x4567, 0x5566, 0xfe56)) return 0;
    if (!CheckOne7D(lut, 0xFF00, 0xFF01, 0xFF12, 0xFF13, 0xF344, 0x6677, 0xbabe)) return 0;

    cmsPipelineFree(DbgThread(), lut);

    return 1;
}