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
typedef  scalar_t__ cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */

__attribute__((used)) static
void EvaluateNegate(cmsContext ContextID, const cmsFloat32Number In[],
                     cmsFloat32Number Out[],
                     const cmsStage *mpe)
{
    Out[0] = 1.0f - In[0];
    Out[1] = 1.0f - In[1];
    Out[2] = 1.0f - In[2];
}