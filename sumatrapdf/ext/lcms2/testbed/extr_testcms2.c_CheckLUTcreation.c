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
typedef  scalar_t__ cmsInt32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * cmsPipelineDup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsPipelineStageCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckLUTcreation(void)
{
    cmsPipeline* lut;
    cmsPipeline* lut2;
    cmsInt32Number n1, n2;

    lut = cmsPipelineAlloc(DbgThread(), 1, 1);
    n1 = cmsPipelineStageCount(DbgThread(), lut);
    lut2 = cmsPipelineDup(DbgThread(), lut);
    n2 = cmsPipelineStageCount(DbgThread(), lut2);

    cmsPipelineFree(DbgThread(), lut);
    cmsPipelineFree(DbgThread(), lut2);

    return (n1 == 0) && (n2 == 0);
}