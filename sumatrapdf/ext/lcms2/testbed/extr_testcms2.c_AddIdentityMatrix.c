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
typedef  int cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void AddIdentityMatrix(cmsPipeline* lut)
{
    const cmsFloat64Number Identity[] = { 1, 0, 0,
                          0, 1, 0,
                          0, 0, 1,
                          0, 0, 0 };

    cmsPipelineInsertStage(DbgThread(), lut, cmsAT_END, cmsStageAllocMatrix(DbgThread(), 3, 3, Identity, NULL));
}