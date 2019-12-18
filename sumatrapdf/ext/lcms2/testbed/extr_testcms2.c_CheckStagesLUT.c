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
 int /*<<< orphan*/  DbgThread () ; 
 int cmsPipelineInputChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsPipelineOutputChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsPipelineStageCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckStagesLUT(cmsPipeline* lut, cmsInt32Number ExpectedStages)
{

    cmsInt32Number nInpChans, nOutpChans, nStages;

    nInpChans  = cmsPipelineInputChannels(DbgThread(), lut);
    nOutpChans = cmsPipelineOutputChannels(DbgThread(), lut);
    nStages    = cmsPipelineStageCount(DbgThread(), lut);

    return (nInpChans == 3) && (nOutpChans == 3) && (nStages == ExpectedStages);
}