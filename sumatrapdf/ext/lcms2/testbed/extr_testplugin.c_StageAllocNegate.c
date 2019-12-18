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
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  EvaluateNegate ; 
 int /*<<< orphan*/  SigNegateType ; 
 int /*<<< orphan*/ * _cmsStageAllocPlaceholder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsStage* StageAllocNegate(cmsContext ContextID)
{
    return _cmsStageAllocPlaceholder(ContextID,
                 SigNegateType, 3, 3, EvaluateNegate,
                 NULL, NULL, NULL);
}